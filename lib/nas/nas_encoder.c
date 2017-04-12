/*
 * Copyright (c) 2017, CellWire Group
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
 * This file had been created by gtpv2c_tlv.py script v0.1.0
 * Please do not modify this file but regenerate it via script.
 * Created on: 2017-04-12 23:01:20.722247 by acetcom
 * from 24301-d80.docx
 ******************************************************************************/

#define TRACE_MODULE _nasenc

#include "core_debug.h"
#include "nas_message.h"

c_int32_t nas_encode_attach_request(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_attach_request_t *attach_request = &message->emm.attach_request;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_eps_attach_type(pkbuf, &attach_request->eps_attach_type);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_eps_mobile_identity(pkbuf, &attach_request->eps_mobile_identity);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_ue_network_capability(pkbuf, &attach_request->ue_network_capability);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_esm_message_container(pkbuf, &attach_request->esm_message_container);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_OLD_P_TMSI_SIGNATURE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_OLD_P_TMSI_SIGNATURE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_p_tmsi_signature(pkbuf, &attach_request->old_p_tmsi_signature);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_ADDITIONAL_GUTI_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_ADDITIONAL_GUTI_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_eps_mobile_identity(pkbuf, &attach_request->additional_guti);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_LAST_VISITED_REGISTERED_TAI_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_LAST_VISITED_REGISTERED_TAI_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_tracking_area_identity(pkbuf, &attach_request->last_visited_registered_tai);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_DRX_PARAMETER_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_DRX_PARAMETER_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_drx_parameter(pkbuf, &attach_request->drx_parameter);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_MS_NETWORK_CAPABILITY_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_MS_NETWORK_CAPABILITY_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_ms_network_capability(pkbuf, &attach_request->ms_network_capability);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_OLD_LOCATION_AREA_IDENTIFICATION_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_OLD_LOCATION_AREA_IDENTIFICATION_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_location_area_identification(pkbuf, &attach_request->old_location_area_identification);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_TMSI_STATUS_PRESENT)
    {
        attach_request->tmsi_status.type = (NAS_ATTACH_REQUEST_TMSI_STATUS_TYPE >> 4);

        size = nas_encode_tmsi_status(pkbuf, &attach_request->tmsi_status);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_2_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_2_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_mobile_station_classmark_2(pkbuf, &attach_request->mobile_station_classmark_2);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_3_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_3_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_mobile_station_classmark_3(pkbuf, &attach_request->mobile_station_classmark_3);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_SUPPORTED_CODECS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_SUPPORTED_CODECS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_supported_codec_list(pkbuf, &attach_request->supported_codecs);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_ADDITIONAL_UPDATE_TYPE_PRESENT)
    {
        attach_request->additional_update_type.type = (NAS_ATTACH_REQUEST_ADDITIONAL_UPDATE_TYPE_TYPE >> 4);

        size = nas_encode_additional_update_type(pkbuf, &attach_request->additional_update_type);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_VOICE_DOMAIN_PREFERENCE_AND_UE_USAGE_SETTING_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_VOICE_DOMAIN_PREFERENCE_AND_UE_USAGE_SETTING_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_voice_domain_preference_and_ue_usage_setting(pkbuf, &attach_request->voice_domain_preference_and_ue_usage_setting);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_DEVICE_PROPERTIES_PRESENT)
    {
        attach_request->device_properties.type = (NAS_ATTACH_REQUEST_DEVICE_PROPERTIES_TYPE >> 4);

        size = nas_encode_device_properties(pkbuf, &attach_request->device_properties);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_OLD_GUTI_TYPE_PRESENT)
    {
        attach_request->old_guti_type.type = (NAS_ATTACH_REQUEST_OLD_GUTI_TYPE_TYPE >> 4);

        size = nas_encode_guti_type(pkbuf, &attach_request->old_guti_type);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_MS_NETWORK_FEATURE_SUPPORT_PRESENT)
    {
        attach_request->ms_network_feature_support.type = (NAS_ATTACH_REQUEST_MS_NETWORK_FEATURE_SUPPORT_TYPE >> 4);

        size = nas_encode_ms_network_feature_support(pkbuf, &attach_request->ms_network_feature_support);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_TMSI_BASED_NRI_CONTAINER_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_TMSI_BASED_NRI_CONTAINER_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_network_resource_identifier_container(pkbuf, &attach_request->tmsi_based_nri_container);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_T3324_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_T3324_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer_2(pkbuf, &attach_request->t3324_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_T3412_EXTENDED_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_T3412_EXTENDED_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer_3(pkbuf, &attach_request->t3412_extended_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_request->presencemask & NAS_ATTACH_REQUEST_EXTENDED_DRX_PARAMETERS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REQUEST_EXTENDED_DRX_PARAMETERS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_extended_drx_parameters(pkbuf, &attach_request->extended_drx_parameters);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_attach_accept(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_attach_accept_t *attach_accept = &message->emm.attach_accept;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_eps_attach_result(pkbuf, &attach_accept->eps_attach_result);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_gprs_timer(pkbuf, &attach_accept->t3412_value);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_tracking_area_identity_list(pkbuf, &attach_accept->tai_list);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_esm_message_container(pkbuf, &attach_accept->esm_message_container);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_GUTI_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_GUTI_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_eps_mobile_identity(pkbuf, &attach_accept->guti);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_LOCATION_AREA_IDENTIFICATION_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_LOCATION_AREA_IDENTIFICATION_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_location_area_identification(pkbuf, &attach_accept->location_area_identification);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_MS_IDENTITY_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_MS_IDENTITY_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_mobile_identity(pkbuf, &attach_accept->ms_identity);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_EMM_CAUSE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_EMM_CAUSE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_emm_cause(pkbuf, &attach_accept->emm_cause);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_T3402_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_T3402_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer(pkbuf, &attach_accept->t3402_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_T3423_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_T3423_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer(pkbuf, &attach_accept->t3423_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_EQUIVALENT_PLMNS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_EQUIVALENT_PLMNS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_plmn_list(pkbuf, &attach_accept->equivalent_plmns);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_EMERGENCY_NUMBER_LIST_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_EMERGENCY_NUMBER_LIST_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_emergency_number_list(pkbuf, &attach_accept->emergency_number_list);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_eps_network_feature_support(pkbuf, &attach_accept->eps_network_feature_support);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_ADDITIONAL_UPDATE_RESULT_PRESENT)
    {
        attach_accept->additional_update_result.type = (NAS_ATTACH_ACCEPT_ADDITIONAL_UPDATE_RESULT_TYPE >> 4);

        size = nas_encode_additional_update_result(pkbuf, &attach_accept->additional_update_result);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_T3412_EXTENDED_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_T3412_EXTENDED_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer_3(pkbuf, &attach_accept->t3412_extended_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_T3324_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_T3324_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer_2(pkbuf, &attach_accept->t3324_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_accept->presencemask & NAS_ATTACH_ACCEPT_EXTENDED_DRX_PARAMETERS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_ACCEPT_EXTENDED_DRX_PARAMETERS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_extended_drx_parameters(pkbuf, &attach_accept->extended_drx_parameters);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_attach_complete(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_attach_complete_t *attach_complete = &message->emm.attach_complete;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_esm_message_container(pkbuf, &attach_complete->esm_message_container);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    return encoded;
}

c_int32_t nas_encode_attach_reject(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_attach_reject_t *attach_reject = &message->emm.attach_reject;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_emm_cause(pkbuf, &attach_reject->emm_cause);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (attach_reject->presencemask & NAS_ATTACH_REJECT_ESM_MESSAGE_CONTAINER_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REJECT_ESM_MESSAGE_CONTAINER_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_esm_message_container(pkbuf, &attach_reject->esm_message_container);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_reject->presencemask & NAS_ATTACH_REJECT_T3346_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REJECT_T3346_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer_2(pkbuf, &attach_reject->t3346_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_reject->presencemask & NAS_ATTACH_REJECT_T3402_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ATTACH_REJECT_T3402_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer_2(pkbuf, &attach_reject->t3402_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (attach_reject->presencemask & NAS_ATTACH_REJECT_EXTENDED_EMM_CAUSE_PRESENT)
    {
        attach_reject->extended_emm_cause.type = (NAS_ATTACH_REJECT_EXTENDED_EMM_CAUSE_TYPE >> 4);

        size = nas_encode_extended_emm_cause(pkbuf, &attach_reject->extended_emm_cause);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_authentication_request(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_authentication_request_t *authentication_request = &message->emm.authentication_request;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_key_set_identifier(pkbuf, &authentication_request->nas_key_set_identifierasme);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_authentication_parameter_rand(pkbuf, &authentication_request->authentication_parameter_rand);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_authentication_parameter_autn(pkbuf, &authentication_request->authentication_parameter_autn);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    return encoded;
}

c_int32_t nas_encode_authentication_response(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_authentication_response_t *authentication_response = &message->emm.authentication_response;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_authentication_response_parameter(pkbuf, &authentication_response->authentication_response_parameter);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    return encoded;
}

c_int32_t nas_encode_identity_request(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_identity_request_t *identity_request = &message->emm.identity_request;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_identity_type_2(pkbuf, &identity_request->identity_type);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    return encoded;
}

c_int32_t nas_encode_identity_response(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_identity_response_t *identity_response = &message->emm.identity_response;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_mobile_identity(pkbuf, &identity_response->mobile_identity);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    return encoded;
}

c_int32_t nas_encode_authentication_failure(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_authentication_failure_t *authentication_failure = &message->emm.authentication_failure;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_emm_cause(pkbuf, &authentication_failure->emm_cause);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (authentication_failure->presencemask & NAS_AUTHENTICATION_FAILURE_AUTHENTICATION_FAILURE_PARAMETER_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_AUTHENTICATION_FAILURE_AUTHENTICATION_FAILURE_PARAMETER_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_authentication_failure_parameter(pkbuf, &authentication_failure->authentication_failure_parameter);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_security_mode_command(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_security_mode_command_t *security_mode_command = &message->emm.security_mode_command;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_security_algorithms(pkbuf, &security_mode_command->selected_nas_security_algorithms);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_key_set_identifier(pkbuf, &security_mode_command->nas_key_set_identifier);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    size = nas_encode_ue_security_capability(pkbuf, &security_mode_command->replayed_ue_security_capabilities);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (security_mode_command->presencemask & NAS_SECURITY_MODE_COMMAND_IMEISV_REQUEST_PRESENT)
    {
        security_mode_command->imeisv_request.type = (NAS_SECURITY_MODE_COMMAND_IMEISV_REQUEST_TYPE >> 4);

        size = nas_encode_imeisv_request(pkbuf, &security_mode_command->imeisv_request);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (security_mode_command->presencemask & NAS_SECURITY_MODE_COMMAND_REPLAYED_NONCEUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_SECURITY_MODE_COMMAND_REPLAYED_NONCEUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_nonce(pkbuf, &security_mode_command->replayed_nonceue);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (security_mode_command->presencemask & NAS_SECURITY_MODE_COMMAND_NONCEMME_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_SECURITY_MODE_COMMAND_NONCEMME_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_nonce(pkbuf, &security_mode_command->noncemme);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_security_mode_complete(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_security_mode_complete_t *security_mode_complete = &message->emm.security_mode_complete;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    if (security_mode_complete->presencemask & NAS_SECURITY_MODE_COMPLETE_IMEISV_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_SECURITY_MODE_COMPLETE_IMEISV_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_mobile_identity(pkbuf, &security_mode_complete->imeisv);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_security_mode_reject(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_security_mode_reject_t *security_mode_reject = &message->emm.security_mode_reject;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_emm_cause(pkbuf, &security_mode_reject->emm_cause);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    return encoded;
}

c_int32_t nas_encode_pdn_connectivity_request(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_pdn_connectivity_request_t *pdn_connectivity_request = &message->esm.pdn_connectivity_request;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_request_type(pkbuf, &pdn_connectivity_request->request_type);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (pdn_connectivity_request->presencemask & NAS_PDN_CONNECTIVITY_REQUEST_ESM_INFORMATION_TRANSFER_FLAG_PRESENT)
    {
        pdn_connectivity_request->esm_information_transfer_flag.type = (NAS_PDN_CONNECTIVITY_REQUEST_ESM_INFORMATION_TRANSFER_FLAG_TYPE >> 4);

        size = nas_encode_esm_information_transfer_flag(pkbuf, &pdn_connectivity_request->esm_information_transfer_flag);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_request->presencemask & NAS_PDN_CONNECTIVITY_REQUEST_ACCESS_POINT_NAME_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REQUEST_ACCESS_POINT_NAME_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_access_point_name(pkbuf, &pdn_connectivity_request->access_point_name);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_request->presencemask & NAS_PDN_CONNECTIVITY_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_protocol_configuration_options(pkbuf, &pdn_connectivity_request->protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_request->presencemask & NAS_PDN_CONNECTIVITY_REQUEST_DEVICE_PROPERTIES_PRESENT)
    {
        pdn_connectivity_request->device_properties.type = (NAS_PDN_CONNECTIVITY_REQUEST_DEVICE_PROPERTIES_TYPE >> 4);

        size = nas_encode_device_properties(pkbuf, &pdn_connectivity_request->device_properties);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_request->presencemask & NAS_PDN_CONNECTIVITY_REQUEST_NBIFOM_CONTAINER_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REQUEST_NBIFOM_CONTAINER_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_nbifom_container(pkbuf, &pdn_connectivity_request->nbifom_container);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_request->presencemask & NAS_PDN_CONNECTIVITY_REQUEST_HEADER_COMPRESSION_CONFIGURATION_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REQUEST_HEADER_COMPRESSION_CONFIGURATION_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_header_compression_configuration(pkbuf, &pdn_connectivity_request->header_compression_configuration);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_request->presencemask & NAS_PDN_CONNECTIVITY_REQUEST_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REQUEST_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_extended_protocol_configuration_options(pkbuf, &pdn_connectivity_request->extended_protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_pdn_connectivity_reject(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_pdn_connectivity_reject_t *pdn_connectivity_reject = &message->esm.pdn_connectivity_reject;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_esm_cause(pkbuf, &pdn_connectivity_reject->esm_cause);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (pdn_connectivity_reject->presencemask & NAS_PDN_CONNECTIVITY_REJECT_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REJECT_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_protocol_configuration_options(pkbuf, &pdn_connectivity_reject->protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_reject->presencemask & NAS_PDN_CONNECTIVITY_REJECT_BACK_OFF_TIMER_VALUE_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REJECT_BACK_OFF_TIMER_VALUE_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_gprs_timer_3(pkbuf, &pdn_connectivity_reject->back_off_timer_value);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_reject->presencemask & NAS_PDN_CONNECTIVITY_REJECT_RE_ATTEMPT_INDICATOR_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REJECT_RE_ATTEMPT_INDICATOR_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_re_attempt_indicator(pkbuf, &pdn_connectivity_reject->re_attempt_indicator);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_reject->presencemask & NAS_PDN_CONNECTIVITY_REJECT_NBIFOM_CONTAINER_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REJECT_NBIFOM_CONTAINER_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_nbifom_container(pkbuf, &pdn_connectivity_reject->nbifom_container);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_connectivity_reject->presencemask & NAS_PDN_CONNECTIVITY_REJECT_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_CONNECTIVITY_REJECT_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_extended_protocol_configuration_options(pkbuf, &pdn_connectivity_reject->extended_protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_pdn_disconnect_request(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_pdn_disconnect_request_t *pdn_disconnect_request = &message->esm.pdn_disconnect_request;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_linked_eps_bearer_identity(pkbuf, &pdn_disconnect_request->linked_eps_bearer_identity);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (pdn_disconnect_request->presencemask & NAS_PDN_DISCONNECT_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_DISCONNECT_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_protocol_configuration_options(pkbuf, &pdn_disconnect_request->protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_disconnect_request->presencemask & NAS_PDN_DISCONNECT_REQUEST_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_DISCONNECT_REQUEST_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_extended_protocol_configuration_options(pkbuf, &pdn_disconnect_request->extended_protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_pdn_disconnect_reject(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_pdn_disconnect_reject_t *pdn_disconnect_reject = &message->esm.pdn_disconnect_reject;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    size = nas_encode_esm_cause(pkbuf, &pdn_disconnect_reject->esm_cause);
    d_assert(size >= 0, return -1, "encode failed");
    encoded += size;

    if (pdn_disconnect_reject->presencemask & NAS_PDN_DISCONNECT_REJECT_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_DISCONNECT_REJECT_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_protocol_configuration_options(pkbuf, &pdn_disconnect_reject->protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (pdn_disconnect_reject->presencemask & NAS_PDN_DISCONNECT_REJECT_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_PDN_DISCONNECT_REJECT_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_extended_protocol_configuration_options(pkbuf, &pdn_disconnect_reject->extended_protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

c_int32_t nas_encode_esm_information_response(pkbuf_t *pkbuf, nas_message_t *message)
{
    nas_esm_information_response_t *esm_information_response = &message->esm.esm_information_response;
    c_int32_t encoded = 0;
    c_int32_t size = 0;

    if (esm_information_response->presencemask & NAS_ESM_INFORMATION_RESPONSE_ACCESS_POINT_NAME_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ESM_INFORMATION_RESPONSE_ACCESS_POINT_NAME_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_access_point_name(pkbuf, &esm_information_response->access_point_name);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (esm_information_response->presencemask & NAS_ESM_INFORMATION_RESPONSE_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ESM_INFORMATION_RESPONSE_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_protocol_configuration_options(pkbuf, &esm_information_response->protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    if (esm_information_response->presencemask & NAS_ESM_INFORMATION_RESPONSE_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
    {
        size = nas_encode_optional_type(pkbuf, NAS_ESM_INFORMATION_RESPONSE_EXTENDED_PROTOCOL_CONFIGURATION_OPTIONS_TYPE);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;

        size = nas_encode_extended_protocol_configuration_options(pkbuf, &esm_information_response->extended_protocol_configuration_options);
        d_assert(size >= 0, return encoded, "decode failed");
        encoded += size;
    }

    return encoded;
}

status_t nas_emm_encode(pkbuf_t **pkbuf, nas_message_t *message)
{
    status_t rv = CORE_ERROR;
    c_int32_t size = 0;
    c_int32_t encoded = 0;

    d_assert(message, return CORE_ERROR, "Null param");

    /* The Packet Buffer(pkbuf_t) for NAS message MUST make a HEADROOM. 
     * When calculating AES_CMAC, we need to use the headroom of the packet. */
    *pkbuf = pkbuf_alloc(NAS_HEADROOM, MAX_SDU_LEN);
    d_assert(*pkbuf, return -1, "Null Param");

    size = sizeof(nas_emm_header_t);
    rv = pkbuf_header(*pkbuf, -size);
    d_assert(rv == CORE_OK, return CORE_ERROR, "pkbuf_header error");

    memcpy((*pkbuf)->payload - size, &message->emm.h, size);
    encoded += size;

    switch(message->emm.h.message_type)
    {
        case NAS_ATTACH_REQUEST:
            size = nas_encode_attach_request(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_ATTACH_ACCEPT:
            size = nas_encode_attach_accept(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_ATTACH_COMPLETE:
            size = nas_encode_attach_complete(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_ATTACH_REJECT:
            size = nas_encode_attach_reject(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_AUTHENTICATION_REQUEST:
            size = nas_encode_authentication_request(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_AUTHENTICATION_RESPONSE:
            size = nas_encode_authentication_response(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_AUTHENTICATION_REJECT:
            break;
        case NAS_IDENTITY_REQUEST:
            size = nas_encode_identity_request(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_IDENTITY_RESPONSE:
            size = nas_encode_identity_response(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_AUTHENTICATION_FAILURE:
            size = nas_encode_authentication_failure(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_SECURITY_MODE_COMMAND:
            size = nas_encode_security_mode_command(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_SECURITY_MODE_COMPLETE:
            size = nas_encode_security_mode_complete(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_SECURITY_MODE_REJECT:
            size = nas_encode_security_mode_reject(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        default:
            d_error("Unknown message type (0x%x) or not implemented", 
                    message->emm.h.message_type);
            pkbuf_free((*pkbuf));
            return CORE_ERROR;
    }

    rv = pkbuf_header(*pkbuf, encoded);
    d_assert(rv == CORE_OK, return CORE_ERROR, "pkbuf_header error");

    (*pkbuf)->len = encoded;

    return CORE_OK;
}

status_t nas_esm_encode(pkbuf_t **pkbuf, nas_message_t *message)
{
    status_t rv = CORE_ERROR;
    c_int32_t size = 0;
    c_int32_t encoded = 0;

    d_assert(message, return CORE_ERROR, "Null param");

    /* The Packet Buffer(pkbuf_t) for NAS message MUST make a HEADROOM. 
     * When calculating AES_CMAC, we need to use the headroom of the packet. */
    *pkbuf = pkbuf_alloc(NAS_HEADROOM, MAX_SDU_LEN);
    d_assert(*pkbuf, return -1, "Null Param");

    size = sizeof(nas_esm_header_t);
    rv = pkbuf_header(*pkbuf, -size);
    d_assert(rv == CORE_OK, return CORE_ERROR, "pkbuf_header error");

    memcpy((*pkbuf)->payload - size, &message->esm.h, size);
    encoded += size;

    switch(message->esm.h.message_type)
    {
        case NAS_PDN_CONNECTIVITY_REQUEST:
            size = nas_encode_pdn_connectivity_request(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_PDN_CONNECTIVITY_REJECT:
            size = nas_encode_pdn_connectivity_reject(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_PDN_DISCONNECT_REQUEST:
            size = nas_encode_pdn_disconnect_request(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_PDN_DISCONNECT_REJECT:
            size = nas_encode_pdn_disconnect_reject(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        case NAS_ESM_INFORMATION_REQUEST:
            break;
        case NAS_ESM_INFORMATION_RESPONSE:
            size = nas_encode_esm_information_response(*pkbuf, message);
            d_assert(size >= 0, return CORE_ERROR, "decode error");
            encoded += size;
            break;
        default:
            d_error("Unknown message type (0x%x) or not implemented", 
                    message->esm.h.message_type);
            pkbuf_free((*pkbuf));
            return CORE_ERROR;
    }

    rv = pkbuf_header(*pkbuf, encoded);
    d_assert(rv == CORE_OK, return CORE_ERROR, "pkbuf_header error");

    (*pkbuf)->len = encoded;

    return CORE_OK;
}

status_t nas_plain_encode(pkbuf_t **pkbuf, nas_message_t *message)
{
    d_assert(message, return CORE_ERROR, "Null param");

    d_assert(message->emm.h.protocol_discriminator ==
            message->esm.h.protocol_discriminator, 
            return CORE_ERROR, "check UNION for protocol");

    if (message->emm.h.protocol_discriminator == 
            NAS_PROTOCOL_DISCRIMINATOR_EMM)
        return nas_emm_encode(pkbuf, message);
    else if (message->emm.h.protocol_discriminator == 
            NAS_PROTOCOL_DISCRIMINATOR_ESM)
        return nas_esm_encode(pkbuf, message);

    d_assert(0, return CORE_ERROR, 
            "Invalid Protocol : %d", message->emm.h.protocol_discriminator);
}
