#define TRACE_MODULE _s1ap_usrsctp

#include "core_debug.h"
#include "core_thread.h"

#include "mme_event.h"

#include "s1ap_path.h"

#if HAVE_USRSCTP_H
#ifndef INET
#define INET            1
#endif
#ifndef INET6
#define INET6           1
#endif
#include <usrsctp.h>
#endif

static status_t s1ap_usrsctp_socket(sock_id *new,
    int family, int type,
    int (*receive_cb)(struct socket *sock, union sctp_sockstore addr,
        void *data, size_t datalen, struct sctp_rcvinfo, int flags,
        void *ulp_info));
static status_t s1ap_usrsctp_bind(sock_id id, c_sockaddr_t *sa);
static status_t s1ap_usrsctp_connect(sock_id id, c_sockaddr_t *sa);
static status_t s1ap_usrsctp_listen(sock_id id);

static int s1ap_usrsctp_recv_cb(struct socket *sock,
        union sctp_sockstore addr, void *data, size_t datalen,
        struct sctp_rcvinfo rcv, int flags, void *ulp_info);

static c_sockaddr_t *usrsctp_remote_addr(union sctp_sockstore *store);
static void debug_printf(const char *format, ...);

status_t s1ap_init(c_uint16_t port)
{
    usrsctp_init(port, NULL, debug_printf);
#ifdef SCTP_DEBUG
    usrsctp_sysctl_set_sctp_debug_on(SCTP_DEBUG_ALL);
#endif
    usrsctp_sysctl_set_sctp_blackhole(2);
    usrsctp_sysctl_set_sctp_enable_sack_immediately(1);

    return CORE_OK;
}

status_t s1ap_final()
{
    while(usrsctp_finish() != 0)
    {
        d_error("try to finsih SCTP\n");
        core_sleep(time_from_msec(1000));
    }
    return CORE_OK;
}

status_t s1ap_server(sock_id *new,
        int family, int type, const char *hostname, c_uint16_t port)
{
    status_t rv;
    c_sockaddr_t *sa;
    char buf[CORE_ADDRSTRLEN];

    rv = core_getaddrinfo(&sa, family, hostname, port, AI_PASSIVE);
    d_assert(rv == CORE_OK && sa, return CORE_ERROR,);

    while(sa)
    {
        rv = s1ap_usrsctp_socket(new,
                sa->c_sa_family, type, s1ap_usrsctp_recv_cb);
        if (rv != CORE_OK) continue;
        
        if (s1ap_usrsctp_bind(*new, sa) == CORE_OK)
        {
            d_trace(1, "s1ap_server %s:%d\n", CORE_NTOP(sa, buf), port);
            break;
        }

        rv = s1ap_delete(*new);
        d_assert(rv == CORE_OK, return CORE_ERROR,);

        sa = sa->next;
    }

    if (sa == NULL)
    {
        d_error("usrsctp bind(%d:%s:%d)", family, hostname, port);
        return CORE_ERROR;
    }

    rv = core_freeaddrinfo(sa);
    d_assert(rv == CORE_OK, return CORE_ERROR,);

    rv = s1ap_usrsctp_listen(*new);
    d_assert(rv == CORE_OK, return CORE_ERROR,);

    return CORE_OK;
}

status_t s1ap_client(sock_id *new,
        int family, int type, const char *hostname, c_uint16_t port)
{
    status_t rv;
    c_sockaddr_t *sa;
    char buf[CORE_ADDRSTRLEN];

    rv = core_getaddrinfo(&sa, family, hostname, port, 0);
    d_assert(rv == CORE_OK && sa, return CORE_ERROR,);

    while(sa)
    {
        rv = s1ap_usrsctp_socket(new, sa->c_sa_family, type, NULL);
        if (rv != CORE_OK) continue;
        
        if (s1ap_usrsctp_connect(*new, sa) == CORE_OK)
        {
            d_trace(1, "s1ap_client %s:%d\n", CORE_NTOP(sa, buf), port);
            break;
        }

        rv = s1ap_delete(*new);
        d_assert(rv == CORE_OK, return CORE_ERROR,);

        sa = sa->next;
    }

    if (sa == NULL)
    {
        d_error("s1ap_client(%d:%s:%d) failed", family, hostname, port);
        return CORE_ERROR;
    }

    rv = core_freeaddrinfo(sa);
    d_assert(rv == CORE_OK, return CORE_ERROR,);

    return CORE_OK;
}

