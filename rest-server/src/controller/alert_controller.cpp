// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley

#include "alert_controller.hpp"
#include <string>
#include <vector>

namespace aoi_rest {

    void AlertController::InitHandlers() {
        listener__.support(methods::GET, std::bind(&AlertController::HandleGet, this, std::placeholders::_1));
        listener__.support(methods::PUT, std::bind(&AlertController::HandlePut, this, std::placeholders::_1));
        listener__.support(methods::POST, std::bind(&AlertController::HandlePost, this, std::placeholders::_1));
        listener__.support(methods::DEL, std::bind(&AlertController::HandleDelete, this, std::placeholders::_1));
    }

    void AlertController::HandleGet(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void AlertController::HandlePost(http_request message) {
        try {
            auto message_body = message.extract_json().get();
            // TODO: Create Alert Object Here (As gSOAP alert?)
            bool valid = true;
            // TODO: Placeholder for verification. Would this happen here or in object creation?
            if (!message_body.has_field("Description")) { valid = false; }
            if (valid) {
                message.reply(status_codes::OK);
            } else {
                message.reply(status_codes::BadRequest);
            }
        } catch(std::exception& e) {
            message.reply(status_codes::InternalError, e.what());
        }
    }

    void AlertController::HandlePut(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void AlertController::HandleDelete(http_request message) {
        message.reply(status_codes::NotImplemented);
    }
}
