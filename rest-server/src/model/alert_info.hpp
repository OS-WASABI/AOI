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
#include <optional>
#include <cpprest/json.h>

namespace aoi_rest {
struct AlertInfo {
    //Required elements
    std::optional<std::string> event;
    std::optional<std::string> urgency;
    std::optional<std::string> severity;
    std::optional<std::string> certainty;
    std::optional<std::time_t> expire_time;
    std::optional<std::time_t> effective_time; // generated upon creation
    std::optional<std::time_t> onset_time;     // generated upon creation
    //Optional elements
    std::optional<std::vector<AlertResource>> resources;
    std::optional<std::vector<AlertArea>> areas;
    std::optional<std::vector<std::string>> categories;
    std::optional<std::string> language;
    std::optional<std::vector<std::string>> response_types;
    std::optional<std::string> audience;
    std::optional<std::vector<std::string>> event_codes;
    std::optional<std::string> sender_name;
    std::optional<std::string> headline;
    std::optional<std::string> description;
    std::optional<std::string> instruction;
    std::optional<std::string> web_url;
    std::optional<std::string> contact;
    std::optional<std::vector<std::string>> parameters;
    
    /**
    * Evaluates the AlertInfo as valid per CAP v1.2 IPAWS profile.
    * 
    * @return boolean
    * 
    */   
    static bool is_valid_cap_ipaws(AlertInfo alert_info) {
        //TODO(Mike): You know, implement this thing.
        return true;
    }    
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
            AlertInfo alert_info = AlertInfo();
            // TODO (Mike): validate format of elements
            if (info_json.has_field("event") && info_json["event"].is_string())
                alert_info.event = info_json["event"].as_string();
            if (info_json.has_field("urgency") && info_json["urgency"].is_string())
                alert_info.urgency = info_json["urgency"].as_string();
            if (info_json.has_field("severity") && info_json["severity"].is_string())
                alert_info.severity = info_json["severity"].as_string();
            if (info_json.has_field("certainty") && info_json["certainty"].is_string())
                alert_info.certainty = info_json["certainty"].as_string();                    
            //TODO (Mike): convert expire_time to time_t
            //if (info_json.has_field("expire_time") && info_json["expire_time"].is_string())
            //alert_info.expire_time = CONVERT(info_json["expire_time"].as_string());
            if (info_json.has_field("resources") && info_json["resources"].is_array()) {
                web::json:array json_array = info_json["resources"].as_array();
                for (auto resource_json = json_array.begin(); resource_json != json_array.end(); ++resource_json) {
                    if (*resource_json.is_object() && (AlertResource alert_resource = AlertResource.from_json(*resource_json))) {
                        alert_info.resources.push_back(alert_resource);
                    }
                }
            }
            if (info_json.has_field("areas") && info_json["areas"].is_array()) {
                web::json:array json_array = info_json["areas"].as_array();
                for (auto area_json = json_array.begin(); area_json != json_array.end(); ++area_json) {
                    if (*area_json.is_object() && (AlertAlert alert_area = AlertArea.from_json(*area_json))) {
                        alert_info.areas.push_back(alert_area);
                    }
                }
            }
            if (info_json.has_field("categories") && info_json["categories"].is_array()) {
                web::json:array json_array = info_json["categories"].as_array();
                for (auto category_json = json_array.begin(); info_json != json_array.end(); ++category_json) {
                    if (*category_json.is_string()) 
                        alert_info.categories.push_back(*category_json.as_string());
                }
            } 
            if (info_json.has_field("language") && info_json["language"].is_string())
                alert_info.language = info_json["language"].to_string();
            if (info_json.has_field("response_types") && info_json["response_types"].is_array()) {
                web::json:array json_array = info_json["response_types"].as_array();
                for (auto response_type_json = json_array.begin(); info_json != json_array.end(); ++response_type_json) {
                    if (*response_type_json.is_string()) 
                        alert_info.response_types.push_back(*response_type_json.as_string());
                }
            } 
            if (info_json.has_field("audience") && info_json["audience"].is_string())
                alert_info.audience = info_json["audience"].to_string();
            if (info_json.has_field("event_codes") && info_json["event_codes"].is_array()) {
                web::json:array json_array = info_json["event_codes"].as_array();
                for (auto event_code_json = json_array.begin(); info_json != json_array.end(); ++event_code_json) {
                    if (*event_code_json.is_string()) 
                        alert_info.event_codes.push_back(*event_code_json.as_string());
                }
            } 
            if (info_json.has_field("sender_name") && info_json["sender_name"].is_string())
                alert_info.sender_name = info_json["sender_name"].to_string();
            if (info_json.has_field("headline") && info_json["headline"].is_string())
                alert_info.headline = info_json["headline"].to_string();
            if (info_json.has_field("description") && info_json["description"].is_string())
                alert_info.description = info_json["description"].to_string();
            if (info_json.has_field("instruction") && info_json["instruction"].is_string())
                alert_info.instruction = info_json["instruction"].to_string();
            if (info_json.has_field("web_url") && info_json["web_url"].is_string())
                alert_info.web_url = info_json["web_url"].to_string();
            if (info_json.has_field("contact") && info_json["contact"].is_string())
                alert_info.contact = info_json["contact"].to_string();
            if (info_json.has_field("paremeters") && info_json["paremeters"].is_array()) {
                web::json:array json_array = info_json["paremeters"].as_array();
                for (auto parameter_json = json_array.begin(); info_json != json_array.end(); ++parameter_json) {
                    if (*parameter_json.is_string()) 
                        alert_info.paremeters.push_back(*parameter_json.as_string());
                }
            } 
            if (AlertInfo::is_valid_cap_ipaws(alert_info)
                return alert_info;
            else 
                return std::nullopt;
        } catch (std::exception&  e) {  
            return std::nullopt;
        }
    }      
};
#endif // ALERT_INFO_H