status_t s1ap_open(void)
{
    status_t rv;
    int family = AF_INET;
    int type = SOCK_SEQPACKET;
    const char *hostname = NULL;
    c_uint16_t port = 36412;

    rv = s1ap_server(&mme_self()->s1ap_sock, family, type, hostname, port);
    if (rv != CORE_OK)
    {
        d_error("s1ap_server(%d:%d:%s:%d) failed",
                family, type, hostname, port);
        return CORE_ERROR;
    }
    
    return CORE_OK;
}

status_t s1ap_close()
{
    s1ap_delete(mme_self()->s1ap_sock);
    return CORE_OK;
}

status_t s1ap_delete(sock_id sock)
{
    d_assert(sock, return CORE_ERROR,);
    usrsctp_close((struct socket *)sock);
    return CORE_OK;
}

status_t s1ap_recv(sock_id id, pkbuf_t *pkbuf)
{
	struct socket *sock = (struct socket *)id;
	struct sockaddr_in addr;
	ssize_t n = 0;
	int flags = 0;
	socklen_t from_len;
	socklen_t infolen;
	struct sctp_rcvinfo rcv_info;
	unsigned int infotype = 0;

    while(1)
    {
        n = usrsctp_recvv(sock, pkbuf->payload, MAX_SDU_LEN,
                (struct sockaddr *)&addr, &from_len, (void *)&rcv_info,
                &infolen, &infotype, &flags);
        if (n > 0)
        {
#undef MSG_NOTIFICATION
#define MSG_NOTIFICATION 0x2000
            if (flags & MSG_NOTIFICATION)
            {
                /* Nothing to do */
            }
            else if (flags & MSG_EOR)
            {
                break;
            }
        }
    }

    pkbuf->len = n;
    return CORE_OK;
}

status_t s1ap_send(sock_id id, pkbuf_t *pkbuf, c_sockaddr_t *addr)
{
    ssize_t sent;
    struct socket *sock = (struct socket *)id;
    struct sctp_sndinfo sndinfo;

    d_assert(id, return CORE_ERROR, "Null param");
    d_assert(pkbuf, return CORE_ERROR, "Null param");

    memset((void *)&sndinfo, 0, sizeof(struct sctp_sndinfo));
    sndinfo.snd_ppid = htonl(SCTP_S1AP_PPID);
    sent = usrsctp_sendv(sock, pkbuf->payload, pkbuf->len, 
            addr ? &addr->sa : NULL, addr ? 1 : 0,
            (void *)&sndinfo, (socklen_t)sizeof(struct sctp_sndinfo),
            SCTP_SENDV_SNDINFO, 0);

    d_trace(10,"Sent %d->%d bytes\n", pkbuf->len, sent);
    d_trace_hex(10, pkbuf->payload, pkbuf->len);
    if (sent < 0 || sent != pkbuf->len)
    {
        d_error("sent : %d, pkbuf->len : %d\n", sent, pkbuf->len);
        return CORE_ERROR;
    }
    pkbuf_free(pkbuf);

    return CORE_OK;
}

