#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <iostream>
#include <string>
#include "User.h"

using namespace std;

class UserService {
public:
    UserService(User& user);
    void showMenu();

private:
    User& loggedInUser;

    void parkVehicle();
    void removeVehicle();
    void changePassword();
};

#endif
