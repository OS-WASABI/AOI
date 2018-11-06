// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef USER_H
#define USER_H
#include <string>

namespace aoi_rest {
struct User {
    std::string name;
    int id;
    std::string password;
};
inline bool operator==(const User &a, const User &b) {
    return a.name == b.name &&
           a.id == b.id &&
           a.password == b.password;
}
}
#endif // USER_H
