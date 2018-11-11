// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef EXAMPLE_CONTROLLER_H
#define EXAMPLE_CONTROLLER_H
#include <controller.hpp>

namespace aoi_rest {
class ExampleController: public Controller {
  public: 
    ExampleController() : Controller() { }
    ~ExampleController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    void HandleGet(http_request message) override;
    void HandlePut(http_request message) override;
    void HandlePost(http_request message) override;
    void HandleDelete(http_request message) override;
};
}
#endif // EXAMPLE_CONTROLLER_H
