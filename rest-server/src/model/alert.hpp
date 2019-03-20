// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing an alert as per CAP message format.
 *
 * @file        alert.hpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */
#ifndef ALERT_H
#define ALERT_H

#include <string>
#include <vector>
#include <array>
#include <time.h>
#include <optional>
#include <cpprest/json.h>
#include <alert_area.hpp>
#include <alert_info.hpp>
#include <alert_resource.hpp>

namespace aoi_rest {
// Allowed codes as per CAP 1.2.
static const std::array<std::string, 5> status_codes {"Actual", "Exercise", "System", "Test", "Draft"};
static const std::array<std::string, 5> msg_type_codes {"Alert", "Update", "Cancel", "Ack", "Error"};
static const std::array<std::string, 3> scope_codes {"Publc", "Restricted", "Private"};

static const std::string restricted_chars = " ,<&";
class Alert {

private:

    // Required elements
    std::optional<std::string> identifier__;
    std::optional<std::string> sender__;
    std::optional<std::time_t> sent_time__;
    std::optional<std::string> status__;
    std::optional<std::string> msg_type__;
    std::optional<std::string> scope__;
    std::optional<std::vector<AlertInfo>> info__;
    // Conditional elements
    std::optional<std::string> restriction__;
    std::optional<std::string> addresses__;      // Required when scope is "Private", optional otherwise.
    // Optional elements
    std::optional<std::vector<std::string>> handling_codes__;
    std::optional<std::string> source__;
    std::optional<std::string> note__;
    std::optional<std::string> references__;
    std::optional<std::string> incidents__;

    /**
    * Validates an Alert's identifier field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_identifier(const std::string &identifier);

    /**
    * Validates an Alert's sender field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_sender(const std::string &sender);

    /**
    * Validates an Alert's sent_time field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_sent_time(const time_t &sent_time);

    /**
    * Validates an Alert's status field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_status(const std::string &status);

    /**
    * Validates an Alert's msg_type field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_msg_type(const std::string &msg_type);

    /**
    * Validates an Alert's scope field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_scope(const std::string &scope);

    /**
    * Validates an Alert's restriction field. If valid, the value for the
    * element is set and the function returns true.
    *
    * Used when scope is "Restricted".
    *
    * @return bool
    *
    */
    bool validate_restriction(const std::string restriction);

    /**
    * Validates an Alert's addresses field. If valid, the value for the
    * element is set and the function returns true.
    *
    * Addresses are required when scope is "Private", optional otherwise.
    * For proper validation, this function MUST be called after validating
    * the scope element.
    *
    * @return bool
    *
    */
    bool validate_addresses(const std::string addresses);

    /**
    * Validates an Alert's handling_codes elements. If valid, the value for thevector of
    * strings. If invalid, returns std::nullopt.
    *
    * @return bool
    *
    */
    bool validate_handling_code(const std::string handling_code);

    /**
    * Validates an Alert's source field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_source(const std::string source);

    /**
    * Validates an Alert's note field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_note(const std::string note);

    /**
    * Validates an Alert's incidents field. If valid, the value for the
    * element is set and the function returns true.
    *
    * References to earlier messages in form "sender,identifier,sent" (no whitespace).
    * Multiple references separated by whitespace.
    *
    * @return bool
    *
    */
    bool validate_references(const std::string references);

    /**
    * Validates an Alert's incidents field. If valid, the value for the
    * element is set and the function returns true.
    *
    * Multiple incidents separated by whitespace. If incident name contains whitespace
    * then surround with double-quotes.
    *
    * @return bool
    *
    */
    bool validate_incidents(const std::string incidents);

public:
    Alert();
    Alert(web::json::value alert_json);
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
            Alert alert = Alert();

            if (alert_json.has_field("identifier") && alert_json["identifier"].is_string()) {
                if (!alert.validate_identifier(alert_json["identifier"].as_string()))
                    return std::nullopt;
            } else {
                return std::nullopt;
            }

            if (alert_json.has_field("sender") && alert_json["sender"].is_string())
                alert.validate_sender(alert_json["sender"].as_string());

            if (alert_json.has_field("sent_time") && alert_json["sent_time"].is_string()) {
                struct tm tm;
                strptime(alert_json["sent_time"].as_string().c_str(), "%FT%T.000Z", &tm);
                time_t sent_time = mktime(&tm);
            }

            if (alert_json.has_field("status") && alert_json["status"].is_string())
                alert.validate_status(alert_json["status"].as_string());

            if (alert_json.has_field("msg_type") && alert_json["msg_type"].is_string())
                alert.validate_msg_type(alert_json["msg_type"].as_string());

            if (alert_json.has_field("scope") && alert_json["scope"].is_string())
                alert.validate_scope(alert_json["scope"].as_string());

            if (alert_json.has_field("info") && alert_json["info"].is_array()) {
                web::json::array json_array = alert_json["info"].as_array();
                std::vector<AlertInfo> temp_infos;
                for (auto info_json = json_array.begin(); info_json != json_array.end(); ++info_json) {
                    if (info_json->is_object()) {
                        if (std::optional<AlertInfo> temp_info = AlertInfo::from_json(*info_json)) {
                            alert.info__.push_back(temp_info.value());
                        }
                    }
                }

            }

            if (alert_json.has_field("restriction") && alert_json["restriction"].is_string())
                alert.validate_restriction(alert_json["restrction"].as_string());

            if (alert_json.has_field("addresses") && alert_json["addresses"].is_string())
                alert.validate_addresses(alert_json["addresses"].as_string());

            if (alert_json.has_field("handling_codes") && alert_json["handling_codes"].is_array()) {
                web::json::array json_array = alert_json["handling_codes"].as_array();
                for (auto handling_codes_json = json_array.begin();
                     handling_codes_json != json_array.end(); ++handling_codes_json) {
                    if (handling_codes_json->is_string()) {
                        alert.validate_handling_code(handling_codes_json->as_string());
                    }
                }
            }

            if (alert_json.has_field("source") && alert_json["source"].is_string())
                alert.validate_source(alert_json["source"].as_string());

            if (alert_json.has_field("note") && alert_json["note"].is_string())
                alert.validate_note(alert_json["note"].as_string());

            if (alert_json.has_field("references") && alert_json["references"].is_string())
                alert.validate_references(alert_json["references"].as_string());
            if (alert_json.has_field("incidents") && alert_json["incidents"].is_string())
                alert.validate_incidents(alert_json["incidents"].as_string());

            return alert;
        } catch (std::exception &e) {
            return std::nullopt;
        }
    }

    friend bool operator==(const Alert &a, const Alert &b);
};

/// Necessary for comparing if two entities are equal.
inline bool operator==(const Alert &a, const Alert &b) {
    return a.identifier__ == b.identifier__;
}
}
#endif // ALERT_H