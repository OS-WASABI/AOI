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
    static std::optional<AlertResource> from_json(web::json::value json) {
        try {
            if(true) {
                AlertResource alert_resource;
                return alert_resource;
            } else {
                return std::nullopt;
            }
        } catch (std::exception&  e) {  
            return std::nullopt;
        }
    }      
};
}
#endif // ALERT_RESOURCE_H