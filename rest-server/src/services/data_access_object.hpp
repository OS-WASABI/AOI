// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef DATA_ACCESS_OBJECT_H
#define DATA_ACCESS_OBJECT_H
#include <string>
#include <vector>
#include "user.hpp"
#include "data_access_interface.hpp"

namespace aoi_rest {
class DataAccessObject : public DataAccessInterface {
  public:
    // The implementation of the data access object is a singleton.
    // Therefore you get an instance of the DAO, but you cannot construct a new one.
    static DataAccessObject& Instance();
    // Deleting the below methods enforces singleton behavior.
    // If you don't delete the copy and compare methods, the compiler auto-generates them.
    DataAccessObject(DataAccessObject const&) = delete;
    void operator=(DataAccessObject const&) = delete;

    std::vector<User> GetUsers() override;
    std::vector<User> GetUsersByName(const std::string& name) override;
    std::vector<User> GetUserByID(int id) override;
    bool RemoveUser(User user) override;
    void AddUser(User user) override;
  private:
    DataAccessObject() { }
    std::vector<User> users__;
};
}
#endif // DATA_ACCESS_OBJECT_H
