/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef NRF_NNRF_HANDLER_H
#define NRF_NNRF_HANDLER_H

#include "ogs-sbi.h"
#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

bool nrf_nnrf_handle_nf_register(ogs_sbi_nf_instance_t *nf_instance,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);
bool nrf_nnrf_handle_nf_update(ogs_sbi_nf_instance_t *nf_instance,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);

bool nrf_nnrf_handle_nf_status_subscribe(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);
bool nrf_nnrf_handle_nf_status_update(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);
bool nrf_nnrf_handle_nf_status_unsubscribe(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);

bool nrf_nnrf_handle_nf_list_retrieval(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);
bool nrf_nnrf_handle_nf_profile_retrieval(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);

bool nrf_nnrf_handle_nf_discover(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);

#ifdef __cplusplus
}
#endif

#endif /* NRF_NNRF_HANDLER_H */
