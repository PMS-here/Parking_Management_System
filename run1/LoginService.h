#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "User.h"


using namespace std;

class LoginService {
public:
    LoginService(const string& filename);
    void run();

private:
    vector<User> users;
    string filename;

    void setColor(int color);
    void printBorder();
    void saveToCSV();
    void loadFromCSV();

    void registerUser();
    bool loginUser();
    void findPassword();  // 비밀번호 찾기 함수 선언
};

#endif

