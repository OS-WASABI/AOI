//
// Created by Ross on 1/31/2019.
//

#include "cap.hpp"

CAP::CAP() {
    //TODO: Verify this information
    //Default node attributes
    declaration_node.append_attribute("version") = "1.0";
    declaration_node.append_attribute("encoding") = "utf-8";
    root_node.append_attribute("xmlns:SOAP-ENV") = "\"http://www.w3.org/2001/12/soap-envelope\"";
    root_node.append_attribute("SOAP-ENV:encodingStyle") = "\"http://www.w3.org/2001/12/soap-encoding\"";
    alert.append_attribute("xmlns") = "\"urn:oasis:names:tc:emergency:cap:1.2\"";
}

void CAP::create_cap_doc(aoi_rest::Alert data_input, std::string cap_filename) {
    identifier.text().set(data_input.identifier);
    sender.text().set(data_input.sender);
    sent.text().set(data_input.sent_time);
    status.text().set(data_input.status);
    msg_type.text().set(data_input.msg_type);
    source.text().set(data_input.source);
    scope.text().set(data_input.scope);
    restriction.text().set(data_input.restriction);
    addresses.text().set(data_input.addresses);

    for (int i = 0; i < data_input.handling_codes.size(); i++) {
        auto code = alert.append_child("code");
        code.text().set(data_input.handling_codes.at(i));
    }

    note.text().set(data_input.note);
    references.text().set(data_input.references);
    incidents.text().set(data_input.incidents);

    for (int i = 0; i < data_input.info.size(); i++) {
        auto info = alert.append_child("info");
        auto language = info.append_child("language");
        language.text().set(data_input.info.at(i).language);

        for (int j = 0; j < data_input.info.at(i).categories.size(); j++) {
            auto category = info.append_child("category");
            category.text().set(data_input.info.at(i).categories.at(j));
        }

        auto event = info.append_child("event");
        event.text().set(data_input.info.at(i).event);

        for (int j = 0; j < data_input.info.at(i).response_types.size(); j++) {
            auto response_type = info.append_child("responseType");
            response_type.text().set(data_input.info.at(i).response_types.at(j));
        }

        auto urgency = info.append_child("urgency");
        urgency.text().set(data_input.info.at(i).urgency);

        auto severity = info.append_child("severity");
        severity.text().set(data_input.info.at(i).severity);

        auto certainty = info.append_child("certainty");
        certainty.text().set(data_input.info.at(i).certainty);

        auto audience = info.append_child("audience");
        audience.text().set(data_input.info.at(i).audience);

        for (int j = 0; j < data_input.info.at(i).event_codes.size(); j++) {
            auto event_code = info.append_child("eventCode");
            event_code.text().set(data_input.info.at(i).event_codes.at(j));
        }

        auto effective = info.append_child("effective");
        effective.text().set(data_input.info.at(i).effective_time);

        auto onset = info.append_child("onset");
        onset.text().set(data_input.info.at(i).onset_time);

        auto expires = info.append_child("expires");
        expires.text().set(data_input.info.at(i).expire_time);

        auto sender_name = info.append_child("senderName");
        sender_name.text().set(data_input.info.at(i).sender_name);

        auto headline = info.append_child("headline");
        headline.text().set(data_input.info.at(i).headline);

        auto description = info.append_child("description");
        description.text().set(data_input.info.at(i).description);

        auto instruction = info.append_child("instruction");
        instruction.text().set(data_input.info.at(i).instruction);

        auto web = info.append_child("web");
        web.text().set(data_input.info.at(i).web_url);

        auto contact = info.append_child("contact");
        contact.text().set(data_input.info.at(i).contact);

        for (int j = 0; j < data_input.info.at(i).parameters.size(); j++) {
            auto parameter = info.append_child("parameter");
            parameter.text().set(data_input.info.at(i).parameters.at(j));
        }

        for (int j = 0; j < data_input.info.at(i).resources.size(); j++) {
            //TODO: Create resource blocks
        }

        for (int j = 0; j < data_input.info.at(i).areas.size(); j++) {
            //TODO: Create area blocks
        }
    }
}