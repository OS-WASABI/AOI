// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley

#ifndef AOI_REST_SERVER_ALERT_CONTROLLER_HPP
#define AOI_REST_SERVER_ALERT_CONTROLLER_HPP

#include "controller.hpp"
#include "data_access_interface.hpp"


namespace aoi_rest {
    class AlertController : public Controller{
    public:
        AlertController(DataAccessInterface& input_dao) : dao__(input_dao), Controller() {};
        ~AlertController() {};

        virtual void InitHandlers() override;
        virtual void HandleGet(http_request message) override;
        virtual void HandlePut(http_request message) override;
        virtual void HandlePost(http_request message) override;
        virtual void HandleDelete(http_request message) override;

    private:
        DataAccessInterface& dao__;

    };
}  // namespace aoi_rest


#endif //AOI_REST_SERVER_ALERT_CONTROLLER_HPP
