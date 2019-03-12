// Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * @file        cap.cpp
 * @authors     Ross Arcemont
 * @date        February, 2019
 */

#include "cap.hpp"

///Creates a CAP message from a provided CAP object.
/**
 * Takes in a CAP object containing all necessary data to create a
 * CAP XML document. This function assumes that all necessary validation
 * of the CAP object data has occurred already, as this function does not
 * provide any such validation.
 * @param data_input        CAP object providing all necessary data
 * @param cap_filename      Filepath and filename of the CAP document to be saved
 */
void CAP::create_cap_doc(aoi_rest::Alert data_input, std::string cap_filename) {
    // Creating SOAP envelope for the CAP message
    pugi::xml_document cap_doc;
    auto declaration_node = cap_doc.append_child(pugi::node_declaration);
    declaration_node.append_attribute("version") = "1.0";
    declaration_node.append_attribute("encoding") = "utf-8";

    auto root_node = cap_doc.append_child("SOAP-ENV:Envelope");
    root_node.append_attribute("xmlns:SOAP-ENV") = "http://www.w3.org/2001/12/soap-envelope";
    root_node.append_attribute("SOAP-ENV:encodingStyle") = "http://www.w3.org/2001/12/soap-encoding";

    auto soap_body = root_node.append_child("SOAP-ENV:Body");
    // Creating CAP message main structure with necessary data
    auto alert = soap_body.append_child("alert");
    alert.append_attribute("xmlns") = "urn:oasis:names:tc:emergency:cap:1.2";

    auto identifier = alert.append_child("identifier");
    identifier.text().set(data_input.identifier.value().c_str());

    auto sender = alert.append_child("sender");
    sender.text().set(data_input.sender);

    auto sent = alert.append_child("sent");
    sent.text().set(data_input.sent_time);

    auto status = alert.append_child("status");
    status.text().set(data_input.status);

    auto msg_type = alert.append_child("msgType");
    msg_type.text().set(data_input.msg_type);

    if (data_input.source.compare("") != 0) {
        auto source = alert.append_child("source");
        source.text().set(data_input.source);
    }

    auto scope = alert.append_child("scope");
    scope.text().set(data_input.scope);

    if (data_input.scope.compare("Restricted") == 0) {
        auto restriction = alert.append_child("restriction");
        restriction.text().set(data_input.restriction);
    }

    if (data_input.scope.compare("Private") == 0 || ((data_input.scope.compare("Public") == 0 || data_input.scope.compare("Restricted") == 0) && data_input.addresses.compare("") != 0)) {
        auto addresses = alert.append_child("addresses");
        addresses.text().set(data_input.addresses);
    }

    for (int i = 0; i < data_input.handling_codes.size(); i++) {
        auto code = alert.append_child("code");
        code.text().set(data_input.handling_codes.at(i));
    }

    if (data_input.note.compare("") != 0 || (data_input.status.compare("Exercise") == 0 && data_input.msg_type.compare("Error") == 0)) {
        auto note = alert.append_child("note");
        note.text().set(data_input.note);
    }

    if (data_input.references.compare("") != 0) {
        auto references = alert.append_child("references");
        references.text().set(data_input.references);
    }

    if (data_input.incidents.compare("") != 0) {
        auto incidents = alert.append_child("incidents");
        incidents.text().set(data_input.incidents);
    }

    // Creating info blocks with necessary data
    for (int i = 0; i < data_input.info.size(); i++) {
        auto info = alert.append_child("info");
        auto language = info.append_child("language");
        if (data_input.info.at(i).language.compare("") == 0) {
            language.text().set("en-US");
        } else {
            language.text().set(data_input.info.at(i).language);
        }

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

        if (data_input.info.at(i).audience.compare("") != 0) {
            auto audience = info.append_child("audience");
            audience.text().set(data_input.info.at(i).audience);
        }

        for (int j = 0; j < data_input.info.at(i).event_codes.size(); j++) {
            auto event_code = info.append_child("eventCode");
            event_code.text().set(data_input.info.at(i).event_codes.at(j));
        }

        auto effective = info.append_child("effective");
        if (data_input.info.at(i).effective.compare("") == 0) {
            effective.text().set(data_input.sent_time);
        } else {
            effective.text().set(data_input.info.at(i).effective_time);
        }

        if (data_input.info.at(i).onset.compare("") != 0) {
            auto onset = info.append_child("onset");
            onset.text().set(data_input.info.at(i).onset_time);
        }

        auto expires = info.append_child("expires");
        if (data_input.info.at(i).expires.compare("") == 0) {
            // TODO(Ross): Determine default behavior
        } else {
            expires.text().set(data_input.info.at(i).expire_time);
        }

        if (data_input.info.at(i).sender_name.compare("") != 0) {
            auto sender_name = info.append_child("senderName");
            sender_name.text().set(data_input.info.at(i).sender_name);
        }

        if (data_input.info.at(i).headline.compare("") != 0) {
            auto headline = info.append_child("headline");
            headline.text().set(data_input.info.at(i).headline);
        }

        if (data_input.info.at(i).description.compare("") != 0) {
            auto description = info.append_child("description");
            description.text().set(data_input.info.at(i).description);
        }

        if (data_input.info.at(i).instruction.compare("") != 0) {
            auto instruction = info.append_child("instruction");
            instruction.text().set(data_input.info.at(i).instruction);
        }

        if (data_input.info.at(i).web_url.compare("") != 0) {
            auto web = info.append_child("web");
            web.text().set(data_input.info.at(i).web_url);
        }

        if (data_input.info.at(i).contact.compare("") != 0) {
            auto contact = info.append_child("contact");
            contact.text().set(data_input.info.at(i).contact);
        }

        for (int j = 0; j < data_input.info.at(i).parameters.size(); j++) {
            auto parameter = info.append_child("parameter");
            parameter.text().set(data_input.info.at(i).parameters.at(j));
        }

        // Creating resource blocks with necessary data
        for (int j = 0; j < data_input.info.at(i).resources.size(); j++) {
            auto resource = info.append_child("resource");
            auto resource_desc = resource.append_child("resourceDesc");
            resource_desc.text().set(data_input.info.at(i).resources.at(j).resource_description);

            auto mime_type = resource.append_child("mimeType");
            mime_type.text().set(data_input.info.at(i).resources.at(j).mime_type);

            if (data_input.info.at(i).resources.at(j).size > 0) {
                auto size = resource.append_child("size");
                size.text().set(data_input.info.at(i).resources.at(j).size);
            }

            if (data_input.info.at(i).resources.at(j).uri.compare("") != 0) {
                auto uri = resource.append_child("uri");
                uri.text().set(data_input.info.at(i).resources.at(j).uri);
            }

            if (data_input.info.at(i).resources.at(j).dereferenced_uri.compare("") != 0) {
                auto dereferenced_uri = resource.append_child("derefUri");
                dereferenced_uri.text().set(data_input.info.at(i).resources.at(j).dereferenced_uri);
            }

            if (data_input.info.at(i).resources.at(j).digest.compare("") != 0) {
                auto digest = resource.append_child("digest");
                digest.text().set(data_input.info.at(i).resources.at(j).digest);
            }
        }

        // Creating area blocks with necessary data
        for (int j = 0; j < data_input.info.at(i).areas.size(); j++) {
            auto area = info.append_child("area");
            auto area_desc = area.append_child("areaDesc");
            area_desc.text().set(data_input.info.at(i).areas.at(j).area_description);

            for (int k = 0; k < data_input.info.at(i).areas.at(j).polygons.size(); k++) {
                auto polygon = area.append_child("polygon");
                polygon.text().set(data_input.info.at(i).areas.at(j).polygons.at(k));
            }

            for (int k = 0; k < data_input.info.at(i).areas.at(j).circles.size(); k++) {
                auto circle = area.append_child("circle");
                circle.text().set(data_input.info.at(i).areas.at(j).circles.at(k));
            }

            for (int k = 0; k < data_input.info.at(i).areas.at(j).geocode.size(); k++) {
                auto geocode = area.append_child("geocode");
                geocode.text().set(data_input.info.at(i).areas.at(j).geocode.at(k));
            }

            // TODO(Ross): Determine if parsing the lower limit from <ceiling> is necessary.
            if (data_input.info.at(i).areas.at(j).altitude.compare("") != 0) {
                auto altitude = area.append_child("altitude");
                altitude.text().set(data_input.info.at(i).areas.at(j).altitude);
            }

            if (data_input.info.at(i).areas.at(j).altitude.compare("") != 0 && data_input.info.at(i).areas.at(j).ceiling.compare("") != 0) {
                auto ceiling = area.append_child("ceiling");
                ceiling.text().set(data_input.info.at(i).areas.at(j).ceiling);
            }
        }
    }
}