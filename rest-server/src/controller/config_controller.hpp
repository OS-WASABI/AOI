/**
 *  AOI configuration API Endpoint Controller
 *
 * Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        config_controller.hpp
 * @authors     Shawn Hulce
 * @date        January 2019
 */

#ifndef AOI_REST_SERVER_CONFIG_CONTROLLER_HPP
#define AOI_REST_SERVER_CONFIG_CONTROLLER_HPP
#include <controller.hpp>

namespace aoi_rest {
    class ConfigController : public Controller{
    public:
        ConfigController() : Controller() { }
        ~ConfigController() { }

        void InitHandlers() override;

        void HandleGet(http_message request) override;
        void HandlePost(http_message request) override;
        void HandlePut(http_message request) override;
        void HandleDelete(http_message request) override;

} // namespace aoi_rest


#endif //AOI_REST_SERVER_CONFIG_CONTROLLER_HPP
