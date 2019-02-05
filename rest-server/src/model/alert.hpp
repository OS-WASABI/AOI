// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing an alert as per CAP message format.
 *
 * @file        alert.hpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#ifndef ALERT_H
#define ALERT_H
#include <string>
#include <vector>
#include <ctime>
#include <cpprest/json.h>

namespace aoi_rest {
struct Alert {
    // Required elements
    std::string identifier;
    std::string sender;
    std::time_t sent_time;
    std::string status;
    std::string msg_type;
    std::string scope;
    std::vector<AlertInfo> info;
    // Conditional elements
    std::string restriction;    // Used when scope is "Restricted" (optional?)
    std::string addresses;      // Required when scope is "Private", optional otherwise.
    // Optional elements    
    std::vector<string> handling_codes;
    std::string source; 
    std::string note;
    std::string references;     // Reference earlier messages in form "sender,identifier,sent"
                                // with multiple references separated by whitespace. 
    std::string incidents;      // Multiples separated by whitespace. If names include whitespace,
                                // surround with double-quotes.
                                
    /**
    * Evaluates an Alert as valid per CAP v1.2 IPAWS profile.
    * 
    * @return boolean
    * 
    */   
    static bool is_valid_cap_ipaws(Alert alert) {
        //TODO(Mike): You know, implement this thing.
        return true;
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
            if (alert_json.has_field("identifier") && alert_json["identifier"].is_string())
                alert.identifier = alert_json["identifier"].as_string();
            if (alert_json.has_field("sender") && alert_json["sender"].is_string())
                alert.sender = alert_json["sender"].as_string();
            // TODO(Mike): Read datetime
            //if (alert_json.has_field("sent_time") && alert_json["sent_time"].is_string())
            //    alert.sent_time = alert_json["sent_time"].as_string();
            if (alert_json.has_field("status") && alert_json["status"].is_string())
                alert.status = alert_json["status"].as_string();
            if (alert_json.has_field("msg_type") && alert_json["msg_type"].is_string())
                alert.msg_type = alert_json["msg_type"].as_string();
            if (alert_json.has_field("scope") && alert_json["scope"].is_string())
                alert.scope = alert_json["scope"].as_string();
            if (alert_json.has_field("info") && alert_json["info"].is_array()) {
                web::json:array json_array = alert_json["info"].as_array();
                for (web::json::value info_json = json_array.begin(); area_json != json_array.end(); ++info_json) {
                    if (*info_json.is_object() && (AlertInfo alert_info = AlertInfo.from_json(*info_json))) {
                        alert.info.push_back(alert_info);
                    }
                }
            }
            if (alert_json.has_field("restriction") && alert_json["restriction"].is_string())
                alert.restriction = alert_json["restriction"].as_string();
            if (alert_json.has_field("addresses") && alert_json["addresses"].is_string())
                alert.addresses = alert_json["addresses"].as_string();
            if (alert_json.has_field("handling_codes") && alert_json["handling_codes"].is_array()) {
                web::json:array json_array = alert_json["handling_codes"].as_array();
                for (web::json::value handling_codes_json = json_array.begin(); area_json != json_array.end(); ++handling_codes_json) {
                    if (*handling_codes_json.is_string()) 
                        alert.handling_codes.push_back(*handling_codes_json.as_string());
                }
            } 
            if (alert_json.has_field("source") && alert_json["source"].is_string())
                alert.source = alert_json["source"].as_string();
            if (alert_json.has_field("note") && alert_json["note"].is_string())
                alert.note = alert_json["note"].as_string();
            if (alert_json.has_field("references") && alert_json["references"].is_string())
                alert.references = alert_json["references"].as_string();
            if (alert_json.has_field("incidents") && alert_json["incidents"].is_string())
                alert.incidents = alert_json["incidents"].as_string();
            if (Alert::is_valid_cap_ipaws(alert)
                return alert;
            else 
                return std::nullopt;
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