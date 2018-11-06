// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <iostream>
#include "user_controller.hpp"

namespace aoi_rest {
void UserController::InitHandlers() {
    listener__.support(methods::GET, std::bind(&UserController::HandleGet, this, std::placeholders::_1));
    listener__.support(methods::PUT, std::bind(&UserController::HandlePut, this, std::placeholders::_1));
    listener__.support(methods::POST, std::bind(&UserController::HandlePost, this, std::placeholders::_1));
    listener__.support(methods::DEL, std::bind(&UserController::HandleDelete, this, std::placeholders::_1));
}
void UserController::HandleGet(http_request message) {
    try {
        auto path = RequestPath(message);
        auto response = json::value::object();
        auto users = DataAccessObject::Instance().GetUsers();
        response["users"] = json::value::object();
        for (auto& user : users) {
            auto user_json  = json::value::object();
            user_json["name"] = json::value::string(user.name);
            user_json["password"] = json::value::string(user.password);
            response["users"][std::to_string(user.id)] = user_json;
        }
        message.reply(status_codes::OK, response);
    } catch (std::exception&  e) {  // for testing purposes
        message.reply(status_codes::InternalError, json::value::string(e.what()));
    }
}
void UserController::HandlePut(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::PUT));
}
void UserController::HandlePost(http_request message) {
    try {
        // parse body and extract user data
        const json::value body_json = message.extract_json().get();
        // validate user data
        // if valid add using dao
        auto users_json = body_json.at("users").as_object();
        for (auto iter = users_json.cbegin(); iter != users_json.cend(); ++iter) {
            auto &key = iter->first;
            const json::value &value = iter->second;
            if (value.is_object()) {
                auto user_json = value.as_object();
                DataAccessObject::Instance().AddUser(
                        User {user_json["name"].as_string(),
                        std::stoi(key), user_json["password"].as_string()});
            }
        }
        // respond with successfully created (201)
        message.reply(status_codes::Created);
    } catch (std::exception&  e) {  // for testing purposes
        message.reply(status_codes::BadRequest, e.what());
    }
}
void UserController::HandleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::DEL));
}
}  // namespace aoi_rest
