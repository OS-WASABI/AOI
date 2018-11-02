// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include "example_controller.hpp"
#include "std_aoi_rest.hpp"

namespace aoi_rest {
void ExampleController::InitHandlers() {
    listener__.support(methods::GET,
            std::bind(&ExampleController::HandleGet,
            this, std::placeholders::_1));
    listener__.support(methods::PUT,
            std::bind(&ExampleController::HandlePut,
            this, std::placeholders::_1));
    listener__.support(methods::POST,
            std::bind(&ExampleController::HandlePost,
            this, std::placeholders::_1));
    listener__.support(methods::DEL,
            std::bind(&ExampleController::HandleDelete,
            this, std::placeholders::_1));
}
void ExampleController::HandleGet(http_request message) {
    auto path = RequestPath(message);
    if (!path.empty()) {
        if (path[0] == "service" && path[1] == "test") {
            auto response = json::value::object();
            response["version"] = json::value::string("0.1.1");
            response["status"] = json::value::string("ready!");
            message.reply(status_codes::OK, response);
        }
    } else {
        message.reply(status_codes::NotFound);
    }
}
void ExampleController::HandlePut(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::PUT));
}
void ExampleController::HandlePost(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::POST));
}
void ExampleController::HandleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, ResponseNotImpl(methods::DEL));
}
}  // namespace aoi_rest
