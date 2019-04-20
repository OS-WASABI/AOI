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
#include "../gSoapFiles/client/CAPSoapHttp.nsmap"
#include "../gSoapFiles/client/soapH.h"
#include "../gSoapFiles/client/soapStub.h"
#include "../gSoapFiles/client/soapCAPSoapHttpProxy.h"
#include "../services/alert_conversion.hpp"
using aoi_rest::LogLevel;

namespace aoi_soap {

    const char server_address[] = "https://wasabi.group/cadg/soap";

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
             web::json::value body_json = message.extract_json().get();
            _ns4__alert incoming_alert;
            if (aoi_soap::json_to_gsoap(body_json, incoming_alert)) {
                struct soap context = *soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
                CAPSoapHttpProxy server;
                _ns1__postCAPRequestTypeDef request;
                _ns1__postCAPResponseTypeDef response;
                request.ns4__alert = &incoming_alert;
                request.soap_serialize(&context);
                server.CAPSoapHttpProxy_init(SOAP_XML_INDENT, SOAP_XML_INDENT);
                server.soap_endpoint = server_address;
                server.postCAP(&request, response);

                if (!server.soap->error) {
                    logger__.Log(LogLevel::DEBUG, std::string("Sent Alert Successfully. Return: ") +
                    *response.postCAPReturn, "SoapController", "HandlePost");
                    message.reply(status_codes::Created);
                } else {
                    message.reply(status_codes::BadRequest);
                }
            } else {
                message.reply(status_codes::BadRequest);
            }
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
