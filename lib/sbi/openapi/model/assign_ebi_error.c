
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "assign_ebi_error.h"

OpenAPI_assign_ebi_error_t *OpenAPI_assign_ebi_error_create(
    OpenAPI_problem_details_t *error,
    OpenAPI_assign_ebi_failed_t *failure_details
)
{
    OpenAPI_assign_ebi_error_t *assign_ebi_error_local_var = ogs_malloc(sizeof(OpenAPI_assign_ebi_error_t));
    ogs_assert(assign_ebi_error_local_var);

    assign_ebi_error_local_var->error = error;
    assign_ebi_error_local_var->failure_details = failure_details;

    return assign_ebi_error_local_var;
}

void OpenAPI_assign_ebi_error_free(OpenAPI_assign_ebi_error_t *assign_ebi_error)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == assign_ebi_error) {
        return;
    }
    if (assign_ebi_error->error) {
        OpenAPI_problem_details_free(assign_ebi_error->error);
        assign_ebi_error->error = NULL;
    }
    if (assign_ebi_error->failure_details) {
        OpenAPI_assign_ebi_failed_free(assign_ebi_error->failure_details);
        assign_ebi_error->failure_details = NULL;
    }
    ogs_free(assign_ebi_error);
}

cJSON *OpenAPI_assign_ebi_error_convertToJSON(OpenAPI_assign_ebi_error_t *assign_ebi_error)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (assign_ebi_error == NULL) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed [AssignEbiError]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!assign_ebi_error->error) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed [error]");
        return NULL;
    }
    cJSON *error_local_JSON = OpenAPI_problem_details_convertToJSON(assign_ebi_error->error);
    if (error_local_JSON == NULL) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed [error]");
        goto end;
    }
    cJSON_AddItemToObject(item, "error", error_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed [error]");
        goto end;
    }

    if (!assign_ebi_error->failure_details) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed [failure_details]");
        return NULL;
    }
    cJSON *failure_details_local_JSON = OpenAPI_assign_ebi_failed_convertToJSON(assign_ebi_error->failure_details);
    if (failure_details_local_JSON == NULL) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed [failure_details]");
        goto end;
    }
    cJSON_AddItemToObject(item, "failureDetails", failure_details_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed [failure_details]");
        goto end;
    }

end:
    return item;
}

OpenAPI_assign_ebi_error_t *OpenAPI_assign_ebi_error_parseFromJSON(cJSON *assign_ebi_errorJSON)
{
    OpenAPI_assign_ebi_error_t *assign_ebi_error_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *error = NULL;
    OpenAPI_problem_details_t *error_local_nonprim = NULL;
    cJSON *failure_details = NULL;
    OpenAPI_assign_ebi_failed_t *failure_details_local_nonprim = NULL;
    error = cJSON_GetObjectItemCaseSensitive(assign_ebi_errorJSON, "error");
    if (!error) {
        ogs_error("OpenAPI_assign_ebi_error_parseFromJSON() failed [error]");
        goto end;
    }
    error_local_nonprim = OpenAPI_problem_details_parseFromJSON(error);
    if (!error_local_nonprim) {
        ogs_error("OpenAPI_problem_details_parseFromJSON failed [error]");
        goto end;
    }

    failure_details = cJSON_GetObjectItemCaseSensitive(assign_ebi_errorJSON, "failureDetails");
    if (!failure_details) {
        ogs_error("OpenAPI_assign_ebi_error_parseFromJSON() failed [failure_details]");
        goto end;
    }
    failure_details_local_nonprim = OpenAPI_assign_ebi_failed_parseFromJSON(failure_details);
    if (!failure_details_local_nonprim) {
        ogs_error("OpenAPI_assign_ebi_failed_parseFromJSON failed [failure_details]");
        goto end;
    }

    assign_ebi_error_local_var = OpenAPI_assign_ebi_error_create (
        error_local_nonprim,
        failure_details_local_nonprim
    );

    return assign_ebi_error_local_var;
end:
    if (error_local_nonprim) {
        OpenAPI_problem_details_free(error_local_nonprim);
        error_local_nonprim = NULL;
    }
    if (failure_details_local_nonprim) {
        OpenAPI_assign_ebi_failed_free(failure_details_local_nonprim);
        failure_details_local_nonprim = NULL;
    }
    return NULL;
}

OpenAPI_assign_ebi_error_t *OpenAPI_assign_ebi_error_copy(OpenAPI_assign_ebi_error_t *dst, OpenAPI_assign_ebi_error_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_assign_ebi_error_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_assign_ebi_error_convertToJSON() failed");
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

    OpenAPI_assign_ebi_error_free(dst);
    dst = OpenAPI_assign_ebi_error_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

