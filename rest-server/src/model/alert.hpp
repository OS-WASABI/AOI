// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing an alert as per CAP message format.
 *
 * @file        alert.hpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */
#ifndef ALERT_H
#define ALERT_H
#include <optional>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <regex>
#include <cpprest/json.h>

namespace aoi_rest {
struct Alert {
    static std::array<std::string,5> std:
    
    // Required elements
    std::optional<std::string> identifier;
    std::optional<std::string> sender;
    std::optional<XMLDateTime> sent_time;
    std::optional<std::string> status;
    std::optional<std::string> msg_type;
    std::optional<std::string> scope;
    std::optional<std::vector<AlertInfo>> info;
    // Conditional elements
    std::optional<std::string> restriction;
    std::optional<std::string> addresses;      // Required when scope is "Private", optional otherwise.
    // Optional elements    
    std::optional<std::vector<string>> handling_codes;
    std::optional<std::string> source; 
    std::optional<std::string> note;
    std::optional<std::string> references; 
    std::optional<std::string> incidents;
    
    // Allowed codes as per CAP 1.2.
    static const std::array<std::string,5> status_codes {"Actual", "Exercise", "System", "Test", "Draft"};
    static const std::array<std::string,5> msg_type_codes {"Alert", "Update", "Cancel", "Ack", "Error"};
    static const std::array<std::string,3> scope_codes {"Publc", "Restricted", "Private"};
    
    static const std::string restricted_chars = " ,<&";
    
