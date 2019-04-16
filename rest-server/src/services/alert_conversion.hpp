//
// Created by mike on 4/15/19.
//

#ifndef AOI_REST_SERVER_ALERT_CONVERSION_HPP
#define AOI_REST_SERVER_ALERT_CONVERSION_HPP

#include <logger.hpp>
#include <logger_interface.hpp>
#include "log_level.hpp"
#include "../gSoapFiles/client/soapH.h"
#include <time.h>
#include <regex>

namespace aoi_soap {
bool json_to_gsoap(web::json::value &alert_json, _ns4__alert &alert) {
    try {
        // Required
        if (alert_json.has_field("identifier") && alert_json["identifier"].is_string()) {
            alert.identifier = alert_json["identifier"].as_string();
        } else {
            return false;
        }


        /*
        // Required
        if (!alert_json.has_field("sender") && !alert.validate_sender(""))
            return std::nullopt;
        if (!alert_json["sender"].is_string())
            return std::nullopt;
        if (!alert.validate_sender(alert_json["sender"].as_string()))
            return std::nullopt;

        // Required
        if (!alert_json.has_field("sent_time") && !alert.validate_sent_time(0))
            return std::nullopt;
        if (!alert_json["sent_time"].is_string())
            return std::nullopt;
        struct tm tm;
        strptime(alert_json["sent_time"].as_string().c_str(), "%FT%T.000Z", &tm);
        time_t sent_time = mktime(&tm);
        if (!alert.validate_sent_time(sent_time))
            return std::nullopt;

        //Required
        if (!alert_json.has_field("status") && !alert.validate_status(""))
            return std::nullopt;
        if (!alert_json["status"].is_string())
            return std::nullopt;
        if (!alert.validate_status(alert_json["status"].as_string()))
            return std::nullopt;

        // Required
        if (alert_json.has_field("msg_type") && alert.validate_msg_type(""))
            return std::nullopt;
        if (!alert_json["msg_type"].is_string())
            return std::nullopt;
        if (!alert.validate_msg_type(alert_json["msg_type"].as_string()))
            return std::nullopt;


        // Required
        if (!alert_json.has_field("scope") && !alert.validate_scope(""))
            return std::nullopt;
        if (!alert_json["scope"].is_string())
            return std::nullopt;
        if (!alert.validate_scope(alert_json["scope"].as_string()))
            return std::nullopt;

        // Required per CAP IPAWS Profile
        std::optional<std::vector<std::string>> codes_vector = json_value_to_string_vector_optional(alert_json["handling_codes"]);
        if (!codes_vector)
            return std::nullopt;
        if (!alert.validate_handling_codes(codes_vector.value()))
            return std::nullopt;

        // Conditional
        if (!alert_json.has_field("restriction") && !alert.validate_restriction(""))
            return std::nullopt;
        if (!alert_json["restriction"].is_string())
            return std::nullopt;
        if (!alert.validate_restriction(alert_json["restrction"].as_string()))
            return std::nullopt;

        // Conditional
        std::optional<std::vector<std::string>> addresses_vector = json_value_to_string_vector_optional(alert_json["addresses"]);
        if (!addresses_vector)
            return std::nullopt;
        if (!alert.validate_addresses(addresses_vector.value()))
            return std::nullopt;

        // Optional
        if (!alert_json.has_field("source") && !alert.validate_source(""))
            return std::nullopt;
        if (!alert_json["source"].is_string())
            return std::nullopt;
        if (!alert.validate_source(alert_json["source"].as_string()))
            return std::nullopt;


        if (!alert_json.has_field("note") && !alert.validate_note(""))
            return std::nullopt;
        if (!alert_json["note"].is_string())
            return std::nullopt;
        if (!alert.validate_note(alert_json["note"].as_string()))
            return std::nullopt;

        std::optional<std::vector<std::string>> references_vector = json_value_to_string_vector_optional(alert_json["references"]);
        if (!references_vector)
            return std::nullopt;
        if (!alert.validate_references(references_vector.value()))
            return std::nullopt;

        std::optional<std::vector<std::string>> incidents_vector = json_value_to_string_vector_optional(alert_json["incidents"]);
        if (!incidents_vector)
            return std::nullopt;
        if (!alert.validate_incidents(references_vector.value()))
            return std::nullopt;
        */
        return true;
    } catch (std::exception &e) {
        return false;
    }
}
}
#endif //AOI_REST_SERVER_ALERT_CONVERSION_HPP
