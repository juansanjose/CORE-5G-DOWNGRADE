
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "secondary_rat_usage_info.h"

OpenAPI_secondary_rat_usage_info_t *OpenAPI_secondary_rat_usage_info_create(
    OpenAPI_rat_type_e secondary_rat_type,
    OpenAPI_list_t *qos_flows_usage_data,
    OpenAPI_list_t *pdu_session_usage_data
)
{
    OpenAPI_secondary_rat_usage_info_t *secondary_rat_usage_info_local_var = ogs_malloc(sizeof(OpenAPI_secondary_rat_usage_info_t));
    ogs_assert(secondary_rat_usage_info_local_var);

    secondary_rat_usage_info_local_var->secondary_rat_type = secondary_rat_type;
    secondary_rat_usage_info_local_var->qos_flows_usage_data = qos_flows_usage_data;
    secondary_rat_usage_info_local_var->pdu_session_usage_data = pdu_session_usage_data;

    return secondary_rat_usage_info_local_var;
}

void OpenAPI_secondary_rat_usage_info_free(OpenAPI_secondary_rat_usage_info_t *secondary_rat_usage_info)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == secondary_rat_usage_info) {
        return;
    }
    if (secondary_rat_usage_info->qos_flows_usage_data) {
        OpenAPI_list_for_each(secondary_rat_usage_info->qos_flows_usage_data, node) {
            OpenAPI_qos_flow_usage_report_free(node->data);
        }
        OpenAPI_list_free(secondary_rat_usage_info->qos_flows_usage_data);
        secondary_rat_usage_info->qos_flows_usage_data = NULL;
    }
    if (secondary_rat_usage_info->pdu_session_usage_data) {
        OpenAPI_list_for_each(secondary_rat_usage_info->pdu_session_usage_data, node) {
            OpenAPI_volume_timed_report_free(node->data);
        }
        OpenAPI_list_free(secondary_rat_usage_info->pdu_session_usage_data);
        secondary_rat_usage_info->pdu_session_usage_data = NULL;
    }
    ogs_free(secondary_rat_usage_info);
}

cJSON *OpenAPI_secondary_rat_usage_info_convertToJSON(OpenAPI_secondary_rat_usage_info_t *secondary_rat_usage_info)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (secondary_rat_usage_info == NULL) {
        ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed [SecondaryRatUsageInfo]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (secondary_rat_usage_info->secondary_rat_type == OpenAPI_rat_type_NULL) {
        ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed [secondary_rat_type]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "secondaryRatType", OpenAPI_rat_type_ToString(secondary_rat_usage_info->secondary_rat_type)) == NULL) {
        ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed [secondary_rat_type]");
        goto end;
    }

    if (secondary_rat_usage_info->qos_flows_usage_data) {
    cJSON *qos_flows_usage_dataList = cJSON_AddArrayToObject(item, "qosFlowsUsageData");
    if (qos_flows_usage_dataList == NULL) {
        ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed [qos_flows_usage_data]");
        goto end;
    }
    OpenAPI_list_for_each(secondary_rat_usage_info->qos_flows_usage_data, node) {
        cJSON *itemLocal = OpenAPI_qos_flow_usage_report_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed [qos_flows_usage_data]");
            goto end;
        }
        cJSON_AddItemToArray(qos_flows_usage_dataList, itemLocal);
    }
    }

    if (secondary_rat_usage_info->pdu_session_usage_data) {
    cJSON *pdu_session_usage_dataList = cJSON_AddArrayToObject(item, "pduSessionUsageData");
    if (pdu_session_usage_dataList == NULL) {
        ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed [pdu_session_usage_data]");
        goto end;
    }
    OpenAPI_list_for_each(secondary_rat_usage_info->pdu_session_usage_data, node) {
        cJSON *itemLocal = OpenAPI_volume_timed_report_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed [pdu_session_usage_data]");
            goto end;
        }
        cJSON_AddItemToArray(pdu_session_usage_dataList, itemLocal);
    }
    }

end:
    return item;
}

