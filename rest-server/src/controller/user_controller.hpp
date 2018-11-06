// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H
#include <controller.hpp>
#include "data_access_object.hpp"
using aoi_rest::DataAccessObject;

namespace aoi_rest {
class UserController: public Controller {
  public: 
    UserController() : Controller() {
      DataAccessObject::Instance().AddUser(User {"Kris Hoadley", 17, "TheBestLikeNoOneEverWas"});
      DataAccessObject::Instance().AddUser(User {"Shawn Hulce", 12, "ecluhwordpass!4"});
    }
    ~UserController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    void HandleGet(http_request message) override;
    void HandlePut(http_request message) override;
    void HandlePost(http_request message) override;
    void HandleDelete(http_request message) override;
};
}
#endif // USER_CONTROLLER_H
