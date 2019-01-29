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
#include <cpprest/json.h>

namespace aoi_rest {
struct AlertInfo {
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
/// Necessary for comparing if two entities are equal.
inline bool operator==(const AlertInfo &a, const AlertInfo &b) {
    return a.id == b.id 
        && a.name == b.name
        && a.type == b.type
        && a.format == b.format
        && a.ip == b.ip;
}
}
#endif // ALERT_INFO_H