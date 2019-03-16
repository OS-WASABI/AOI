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

bool Alert::validate_identifier(web::json::value &alert_json) {
    if (alert_json.has_field("identifier") && alert_json["identifier"].is_string()) {
        if (alert_json["identifier"].as_string().find_first_of(restricted_chars) == std::string::npos) {
            identifier = alert_json["identifier"].as_string();
            return true;
        }
    }
    return false;
}

bool Alert::validate_sender(web::json::value &alert_json) {
    if (alert_json.has_field("sender") && alert_json["sender"].is_string()) {
        if (alert_json["sender"].as_string().find_first_of(restricted_chars) == std::string::npos) {
            sender = alert_json["sender"].as_string();
            return true;
        }
    }
    return false;
}

bool Alert::validate_sent_time(web::json::value &alert_json) {
    if (alert_json.has_field("sent_time") && alert_json["sent_time"].is_string()) {
        struct tm tm;
        strptime(alert_json["sent_time"].as_string().c_str(), "%FT%T.000Z", &tm);
        sent_time = mktime(&tm);
        return true;
    }
    return false;
}

bool Alert::validate_status(web::json::value &alert_json) {
    if (alert_json.has_field("status") && alert_json["status"].is_string()) {
        std::string status_proper = alert_json["status"].as_string();
        for (std::string::size_type i = 0; i < status_proper.length(); ++i) {
            if (i == 0)
                status_proper[i] = std::toupper(status_proper[i]);
            else
                status_proper[i] = std::tolower(status_proper[i]);
        }
        for (auto status_code = status_codes.begin(); status_code != status_codes.end(); status_code++) {
            if (status_proper == *status_code) {
                status = status_proper;
                return true;
            }
        }
    }
    return false;
}

bool Alert::validate_msg_type(web::json::value &alert_json) {
    if (alert_json.has_field("msg_type") && alert_json["msg_type"].is_string()) {
        std::string msg_type_proper = alert_json["msg_type"].as_string();
        for (std::string::size_type i = 0; i < msg_type_proper.length(); ++i) {
            if (i == 0)
                msg_type_proper[i] = std::toupper(msg_type_proper[i]);
            else
                msg_type_proper[i] = std::tolower(msg_type_proper[i]);
        }
        for (auto msg_type_code = msg_type_codes.begin();
             msg_type_code != msg_type_codes.end(); msg_type_code++) {
            if (msg_type_proper == *msg_type_code) {
                msg_type = msg_type_proper;
                return true;
            }
        }
    }
    return false;
}

bool Alert::validate_scope(web::json::value &alert_json) {
    if (alert_json.has_field("scope") && alert_json["scope"].is_string()) {
        std::string scope_proper = alert_json["scope"].as_string();
        for (std::string::size_type i = 0; i < scope_proper.length(); ++i) {
            if (i == 0)
                scope_proper[i] = std::toupper(scope_proper[i]);
            else
                scope_proper[i] = std::tolower(scope_proper[i]);
        }
        for (auto scope_code = scope_codes.begin(); scope_code != scope_codes.end(); scope_code++) {
            if (scope_proper == *scope_code) {
                scope = scope_proper;
                return true;
            }
        }
    }
    return false;
}

bool Alert::validate_info(web::json::value &alert_json) {
    if (alert_json.has_field("info") && alert_json["info"].is_array()) {
        web::json::array json_array = alert_json["info"].as_array();
        std::vector<AlertInfo> temp_infos;
        for (auto info_json = json_array.begin(); info_json != json_array.end(); ++info_json) {
            if (info_json->is_object()) {
                if (std::optional<AlertInfo> temp_info = AlertInfo::from_json(*info_json))
                    temp_infos.push_back(temp_info.value());
            } else {
                return false;
            }
        }
        // Yeah, the naming could be better.
        info = temp_infos;
        return true;
    }
    return false;
}

bool Alert::validate_restriction(web::json::value &alert_json) {
    if (alert_json.has_field("restriction") && alert_json["restriction"].is_string()) {
        restriction = alert_json["restriction"].as_string();
        return true;
    }
    return false;
}

bool Alert::validate_addresses(web::json::value &alert_json) {
    if (scope.value() == "Private") {
        if (alert_json.has_field("addresses")
            && alert_json["addresses"].is_string()
            && alert_json["addresses"].as_string() != "") {
            //TODO(Mike): Parse addresses
        } else {
            return false;
        }
    } else {
        if (alert_json["addresses"].is_string()) {
            //TODO(Mike): Parse addresses
        } else {
            return false;
        }
    }
}

bool Alert::validate_handling_codes(web::json::value &alert_json) {
    if (alert_json.has_field("handling_codes") && alert_json["handling_codes"].is_array()) {
        web::json::array json_array = alert_json["handling_codes"].as_array();
        for (auto handling_codes_json = json_array.begin();
             handling_codes_json != json_array.end(); ++handling_codes_json) {
            if (handling_codes_json->is_string()) {
                handling_codes.push_back(handling_codes_json->as_string());
            } else {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Alert::validate_source(web::json::value &alert_json) {
    if (alert_json.has_field("source") && alert_json["source"].is_string()) {
        source = alert_json["source"].as_string();
        return true;
    } else {
        return false;
    }
}

bool Alert::validate_note(web::json::value &alert_json) {
    if (alert_json.has_field("note") && alert_json["note"].is_string()) {
        note = alert_json["note"].as_string();
        return true;
    } else {
        return false;
    }
}

bool Alert::validate_references(web::json::value &alert_json) {
    if (alert_json.has_field("references") && alert_json["references"].is_string()) {
        references = alert_json["references"].as_string();
        return true;
    } else {
        return false;
    }
}

bool Alert::validate_incidents(web::json::value &alert_json) {
    if (alert_json.has_field("incidents") && alert_json["incidents"].is_string()) {
        incidents = alert_json["incidents"].as_string();
        return true;
    } else {
        return false;
    }
}
} // namespace aoi_rest