static status_t s1ap_usrsctp_socket(sock_id *new,
    int family, int type,
    int (*receive_cb)(struct socket *sock, union sctp_sockstore addr,
        void *data, size_t datalen, struct sctp_rcvinfo, int flags,
        void *ulp_info))
{
    struct socket *sock = NULL;
    const int on = 1;
    struct sctp_event event;
    c_uint16_t event_types[] = {
        SCTP_ASSOC_CHANGE,
        SCTP_PEER_ADDR_CHANGE,
        SCTP_REMOTE_ERROR,
        SCTP_SHUTDOWN_EVENT,
        SCTP_ADAPTATION_INDICATION,
        SCTP_PARTIAL_DELIVERY_EVENT
    };
    int i;

    if (!(sock = usrsctp_socket(family, type, IPPROTO_SCTP,
            receive_cb, NULL, 0, NULL)))
    {
        d_error("usrsctp_socket failed");
        return CORE_ERROR;
    }

    if (usrsctp_setsockopt(sock, IPPROTO_SCTP, SCTP_RECVRCVINFO,
                &on, sizeof(int)) < 0)
    {
        d_error("usrsctp_setsockopt SCTP_RECVRCVINFO failed");
        return CORE_ERROR;
    }

    memset(&event, 0, sizeof(event));
    event.se_assoc_id = SCTP_FUTURE_ASSOC;
    event.se_on = 1;
    for (i = 0; i < (int)(sizeof(event_types)/sizeof(c_uint16_t)); i++)
    {
        event.se_type = event_types[i];
        if (usrsctp_setsockopt(sock, IPPROTO_SCTP, SCTP_EVENT,
                    &event, sizeof(struct sctp_event)) < 0)
        {
            d_error("usrsctp_setsockopt SCTP_EVENT failed");
            return CORE_ERROR;
        }
    }

    *new = (sock_id)sock;

    return CORE_OK;
}

static status_t s1ap_usrsctp_bind(sock_id id, c_sockaddr_t *sa)
{
    struct socket *sock = (struct socket *)id;
    char buf[CORE_ADDRSTRLEN];
    socklen_t addrlen;

    d_assert(sock, return CORE_ERROR,);
    d_assert(sa, return CORE_ERROR,);

    addrlen = sockaddr_len(sa);
    d_assert(addrlen, return CORE_ERROR,);

    if (usrsctp_bind(sock, &sa->sa, addrlen) != 0)
    {
        d_error("usrsctp_bind(%s:%d) failed",
                CORE_NTOP(sa, buf), CORE_PORT(sa));
        return CORE_ERROR;
    }

    d_trace(3, "usrsctp_bind %s:%d\n", CORE_NTOP(sa, buf), CORE_PORT(sa));

    return CORE_OK;
}

static status_t s1ap_usrsctp_connect(sock_id id, c_sockaddr_t *sa)
{
    struct socket *sock = (struct socket *)id;
    char buf[CORE_ADDRSTRLEN];
    socklen_t addrlen;

    d_assert(sock, return CORE_ERROR,);
    d_assert(sa, return CORE_ERROR,);

    addrlen = sockaddr_len(sa);
    d_assert(addrlen, return CORE_ERROR,);

    if (usrsctp_connect(sock, &sa->sa, addrlen) != 0)
    {
        d_error("usrsctp_connect(%s:%d)", CORE_NTOP(sa, buf), CORE_PORT(sa));
        return CORE_ERROR;
    }

    d_trace(3, "usrsctp_connect %s:%d\n", CORE_NTOP(sa, buf), CORE_PORT(sa));

    return CORE_OK;
}

static status_t s1ap_usrsctp_listen(sock_id id)
{
    int rc;
    struct socket *sock = (struct socket *)id;
    d_assert(sock, return CORE_ERROR,);

    rc = usrsctp_listen(sock, 5);
    if (rc < 0)
    {
        d_error("usrsctp_listen failed");
        return CORE_ERROR;
    }

    return CORE_OK;
}

