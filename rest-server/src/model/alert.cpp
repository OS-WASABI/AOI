// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Implementation code for alert classes.
 *
 * @file        alert.cpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */

/**
* Validates an Alert's identifier field. If valid, the value for the
* element is set and the function returns true.
*
* @return bool
*
*/

#include <alert.hpp>

namespace aoi_rest {

std::optional<std::vector<std::string>> json_value_to_string_vector_optional(web::json::value json_value) {
    if (!json_value.is_array())
        return std::nullopt;
    std::optional<std::vector<std::string>> temp_vector;
    for (auto json_element = json_value.as_array().begin();
         json_element != json_value.as_array().end(); ++json_element) {
        if (json_element->is_string()) {
            temp_vector.value().push_back(json_element->as_string());
        } else {
            return std::nullopt;
        }
    }
    return temp_vector;
}

std::optional<Alert> Alert::from_json(web::json::value alert_json) {
    try {
        Alert alert = Alert();

        // Required
        if (!alert_json.has_field("identifier") && !alert.validate_identifier(""))
            return std::nullopt;
        if (!alert_json["identifier"].is_string())
            return std::nullopt;
        if (!alert.validate_identifier(alert_json["identifier"].as_string()))
            return std::nullopt;

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

        if (alert_json.has_field("info")) {
            if (alert_json["info"].is_array()) {
                web::json::array json_array = alert_json["info"].as_array();
                std::vector<AlertInfo> temp_infos;
                for (auto info_json = json_array.begin(); info_json != json_array.end(); ++info_json) {
                    if (info_json->is_object()) {
                        if (std::optional<AlertInfo> temp_info = AlertInfo::from_json(*info_json)) {
                            alert.get_info().value().push_back(temp_info.value());
                        } else {
                            return std::nullopt;
                        }
                    } else {
                        return std::nullopt;
                    }
                }
            } else {
                return std::nullopt;
            }
        }
        return alert;
    } catch (std::exception &e) {
        return std::nullopt;
    }
}

bool Alert::validate_identifier(const std::string &identifier) {
    if (identifier.find_first_of(restricted_chars) == std::string::npos) {
        identifier__ = identifier;
        return true;
    }
    return false;
}

bool Alert::validate_sender(const std::string &sender) {
    if (sender.find_first_of(restricted_chars) == std::string::npos) {
        sender__ = sender;
        return true;
    }
    return false;
}

bool Alert::validate_sent_time(const time_t &sent_time) {
    sent_time__ = sent_time;
    return true;
}

bool Alert::validate_status(const std::string &status) {
    std::string status_proper = status;
    for (std::string::size_type i = 0; i < status_proper.length(); ++i) {
        if (i == 0)
            status_proper[i] = std::toupper(status_proper[i]);
        else
            status_proper[i] = std::tolower(status_proper[i]);
    }
    for (auto status_code = status_codes.begin(); status_code != status_codes.end(); status_code++) {
        if (status_proper == *status_code) {
            status__ = status_proper;
            return true;
        }
    }
    return false;
}

bool Alert::validate_msg_type(const std::string &msg_type) {
    std::string msg_type_proper = msg_type;
    for (std::string::size_type i = 0; i < msg_type_proper.length(); ++i) {
        if (i == 0)
            msg_type_proper[i] = std::toupper(msg_type_proper[i]);
        else
            msg_type_proper[i] = std::tolower(msg_type_proper[i]);
    }
    for (auto msg_type_code = msg_type_codes.begin();
         msg_type_code != msg_type_codes.end(); msg_type_code++) {
        if (msg_type_proper == *msg_type_code) {
            msg_type__ = msg_type_proper;
            return true;
        }
    }
    return false;
}

bool Alert::validate_scope(const std::string &scope) {
    std::string scope_proper = scope;
    for (std::string::size_type i = 0; i < scope_proper.length(); ++i) {
        if (i == 0)
            scope_proper[i] = std::toupper(scope_proper[i]);
        else
            scope_proper[i] = std::tolower(scope_proper[i]);
    }
    for (auto scope_code = scope_codes.begin(); scope_code != scope_codes.end(); scope_code++) {
        if (scope_proper == *scope_code) {
            scope__ = scope_proper;
            return true;
        }
    }
    return false;
}

bool Alert::validate_restriction(const std::string restriction) {
    restriction__ = restriction;
    return true;
}

bool Alert::validate_addresses(const std::vector<std::string> addresses) {
    if (scope__.value() == "Private" && addresses.size() == 0)
        return false;
    //TODO(Mike): Parse and validate addresses
    addresses__ = addresses;
    return true;
}

bool Alert::validate_handling_codes(const std::vector<std::string> handling_codes) {
    //TODO(Mike): Parse handling codes (validate IPAWS Profile)
    handling_codes__ = handling_codes;
    return true;
}

bool Alert::validate_source(const std::string source) {
    source__ = source;
    return true;
}

bool Alert::validate_note(const std::string note) {
    note__ = note;
    return true;
}

bool Alert::validate_references(const std::vector<std::string> references) {
    references__ = references;
    return true;
}

bool Alert::validate_incidents(const std::vector<std::string> incidents) {
    incidents__ = incidents;
    return true;
}

std::optional<std::vector<AlertInfo>> Alert::get_info() {
    return info__;
}
}