// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include "another_controller.hpp"

namespace aoi_rest {
void AnotherController::InitHandlers() {
    listener__.support(methods::GET,
            std::bind(&AnotherController::HandleGet,
            this, std::placeholders::_1));
}
void AnotherController::HandleGet(http_request message) {
    // This is an example of how to extract information from the 
    // http_request message and form a json return
    auto response = json::value::object();
    response["uri"] = json::value::string(message.relative_uri().to_string());
    response["headers"] = json::value::object();
    for (auto& header: message.headers())
        response["headers"][header.first] = json::value::string(header.second);
    response["method"] = json::value::string(message.method());
    response["request dump"] = json::value::string(message.to_string());
    message.reply(status_codes::OK, response);
}
void AnotherController::HandlePut(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::PUT));
}
void AnotherController::HandlePost(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::POST));
}
void AnotherController::HandleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::DEL));
}
}  // namespace aoi_rest