static int s1ap_usrsctp_recv_cb(struct socket *sock,
    union sctp_sockstore addr, void *data, size_t datalen,
    struct sctp_rcvinfo rcv, int flags, void *ulp_info)
{
    if (data)
    {
        event_t e;

#undef MSG_NOTIFICATION
#define MSG_NOTIFICATION 0x2000
        if (flags & MSG_NOTIFICATION)
        {
            union sctp_notification *not = (union sctp_notification *)data;
            if (not->sn_header.sn_length == (c_uint32_t)datalen)
            {
                switch(not->sn_header.sn_type) 
                {
                    case SCTP_ASSOC_CHANGE :
                        d_trace(3, "SCTP_ASSOC_CHANGE"
                                "(type:0x%x, flags:0x%x, state:0x%x)\n", 
                                not->sn_assoc_change.sac_type,
                                not->sn_assoc_change.sac_flags,
                                not->sn_assoc_change.sac_state);

                        if (not->sn_assoc_change.sac_state == 
                                SCTP_SHUTDOWN_COMP ||
                            not->sn_assoc_change.sac_state == 
                                SCTP_COMM_LOST)
                        {
                            c_sockaddr_t *c_addr =
                                usrsctp_remote_addr(&addr);
                            d_assert(c_addr, return 1,);

                            event_set(&e, MME_EVT_S1AP_LO_CONNREFUSED);
                            event_set_param1(&e, (c_uintptr_t)sock);
                            event_set_param2(&e, (c_uintptr_t)c_addr);
                            if (mme_event_send(&e) != CORE_OK)
                            {
                                core_free(c_addr);
                            }
                        }
                        else if (not->sn_assoc_change.sac_state == SCTP_COMM_UP)
                        {
                            c_sockaddr_t *c_addr =
                                usrsctp_remote_addr(&addr);
                            d_assert(c_addr, return 1,);

                            event_set(&e, MME_EVT_S1AP_LO_ACCEPT);
                            event_set_param1(&e, (c_uintptr_t)sock);
                            event_set_param2(&e, (c_uintptr_t)c_addr);
                            if (mme_event_send(&e) != CORE_OK)
                            {
                                core_free(c_addr);
                            }
                        }

                        break;
                    case SCTP_PEER_ADDR_CHANGE:
                        break;
                    case SCTP_SEND_FAILED :
                        d_error("SCTP_SEND_FAILED"
                                "(type:0x%x, flags:0x%x, error:0x%x)\n", 
                                not->sn_send_failed_event.ssfe_type,
                                not->sn_send_failed_event.ssfe_flags,
                                not->sn_send_failed_event.ssfe_error);
                        break;
                    case SCTP_SHUTDOWN_EVENT :
                    {
                        c_sockaddr_t *c_addr = usrsctp_remote_addr(&addr);
                        d_assert(c_addr, return 1,);

                        event_set(&e, MME_EVT_S1AP_LO_CONNREFUSED);
                        event_set_param1(&e, (c_uintptr_t)sock);
                        event_set_param2(&e, (c_uintptr_t)c_addr);
                        if (mme_event_send(&e) != CORE_OK)
                        {
                            core_free(c_addr);
                        }
                        break;
                    }
                    default :
                        d_error("Discarding event with unknown "
                                "flags = 0x%x, type 0x%x", 
                                flags, not->sn_header.sn_type);
                        break;
                }
            }
        }
        else if (flags & MSG_EOR)
        {
            pkbuf_t *pkbuf;
            c_sockaddr_t *c_addr = NULL;

            pkbuf = pkbuf_alloc(0, MAX_SDU_LEN);
            d_assert(pkbuf, return 1, );
            c_addr = usrsctp_remote_addr(&addr);
            d_assert(c_addr, return 1,);

            pkbuf->len = datalen;
            memcpy(pkbuf->payload, data, pkbuf->len);

            event_set(&e, MME_EVT_S1AP_MESSAGE);
            event_set_param1(&e, (c_uintptr_t)sock);
            event_set_param2(&e, (c_uintptr_t)c_addr);
            event_set_param3(&e, (c_uintptr_t)pkbuf);
            if (mme_event_send(&e) != CORE_OK)
            {
                pkbuf_free(pkbuf);
                core_free(c_addr);
            }
        }
        else
        {
            d_error("Not engough buffer. Need more recv : 0x%x", flags);
        }
        free(data);
    }
    return (1);
}

static c_sockaddr_t *usrsctp_remote_addr(union sctp_sockstore *store)
{
    c_sockaddr_t *addr = NULL;

    d_assert(store, return NULL,);

    addr = core_calloc(1, sizeof(c_sockaddr_t));
    d_assert(addr, return NULL,);

    addr->c_sa_family = store->sin.sin_family;
    switch(addr->c_sa_family)
    {
        case AF_INET:
            memcpy(&addr->sin, &store->sin, sizeof(struct sockaddr_in));
            break;
        case AF_INET6:
            memcpy(&addr->sin6, &store->sin6, sizeof(struct sockaddr_in6));
            break;
        default:
            d_assert(0, return NULL,);
    }

    return addr;
}

static void debug_printf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}
