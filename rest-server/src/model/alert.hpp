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
#include <time.h>
#include <regex>
#include <cpprest/json.h>

namespace aoi_soap {
// Allowed codes as per CAP 1.2.
static const std::array<std::string, 5> status_codes{"Actual", "Exercise", "System", "Test", "Draft"};
static const std::array<std::string, 5> msg_type_codes{"Alert", "Update", "Cancel", "Ack", "Error"};
static const std::array<std::string, 3> scope_codes{"Public", "Restricted", "Private"};

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
    // Conditional elements
    std::optional<std::string> restriction__;
    std::optional<std::vector<std::string>> addresses__;      // Required when scope is "Private", optional otherwise.
    // Optional elements
    std::optional<std::vector<std::string>> handling_codes__;
    std::optional<std::string> source__;
    std::optional<std::string> note__;
    std::optional<std::vector<std::string>> references__;
    std::optional<std::vector<std::string>> incidents__;
//    std::optional<std::vector<AlertInfo>> info__;

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
    bool validate_addresses(const std::vector<std::string> addresses);

    /**
    * Validates an Alert's handling_codes elements. If valid, the value for thevector of
    * strings. If invalid, returns std::nullopt.
    *
    * @return bool
    *
    */
    bool validate_handling_codes(const std::vector<std::string> handling_codes);

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
    bool validate_references(const std::vector<std::string> references);

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
    bool validate_incidents(const std::vector<std::string> incidents);

    // comments are for the weak
    std::optional<std::string> get_identifier();

    std::optional<std::string> get_sender();

    std::optional<std::time_t> get_sent_time();

    std::optional<std::string> get_status();

    int get_status_enum();

    std::optional<std::string> get_msg_type();

    int get_msg_type_enum();

    std::optional<std::string> get_scope();

    int get_scope_enum();

public:
    Alert();

    /**
     * Creates an optional<Alert> from a web::json::value.
     *
     * If the json value does not contain all required fields,
     * a std::nullopt is returned.
     *
     * @return std::optional<Alert>
     */
    //std::optional<std::vector<AlertInfo>> get_info();

    static std::optional<Alert> from_json(web::json::value &alert_json);

    friend bool operator==(const Alert &a, const Alert &b);
};

/// Necessary for comparing if two entities are equal.
inline bool operator==(const Alert &a, const Alert &b) {
    return a.identifier__ == b.identifier__;
}
} // namespace aoi_rest
#endif // ALERT_H