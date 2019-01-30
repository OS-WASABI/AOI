/**
 *  Alert Originator Groups API Endpoint Controller
 *
 * Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        aog_controller.cpp
 * @authors     Shawn Hulce
 * @date        January 2019
 */

#include "config_controller.hpp"

namespace aoi_rest {
    void ConfigController::InitHandlers() {
        listener__.support(methods::GET, std::bind(&ConfigController::HandleGet, this, std::placeholders::_1));
        listener__.support(methods::PUT, std::bind(&ConfigController::HandlePut, this, std::placeholders::_1));
        listener__.support(methods::POST, std::bind(&ConfigController::HandlePost, this, std::placeholders::_1));
        listener__.support(methods::DEL, std::bind(&ConfigController::HandleDelete, this, std::placeholders::_1));
    }

    void ConfigController::HandleGet(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void ConfigController::HandleDelete(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void ConfigController::HandlePost(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void ConfigController::HandlePut(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

}  // namespace aoi_rest
