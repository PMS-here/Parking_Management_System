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

int User::getX() const {
    return x;
}

void User::setX(int x) {
    this->x = x;
}

int User::getY() const {
    return y;
}

void User::setY(int y) {
    this->y = y;
}

int User::getTx() const {
    return tx;
}

void User::setTx(int tx) {
    this->tx = tx;
}

int User::getTy() const {
    return ty;
}

void User::setTy(int ty) {
    this->ty = ty;
}

