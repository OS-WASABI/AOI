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
            if(  alert_json.has_field("identifier")
                 && alert_json.has_field("sender")
                 && alert_json.has_field("sent_time")
                 && alert_json.has_field("status")
                 && alert_json.has_field("msg_type")
                 && alert_json.has_field("scope")
            ) {
                Alert alert;
                alert.identifier = alert_json["identifier"].as_string();
                alert.sender = alert_json["sender"].as_string();
                alert.sent_time = alert_json["sent_time"].as_string();
                alert.status = alert_json["status"].as_string();
                alert.msg_type = alert_json["msg_type"].as_string();
                alert.scope = alert_json["scope"].as_string();
                //TODO (Mike): alert info, area, resource from json
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