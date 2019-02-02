// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
// Created by Shawn on 11/26/2018.
//

#ifndef SOAP_CONTROLLER_HPP
#define SOAP_CONTROLLER_HPP
#include <controller.hpp>
#include <data_access_interface.hpp>
#include "../../gSoapFiles/CAP/soapH.h"
using aoi_rest::DataAccessInterface;
using aoi_rest::LoggerInterface;
using aoi_rest::Logger;

namespace aoi_soap {
class SoapController: public aoi_rest::Controller {

    public:
        SoapController(aoi_rest::DataAccessInterface& dao__) : dao__(dao__),
                        logger__(Logger::Instance()), Controller() {

        }
        ~SoapController() {}

    void InitHandlers() override;
    void HandleGet(http_request message) override;
    void HandlePut(http_request message) override;
    void HandlePost(http_request message) override;
    void HandleDelete(http_request message) override;
    private:
    DataAccessInterface& dao__;
    LoggerInterface& logger__;
};

} //end aoi_soap
#endif //CADG_REST_SERVER_SOAP_CONTROLLER_HPP
