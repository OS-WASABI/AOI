//
// Created by mike on 4/15/19.
//

#ifndef AOI_REST_SERVER_ALERT_CONVERSION_HPP
#define AOI_REST_SERVER_ALERT_CONVERSION_HPP

#include <logger.hpp>
#include <logger_interface.hpp>
#include "log_level.hpp"
#include "../gSoapFiles/client/soapH.h"
#include <time.h>
#include <regex>
#include "alert.hpp"

namespace aoi_soap {
bool json_to_gsoap(web::json::value &alert_json, _ns4__alert &alert) {
    try {
        if (auto alert = Alert::from_json(alert_json)) {

        } else {
            return false;
        }
        return true;
    } catch (std::exception &e) {
        return false;
    }
}
}
#endif //AOI_REST_SERVER_ALERT_CONVERSION_HPP
