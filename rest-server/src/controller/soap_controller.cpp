/// Simple SOAP endpoint for testing.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
                    Shawn Hulce, Michael McCulley

 * @file        soap_controller.cpp
 * @authors     Shawn Hulce
 * @date        January, 2019
 */
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "soap_controller.hpp"
#include "log_level.hpp"
#include "../gSoapFiles/client/ns2.nsmap"
using aoi_rest::LogLevel;

namespace aoi_soap {
    void SoapController::InitHandlers() {
        listener__.support(methods::GET, std::bind(&SoapController::HandleGet, this, std::placeholders::_1));
        listener__.support(methods::PUT, std::bind(&SoapController::HandlePut, this, std::placeholders::_1));
        listener__.support(methods::POST, std::bind(&SoapController::HandlePost, this, std::placeholders::_1));
        listener__.support(methods::DEL, std::bind(&SoapController::HandleDelete, this, std::placeholders::_1));
    }

    void SoapController::HandlePost(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 1);
        try {
            auto body = message.extract_string().get();
            logger__.Log(LogLevel::DEBUG, "JSON Received: " + body, "SoapController", "HandlePost");

            // TODO(Kris): parse CAP json from string
            const json::value body_json = message.extract_json().get();
            // const json::object body_object = body_json.as_object();
            
            // TODO(Kris): validate CAP

            // TODO(Kris): use SOAP client to send CAP to CADG

            message.reply(status_codes::OK, "Recieved: " + body);
        } catch (std::exception& e) {
            message.reply(status_codes::BadRequest);
        }
    }
    void SoapController::HandleGet(http_request message) {
        message.reply(status_codes::NotImplemented);
    }
    void SoapController::HandlePut(http_request message) {
        message.reply(status_codes::NotImplemented);
    }
    void SoapController::HandleDelete(http_request message) {
        message.reply(status_codes::NotImplemented);
    }
}  // namespace aoi_soap
