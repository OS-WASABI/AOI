// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing an alert as per CAP message format.
 *
 * @file        alert_area.hpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#ifndef ALERT_AREA_H
#define ALERT_AREA_H
#include <string>
#include <vector>
#include <cpprest/json.h>

namespace aoi_rest {
struct AlertArea {
    std::string area_description;
    std::vector<std::string> polygons;
    std::vector<std::string> circles;
    std::vector<std::string> geocode;
    std::string altitude;
    std::string ceiling;
    /**
     * Converts the alert area entity to a json object.
     * 
     * @return a json object representation of a alert area.
     * 
     */
    web::json::value to_json() {
        auto json  = web::json::value::object();
        return json;
    }
    /**
     * Creates an optional<AlertArea> from a web::json::value.
     * 
     * If the json value does not contain all required fields,
     * a std::nullopt is returned.
     * 
     * @return std::optional<AlertArea>
     */     
    static std::optional<AlertArea> from_json(web::json::value area_json) {
        try {
            if (area_json.has_field("area_description") && area_json["area_description"].is_string()) {
                AlertArea alert_area;
                alert_area.area_description = area_json["area_description"].as_string();
                //TODO (Mike): validate format of area elements.
                if (area_json.has_field("polygons") && area_json["polygons"].is_array()) {
                    alert_area.polygons = area_json["polygons"].as_array();
                }                
                if (area_json.has_field("circles") && area_json["circles"].is_array()) {
                    alert_area.circles = area_json["circles"].as_array();
                }                
                if (area_json.has_field(geocode) && area_json["geocode"].is_array()) {
                    alert_area.geocode = area_json["geocode"].as_array();
                }
                if (area_json.has_field("altitude") && area_json["altitude"].is_string()) {
                    alert_area.altitude = area_json["altitude"].as_string();
                }
                if (area_json.has_field(ceiling) && area_json["ceiling"].is_string()) {
                    alert_area.ceiling = area_json["ceiling"].as_string();
                }
                return alert_area;
            } else {
                return std::nullopt;
            }
        } catch (std::exception&  e) {  
            return std::nullopt;
        }
    }
};
}
#endif // ALERT_AREA_H