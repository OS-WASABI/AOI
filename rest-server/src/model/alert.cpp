// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Implementation code for alert classes.
 *
 * @file        alert.cpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */

/**
* Validates an Alert's identifier field. If valid, the value for the
* element is set and the function returns true.
*
* @return bool
*
*/

#include <alert.hpp>

namespace aoi_rest {

bool Alert::validate_identifier(const std::string &identifier) {
    if (identifier.find_first_of(restricted_chars) == std::string::npos) {
        identifier__ = identifier;
        return true;
    }
    return false;
}

bool Alert::validate_sender(const std::string &sender) {
        if (sender.find_first_of(restricted_chars) == std::string::npos) {
            sender__ = sender;
            return true;
        }
    return false;
}

bool Alert::validate_sent_time(const time_t &sent_time) {
    sent_time__ = sent_time;
    return true;
}

bool Alert::validate_status(const std::string &status) {
    std::string status_proper = status;
    for (std::string::size_type i = 0; i < status_proper.length(); ++i) {
        if (i == 0)
            status_proper[i] = std::toupper(status_proper[i]);
        else
            status_proper[i] = std::tolower(status_proper[i]);
    }
    for (auto status_code = status_codes.begin(); status_code != status_codes.end(); status_code++) {
        if (status_proper == *status_code) {
            status__ = status_proper;
            return true;
        }
    }
    return false;
}

bool Alert::validate_msg_type(const std::string &msg_type) {
    std::string msg_type_proper = msg_type;
    for (std::string::size_type i = 0; i < msg_type_proper.length(); ++i) {
        if (i == 0)
            msg_type_proper[i] = std::toupper(msg_type_proper[i]);
        else
            msg_type_proper[i] = std::tolower(msg_type_proper[i]);
    }
    for (auto msg_type_code = msg_type_codes.begin();
        msg_type_code != msg_type_codes.end(); msg_type_code++) {
        if (msg_type_proper == *msg_type_code) {
            msg_type__ = msg_type_proper;
            return true;
        }
    }
    return false;
}

bool Alert::validate_scope(const std::string &scope) {
    std::string scope_proper = scope;
    for (std::string::size_type i = 0; i < scope_proper.length(); ++i) {
        if (i == 0)
            scope_proper[i] = std::toupper(scope_proper[i]);
        else
            scope_proper[i] = std::tolower(scope_proper[i]);
    }
    for (auto scope_code = scope_codes.begin(); scope_code != scope_codes.end(); scope_code++) {
        if (scope_proper == *scope_code) {
            scope__ = scope_proper;
            return true;
        }
    }
    return false;
}

bool Alert::validate_restriction(const std::string restriction) {
    restriction__ = restriction;
    return true;
}

bool Alert::validate_addresses(const std::string addresses) {
    if (scope__.value() == "Private" && addresses == "")
        return false;
    //TODO(Mike): Parse addresses
    return true;
}

bool Alert::validate_handling_code(const std::string handling_code) {
    //TODO(Mike): Parse addresses
    handling_codes__.value().push_back(handling_code);
    return true;
}

bool Alert::validate_source(const std::string source) {
      source__ = source;
      return true;
}

bool Alert::validate_note(const std::string note) {
    note__ = note;
    return true;
}

bool Alert::validate_references(const std::string references) {
    //TODO(Mike): Validate references
    references__ = references;
    return true;
}

bool Alert::validate_incidents(const std::string incidents) {
    incidents__ = incidents;
    return true;
}
}