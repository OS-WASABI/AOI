// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <string>
#include <vector>
#include "data_access_object.hpp"

namespace aoi_rest {
DataAccessObject& DataAccessObject::Instance() {
    static DataAccessObject instance;
    return instance;
}
std::vector<User> DataAccessObject::GetUsers() {
    return users__;
}
bool DataAccessObject::RemoveUser(User user) {
    for(auto itr = users__.begin(); itr != users__.end(); itr++) {
        if(user == *itr) {
            users__.erase(itr);
            return true;
        }
    }
    return false;
}
void DataAccessObject::AddUser(User user) {
    users__.push_back(user);
}
}
