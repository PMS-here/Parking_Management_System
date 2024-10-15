#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "User.h"
#include "UserManager.h"
#include "ParkingLot.h"
#include "ParkingLotManager.h"

using namespace std;

class LoginService {
public:
    LoginService(const string& filename);
    void run();

private:
    vector<User> users;
    ParkingLot parkingLot;
    string filename;

    void setColor(int color); // 색 
    void printBorder();   // 라인
    void saveToCSV();     // csv 저장 함수
    void loadFromCSV();   // csv 로드 함수

    void registerUser();  // 계정 등록 함수
    bool loginUser();     // 로그인 판별 함수
    void findPassword();  // 비밀번호 찾기 함수 선언
    
};

#endif