    /**
    * Validates an Alert's identifier field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */   
    bool validate_identifier(web::json::value& alert_json) {
        if (alert_json.has_field("identifier") && alert_json["identifier"].is_string()) {
            if (alert_json["identifier"].as_string().find_first_of(restricted_chars) == std::string::npos
                    && ) {
                identifier = alert_json["identifier"].as_string();
                return true;
            }
        }
        return false;
    }  
    /**
    * Validates an Alert's sender field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */   
    bool validate_sender(web::json::value& alert_json) {
        if (alert_json.has_field("sender") && alert_json["sender"].is_string()) {
            if (alert_json["sender"].as_string().find_first_of(restricted_chars) == std::string::npos) {
                sender = alert_json["sender"].as_string();
                return true;
            }
        }
        return false;
    }  
    /**
    * Validates an Alert's sent_time field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */   
    bool validate_sent_time(web::json::value& alert_json) {
        if (alert_json.has_field("sent_time") && alert_json["sent_time"].is_string()) 
            && (auto sent_time_optional = XMLDateTime::from_string(alert_json["sent_time"].as_string())) {
            sent_time = sent_time_optional.value();
            return true;
        }
        return false;
    /**
    * Validates an Alert's status field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */   
    bool validate_status(web::json::value& alert_json) {
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
    /**
    * Validates an Alert's msg_type field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */ 
    bool validate_msg_type(web::json::value& alert_json) {
        if (alert_json.has_field("msg_type") && alert_json["msg_type"].is_string()) {
            std::string msg_type_proper = alert_json["msg_type"].as_string();
            for (std::string::size_type i = 0; i < msg_type_proper.length(); ++i) {
               if (i == 0) 
                   msg_type_proper[i] = std::toupper(msg_type_proper[i]);
               else 
                   msg_type_proper[i] = std::tolower(msg_type_proper[i]);
            }
            for (auto msg_type_code = msg_type_codes.begin(); msg_type_code != msg_type_codes.end(); msg_type_code++) {
                if (msg_type_proper == *msg_type_code) {
                    msg_type = msg_type_proper;
                    return true;
                }
            }
        }
        return false;
    }
    /**
    * Validates an Alert's scope field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */   
    bool validate_scope(web::json::value& alert_json) {
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
    /**
    * Validates an Alert's info arary. If valid, the value for thevector of AlertInfo
    * objects. If invalid, returns std::nullopt.
    * 
    * @return bool
    * 
    */   
    bool validate_info(web::json::value& alert_json) {
        if (alert_json.has_field("info") && alert_json["info"].is_array()) {
            web::json::array json_array = alert_json["info"].as_array();
            std::vector<AlertInfo> temp_infos;
            for (auto info_json = json_array.begin(); info_json != json_array.end(); ++info_json) {
                if (*info_json.is_object() && (AlertInfo temp_info = AlertInfo.from_json(*info_json))) {
                    temp_infos.push_back(temp_info);
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
    /**
    * Validates an Alert's restriction field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * Used when scope is "Restricted".
    * 
    * @return bool
    * 
    */   
    //TODO(Mike): Determine if this is optional when scope is restricted.
    bool validate_restriction(web::json::value& alert_json) {
        if (alert_json.has_field("restriction") && alert_json["restriction"].is_string()) {
            restriction = alert_json["restriction"].as_string();
            return true;
        }
        return false;
    }
    /**
    * Validates an Alert's addresses field. If valid, the value for the
    * element is set and the function returns true. 
    * 
    * Addresses are required when scope is "Private", optional otherwise.
    * For proper validation, this function MUST be called after validating
    * the scope element.
    * 
    * @return bool
    * 
    */   
    bool validate_addresses(web::json::value& alert_json) {
        if (scope.value() == "Private") {
            if (alert_json.has_field("addresses") 
                && alert_json["addresses"].is_string() 
                && alert_json["addresses"].as_string() != "") {
                //TODO(Mike): Parse addresses
            } else {
                return false
            }
        } else {
            if (alert_json["addresses"].is_string()) {
                //TODO(Mike): Parse addresses
            } else {
                return std::nullopt;
            }
        }
    }
    /**
    * Validates an Alert's handling_codes elements. If valid, the value for thevector of 
    * strings. If invalid, returns std::nullopt.
    * 
    * @return bool
    * 
    */   
    static std::optional<std::vector<AlertInfo>> validate_handling_codes(web::json::value& alert_json) {
        if (alert_json.has_field("handling_codes") && alert_json["handling_codes"].is_array()) {
            web::json::array json_array = alert_json["handling_codes"].as_array();
            std::vector<string> handling_codes;
            for (auto handling_codes_json = json_array.begin(); handling_codes_json != json_array.end(); ++handling_codes_json) {
                if (*handling_codes_json.is_string()) {
                    handling_codes.push_back(*handling_codes_json.as_string());
                } else {
                    return std::nullopt;
                }
            }
            return alert_handling_codes;
        } else {
            return std::nullopt;
        }
    }
    /**
    * Validates an Alert's source field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */   
    static std::optional<std::string> validate_source(web::json::value& alert_json) {
        if (alert_json.has_field("source") && alert_json["source"].is_string()) {
            return alert_json["source"].as_string();
        } else {
            return std::nullopt;
        }
    }
    /**
    * Validates an Alert's note field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * @return bool
    * 
    */   
    static std::optional<std::string> validate_note(web::json::value& alert_json) {
        if (alert_json.has_field("note") && alert_json["note"].is_string()) {
            return alert_json["note"].as_string();
        } else {
            return std::nullopt;
        }
    }
    /**
    * Validates an Alert's incidents field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * References to earlier messages in form "sender,identifier,sent" (no whitespace).
    * Multiple references separated by whitespace.
    *
    * @return bool
    * 
    */    
    static std::optional<std::string> validate_references(web::json::value& alert_json) {
        if (alert_json.has_field("references") && alert_json["references"].is_string()) {
            return alert_json["references"].as_string();
        } else {
            return std::nullopt;
        }
    }
    /**
    * Validates an Alert's incidents field. If valid, the value for the
    * element is set and the function returns true.
    * 
    * Multiple incidents separated by whitespace. If incident name contains whitespace
    * then surround with double-quotes.
    *
    * @return bool
    * 
    */
    static std::optional<std::string> validate_incidents(web::json::value& alert_json) {
        if (alert_json.has_field("incidents") && alert_json["incidents"].is_string()) {
            return alert_json["incidents"].as_string();
        } else {
            return std::nullopt;
        }
    }
/**
     * Converts the alert entity to a json object.
     * 
     * @return a json object representation of a alert.
     * 
     */
    web::json::value to_json() {
        auto json  = web::json::value::object();
        return json;
    }
    /**
     * Creates an optional<Alert> from a web::json::value.
     * 
     * If the json value does not contain all required fields,
     * a std::nullopt is returned.
     * 
     * @return std::optional<Alert>
     */     
    static std::optional<Alert> from_json(web::json::value alert_json) {
        try {
            Alert alert;
            alert.identifer = Alert::validate_identifier(alert_json);
            alert.sender = Alert::validate_sender(alert_json); 
            alert.status = Alert::validate_status(alert_json); 
            alert.msg_type = Alert::validate_msg_type(alert_json); 
            alert.scope = Alert::validate_scope(alert_json); 
            alert.info = Alert::validate_info(alert_json); 
            alert.restriction = Alert::validate_restriction(alert_json); 
            alert.addresses = Alert::validate_addresses(alert_json); 
            alert.handling_codes = Alert::validate_handling_codes(alert_json); 
            alert.source = Alert::validate_source(alert_json); 
            alert.note = Alert::validate_note(alert_json); 
            alert.references = Alert::validate_references(alert_json); 
            alert.incidents = Alert::validate_incidents(alert_json); 
            if (alert.identifier && alert.
                return alert;
            } else {
                return std::nullopt;
            }
        } catch (std::exception&  e) {  
            return std::nullopt;
        }
    }      
};
/// Necessary for comparing if two entities are equal.
inline bool operator==(const Alert &a, const Alert &b) {
    return a.identifier == b.identifier;
}
}
#endif // ALERT_H