OpenAPI_secondary_rat_usage_info_t *OpenAPI_secondary_rat_usage_info_parseFromJSON(cJSON *secondary_rat_usage_infoJSON)
{
    OpenAPI_secondary_rat_usage_info_t *secondary_rat_usage_info_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *secondary_rat_type = NULL;
    OpenAPI_rat_type_e secondary_rat_typeVariable = 0;
    cJSON *qos_flows_usage_data = NULL;
    OpenAPI_list_t *qos_flows_usage_dataList = NULL;
    cJSON *pdu_session_usage_data = NULL;
    OpenAPI_list_t *pdu_session_usage_dataList = NULL;
    secondary_rat_type = cJSON_GetObjectItemCaseSensitive(secondary_rat_usage_infoJSON, "secondaryRatType");
    if (!secondary_rat_type) {
        ogs_error("OpenAPI_secondary_rat_usage_info_parseFromJSON() failed [secondary_rat_type]");
        goto end;
    }
    if (!cJSON_IsString(secondary_rat_type)) {
        ogs_error("OpenAPI_secondary_rat_usage_info_parseFromJSON() failed [secondary_rat_type]");
        goto end;
    }
    secondary_rat_typeVariable = OpenAPI_rat_type_FromString(secondary_rat_type->valuestring);

    qos_flows_usage_data = cJSON_GetObjectItemCaseSensitive(secondary_rat_usage_infoJSON, "qosFlowsUsageData");
    if (qos_flows_usage_data) {
        cJSON *qos_flows_usage_data_local = NULL;
        if (!cJSON_IsArray(qos_flows_usage_data)) {
            ogs_error("OpenAPI_secondary_rat_usage_info_parseFromJSON() failed [qos_flows_usage_data]");
            goto end;
        }

        qos_flows_usage_dataList = OpenAPI_list_create();

        cJSON_ArrayForEach(qos_flows_usage_data_local, qos_flows_usage_data) {
            if (!cJSON_IsObject(qos_flows_usage_data_local)) {
                ogs_error("OpenAPI_secondary_rat_usage_info_parseFromJSON() failed [qos_flows_usage_data]");
                goto end;
            }
            OpenAPI_qos_flow_usage_report_t *qos_flows_usage_dataItem = OpenAPI_qos_flow_usage_report_parseFromJSON(qos_flows_usage_data_local);
            if (!qos_flows_usage_dataItem) {
                ogs_error("No qos_flows_usage_dataItem");
                goto end;
            }
            OpenAPI_list_add(qos_flows_usage_dataList, qos_flows_usage_dataItem);
        }
    }

    pdu_session_usage_data = cJSON_GetObjectItemCaseSensitive(secondary_rat_usage_infoJSON, "pduSessionUsageData");
    if (pdu_session_usage_data) {
        cJSON *pdu_session_usage_data_local = NULL;
        if (!cJSON_IsArray(pdu_session_usage_data)) {
            ogs_error("OpenAPI_secondary_rat_usage_info_parseFromJSON() failed [pdu_session_usage_data]");
            goto end;
        }

        pdu_session_usage_dataList = OpenAPI_list_create();

        cJSON_ArrayForEach(pdu_session_usage_data_local, pdu_session_usage_data) {
            if (!cJSON_IsObject(pdu_session_usage_data_local)) {
                ogs_error("OpenAPI_secondary_rat_usage_info_parseFromJSON() failed [pdu_session_usage_data]");
                goto end;
            }
            OpenAPI_volume_timed_report_t *pdu_session_usage_dataItem = OpenAPI_volume_timed_report_parseFromJSON(pdu_session_usage_data_local);
            if (!pdu_session_usage_dataItem) {
                ogs_error("No pdu_session_usage_dataItem");
                goto end;
            }
            OpenAPI_list_add(pdu_session_usage_dataList, pdu_session_usage_dataItem);
        }
    }

    secondary_rat_usage_info_local_var = OpenAPI_secondary_rat_usage_info_create (
        secondary_rat_typeVariable,
        qos_flows_usage_data ? qos_flows_usage_dataList : NULL,
        pdu_session_usage_data ? pdu_session_usage_dataList : NULL
    );

    return secondary_rat_usage_info_local_var;
end:
    if (qos_flows_usage_dataList) {
        OpenAPI_list_for_each(qos_flows_usage_dataList, node) {
            OpenAPI_qos_flow_usage_report_free(node->data);
        }
        OpenAPI_list_free(qos_flows_usage_dataList);
        qos_flows_usage_dataList = NULL;
    }
    if (pdu_session_usage_dataList) {
        OpenAPI_list_for_each(pdu_session_usage_dataList, node) {
            OpenAPI_volume_timed_report_free(node->data);
        }
        OpenAPI_list_free(pdu_session_usage_dataList);
        pdu_session_usage_dataList = NULL;
    }
    return NULL;
}

OpenAPI_secondary_rat_usage_info_t *OpenAPI_secondary_rat_usage_info_copy(OpenAPI_secondary_rat_usage_info_t *dst, OpenAPI_secondary_rat_usage_info_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_secondary_rat_usage_info_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_secondary_rat_usage_info_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_secondary_rat_usage_info_free(dst);
    dst = OpenAPI_secondary_rat_usage_info_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

