// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef DATA_ACCESS_OBJECT_H
#define DATA_ACCESS_OBJECT_H
#include <string>
#include <vector>
#include "user.hpp"
#include "data_access_interface.hpp"

namespace aoi_rest {
class DataAccessObject : DataAccessInterface {
  public:
    static DataAccessObject& Instance();
    DataAccessObject(DataAccessObject const&) = delete;
    void operator=(DataAccessObject const&) = delete;

    std::vector<User> GetUsers() override;
    bool RemoveUser(User user) override;
    void AddUser(User user) override;
  private:
    DataAccessObject() { }
    std::vector<User> users__;
};
}
#endif // DATA_ACCESS_OBJECT_H
