// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing a datetime convenient for XML dateTime. This format
 * is required for both CAP and CMAC messages.
 *
 * Example: 2003-04-02T14:39:01-05:00
 *
 * @file        xml_datetime.hpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */
#ifndef XML_DATETIME_H
#define XML_DATETIME_H
#include <string>
#include <regex>
#include <optional>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ios>

namespace aoi_rest {
struct XMLDateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int zone_hour;
    int zone_minute;
    
    static std::optional<XMLDateTime> from_string(std::string xml_datetime_string) {
        std::regex datetime_regex {"(2[0-9]{3})-(0[1-9]|1[0-2])-(0[1-9]|1[0-9]|2[0-9]|3[0-1])T(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])-(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])"};
        std::smatch matches;
        std::regex_search(date_string, matches, datetime_regex);
        if (matches.size() == 9) {
            XMLDateTime xml_datetime;
            // matches[0] is the entire matched string.
            xml_datetime.year = std::stoi(matches[1]);
            xml_datetime.month = std::stoi(matches[2]);
            xml_datetime.day = std::stoi(matches[3]);
            xml_datetime.hour = std::stoi(matches[4]);
            xml_datetime.minute = std::stoi(matches[5]);
            xml_datetime.second = std::stoi(matches[6]);
            xml_datetime.zone_hour = std::stoi(matches[7]);
            xml_datetime.zone_minute = std::stoi(matches[8]);
            // TODO(Mike): validate using tm struct?
            return xml_datetime;
        }
        return std::nullopt;
    }
    
    std::string to_string() {
        std::ostringstream os;
        os << std::internal << std::setfill('0') << std::setw(4) << year 
            << '-' << std::setfill('0') << std::setw(2) << month
            << '-' << std::setfill('0') << std::setw(2) << day
            << 'T' << std::setfill('0') << std::setw(2) << hour
            << ':' << std::setfill('0') << std::setw(2) << minute
            << ':' << std::setfill('0') << std::setw(2) << second
            << '-' << std::setfill('0') << std::setw(2) << zone_hour
            << ':' << std::setfill('0') << std::setw(2) << zone_minute;
        return os.str();
    }
}
}
#endif // XML_DATETIME_H