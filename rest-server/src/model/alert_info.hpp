// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing an alert info entity as per CAP message format.
 *
 * @file        alert_info.hpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#ifndef ALERT_INFO_H
#define ALERT_INFO_H
#include <string>
#include <vector>
#include <ctime>
#include <cpprest/json.h>

namespace aoi_rest {
struct AlertInfo {
    //Required elements
    std::vector<AlertResource> resources;
    std::vector<AlertArea> areas;
    std::vector<std::string> categories;
    std::string event;
    std::string urgency;
    std::string severity;
    std::string certainty;
    //Optional elements
    std::string language;
    std::vector<std::string> response_types;
    std::string audience;
    std::vector<std::string> event_codes;
    std::time_t effective_time;
    std::time_t onset_time;
    std::time_t expire_time;
    std::string sender_name;
    std::string headline;
    std::string description;
    std::string instruction;
    std::string web_url;
    std::string contact;
    std::vector<std::string> parameters;
    
    /**
     * Converts the alert info entity to a json object.
     * 
     * @return a json object representation of a alert info.
     * 
     */
    web::json::value to_json() {
        auto json  = web::json::value::object();
        return json;
    }
    /**
     * Creates an optional<AlertInfo> from a web::json::value.
     * 
     * If the json value does not contain all required fields,
     * a std::nullopt is returned.
     * 
     * @return std::optional<AlertInfo>
     */     
    static std::optional<AlertInfo> from_json(web::json::value json) {
        try {
            if(true) {
                AlertInfo alert_info;
                return alert_info;
            } else {
                return std::nullopt;
            }
        } catch (std::exception&  e) {  
            return std::nullopt;
        }
    }      
};
#endif // ALERT_INFO_H