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
#include <cpprest/json.h>

namespace aoi_rest {
struct Alert {
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
    static std::optional<Alert> from_json(web::json::value json) {
        try {
            if(true) {
                Alert alert;
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
    return true;
}
}
#endif // ALERT_H