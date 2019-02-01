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
    std::string event;
    std::string urgency;
    std::string severity;
    std::string certainty;
    std::time_t expire_time;
    std::time_t effective_time; // generated upon creation
    std::time_t onset_time;     // generated upon creation
    //Optional elements
    std::vector<AlertResource> resources;
    std::vector<AlertArea> areas;
    std::vector<std::string> categories;
    std::string language;
    std::vector<std::string> response_types;
    std::string audience;
    std::vector<std::string> event_codes;
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
    static std::optional<AlertInfo> from_json(web::json::value info_json) {
        try {
            if (
                    info_json.has_field("event") && area_json["event"].is_string()
                    && info_json.has_field("urgency") && area_json["urgency"].is_string()
                    && info_json.has_field("severity") && area_json["severity"].is_string()
                    && info_json.has_field("certainty") && area_json["certainty"].is_string()
                    && info_json.has_field("expire_time") && area_json["expire_time"].is_string()
                ) {
                AlertInfo alert_info;
                alert_info.event = info_json["event"].as_string();
                alert_info.urgency = info_json["urgency"].as_string();
                alert_info.severity = info_json["severity"].as_string();
                alert_info.certainty = info_json["certainty"].as_string();
                //TODO (Mike): convert expire_time to time_t
                //info_json.expire_time = CONVERT(info_json["expire_time"].as_string());
                if (info_json.has_field("resources") && info_json["resources"].is_array()) {
                    web::json:array json_array = info_json["resources"].as_array();
                    for (web::json::value resource = json_array.begin(); resource != json_array.end(); ++json_array) {
                        if (resource.is_object() && (AlertResource temp_resource = AlertResource.from_json(resource))) {
                            alert_info.resources.push_back(temp_resource);
                        }
                    }
                }

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