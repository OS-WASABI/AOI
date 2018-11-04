// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef ANOTHER_CONTROLLER_H
#define ANOTHER_CONTROLLER_H
#include <controller.hpp>

namespace aoi_rest {
class AnotherController: public Controller {
  public: 
    AnotherController() : Controller() { }
    ~AnotherController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    void HandleGet(http_request message) override;
    void HandlePut(http_request message) override;
    void HandlePost(http_request message) override;
    void HandleDelete(http_request message) override;
};
}
#endif // ANOTHER_CONTROLLER_H
