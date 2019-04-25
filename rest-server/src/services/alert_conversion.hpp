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
bool json_to_gsoap(web::json::value &alert_json, _ns4__alert &gsoap_alert) {
    LoggerInterface& logger__(Logger::Instance());
    try {
        if (auto alert = Alert::from_json(alert_json)) {
            if (alert.value().get_identifier())
                gsoap_alert.identifier = alert.value().get_identifier().value();
            if (alert.value().get_sender())
                gsoap_alert.sender = alert.value().get_sender().value();
            if (alert.value().get_sent_time())
                gsoap_alert.sent = alert.value().get_sent_time().value();
            if (alert.value().get_status_enum() >= 0)
                gsoap_alert.status = (_ns4__alert_status)alert.value().get_status_enum();
            if (alert.value().get_msg_type_enum() >= 0)
                gsoap_alert.msgType = (_ns4__alert_msgType)alert.value().get_msg_type_enum();
            if (alert.value().get_scope_enum() >= 0)
                gsoap_alert.scope = (_ns4__alert_scope)alert.value().get_scope_enum();
        } else {
            logger__.Log(aoi_rest::LogLevel::DEBUG, "Alert not created from json.", "alert_conversion.hpp", "json_to_gsoap");
            //Mock data until we fix it.
            gsoap_alert.identifier = "ZingZang!";
            gsoap_alert.sender = "Your mother.";
            gsoap_alert.sent = 0;
            gsoap_alert.status = (_ns4__alert_status)0;
            gsoap_alert.msgType = (_ns4__alert_msgType)0;
            gsoap_alert.scope = (_ns4__alert_scope)0;

            return true;
            //return false;
        }
        return true;
    } catch (std::exception &e) {
        logger__.Log(aoi_rest::LogLevel::DEBUG, e.what(), "alert_conversion.hpp", "json_to_gsoap");
        return false;
    }
}
}
#endif //AOI_REST_SERVER_ALERT_CONVERSION_HPP
