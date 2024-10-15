#include "User.h"

string User::getId() const {
    return id;
}

void User::setId(const string& id) {
    this->id = id;
}

string User::getEmail() const {
    return email;
}

void User::setEmail(const string& email) {
    this->email = email;
}

string User::getPassword() const {
    return password;
}

void User::setPassword(const string& password) {
    this->password = password;
}

