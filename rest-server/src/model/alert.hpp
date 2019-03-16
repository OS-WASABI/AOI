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
    std::optional<std::string> identifier;
    std::optional<std::string> sender;
    std::optional<std::time_t> sent_time;
    std::optional<std::string> status;
    std::optional<std::string> msg_type;
    std::optional<std::string> scope;
    std::optional<std::vector<AlertInfo>> info;
    // Conditional elements
    std::optional<std::string> restriction;
    std::optional<std::string> addresses;      // Required when scope is "Private", optional otherwise.
    // Optional elements
    std::optional<std::vector<std::string>> handling_codes;
    std::optional<std::string> source;
    std::optional<std::string> note;
    std::optional<std::string> references;
    std::optional<std::string> incidents;

    /**
    * Validates an Alert's identifier field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_identifier(web::json::value &alert_json);

    /**
    * Validates an Alert's sender field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_sender(web::json::value &alert_json);

    /**
    * Validates an Alert's sent_time field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_sent_time(web::json::value &alert_json);

    /**
    * Validates an Alert's status field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_status(web::json::value &alert_json);

    /**
    * Validates an Alert's msg_type field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_msg_type(web::json::value &alert_json);

    /**
    * Validates an Alert's scope field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_scope(web::json::value &alert_json);

    /**
    * Validates an Alert's info arary. If valid, the value for thevector of AlertInfo
    * objects. If invalid, returns std::nullopt.
    *
    * @return bool
    *
    */
    bool validate_info(web::json::value &alert_json);

    /**
    * Validates an Alert's restriction field. If valid, the value for the
    * element is set and the function returns true.
    *
    * Used when scope is "Restricted".
    *
    * @return bool
    *
    */
    bool validate_restriction(web::json::value &alert_json);

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
    bool validate_addresses(web::json::value &alert_json);

    /**
    * Validates an Alert's handling_codes elements. If valid, the value for thevector of
    * strings. If invalid, returns std::nullopt.
    *
    * @return bool
    *
    */
    bool validate_handling_codes(web::json::value &alert_json);

    /**
    * Validates an Alert's source field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_source(web::json::value &alert_json);

    /**
    * Validates an Alert's note field. If valid, the value for the
    * element is set and the function returns true.
    *
    * @return bool
    *
    */
    bool validate_note(web::json::value &alert_json);

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
    bool validate_references(web::json::value &alert_json);

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
    bool validate_incidents(web::json::value &alert_json);

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
            alert.validate_identifier(alert_json);
            alert.validate_sender(alert_json);
            alert.validate_status(alert_json);
            alert.validate_msg_type(alert_json);
            alert.validate_scope(alert_json);
            alert.validate_info(alert_json);
            alert.validate_restriction(alert_json);
            alert.validate_addresses(alert_json);
            alert.validate_handling_codes(alert_json);
            alert.validate_source(alert_json);
            alert.validate_note(alert_json);
            alert.validate_references(alert_json);
            alert.validate_incidents(alert_json);
            return alert;
        } catch (std::exception &e) {
            return std::nullopt;
        }
    }

    friend bool operator==(const Alert &a, const Alert &b);
};

/// Necessary for comparing if two entities are equal.
inline bool operator==(const Alert &a, const Alert &b) {
    return a.identifier == b.identifier;
}
}
#endif // ALERT_H