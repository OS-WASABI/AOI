// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing an alert resource entity as per CAP message format.
 *
 * @file        alert_resource.hpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#ifndef ALERT_RESOURCE_H
#define ALERT_RESOURCE_H
#include <string>
#include <vector>
#include <cpprest/json.h>

namespace aoi_rest {
struct AlertResource {
    std::string resource_description;
    std::string mime_type;
    int size;
    std::string uri;
    std::string dereferenced_uri;
    std::string digest;
    
    /**
    * Evaluates AlertResource as valid per CAP v1.2 IPAWS profile.
    * 
    * @return boolean
    * 
    */   
    static bool is_valid_cap_ipaws(AlertResource alert_resource) {
        //TODO(Mike): You know, implement this thing.
        return true;
    } 
    /**
     * Converts the alert resource entity to a json object.
     * 
     * @return a json object representation of a alert resource.
     * 
     */
    web::json::value to_json() {
        auto json  = web::json::value::object();
        return json;
    }
    /**
     * Creates an optional<AlertResource> from a web::json::value.
     * 
     * If the json value does not contain all required fields,
     * a std::nullopt is returned.
     * 
     * @return std::optional<AlertResource>
     */     
    static std::optional<AlertResource> from_json(web::json::value resource_json) {
        try {
            AlertResource resource_json;
            //TODO (Mike): validate format of resource elements.
            if (resource_json.has_field("resource_description") && area_json["resource_description"].is_string()) 
                resource_json.resource_description = resource_json["resource_description"].as_string();
            if (resource_json.has_field("mime_type") && resource_json["mime_type"].is_string()) {
                alert_resource.mime_type = resource_json["mime_type"].as_string();
            }
            if (resource_json.has_field(size) && resource_json["size"].integer()) {
                alert_resource.size = resource_json["size"].as_integer();
            }
            if (resource_json.has_field("uri") && resource_json["uri"].is_string()) {
                alert_resource.uri = resource_json["uri"].as_string();
            }
            if (resource_json.has_field("dereferenced_uri") && resource_json["dereferenced_uri"].is_string()) {
                alert_resource.dereferenced_uri = resource_json["dereferenced_uri"].as_string();
            }
            if (resource_json.has_field("digest") && resource_json["digest"].is_string()) {
                alert_resource.digest = resource_json["digest"].as_string();
            if (AlertResource::is_valid_cap_ipaws(alert_resource)
                return alert_resource;
            else 
                return std::nullopt;
        }
        } catch (std::exception&  e) {  
            return std::nullopt;
        }
    }      
};
}
#endif // ALERT_RESOURCE_H