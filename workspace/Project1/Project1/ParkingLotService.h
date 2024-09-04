// parkinglotService.h
#ifndef PARKINGLOTSERVICE_H
#define PARKINGLOTSERVICE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <regex>
#include "Vehicle.h"

using namespace std;

class ParkingLotService {

public:
    string userId;
    Vehicle** map;
    int rows, cols;
    int targetX, targetY;
    double fee;
    string vehicleFilePath;

    ParkingLotService();
    ParkingLotService(int rows, int cols);
    ParkingLotService(const string& filePath, const string& userId);
    ~ParkingLotService();
    
    // 최초 주차장 초기화 함수
    void initializeParkingLot(int aa, int bb);
    
    // 배열 단위로 주차장 초기화 함수
    void userinitializeParkingLot(int aa, int bb);

    // 특정 좌표 주차
    void initializeAtPosition(int tx, int ty, int aa, int bb);

    // 특정 좌표 출차
    void removeVehicleAtPosition(int tx, int ty,int rate);

    // BFS
    int BFS(int** a, int x, int y, int tx, int ty);

    // 정규 표현식
    bool isValidLicensePlate(const string& plate);

    Vehicle getVehicle(int i, int j);
    void setVehicle(int i, int j, const Vehicle& vehicle);

    void enterVehicle(const Vehicle& vehicle);
    void exitVehicle(const string& licensePlate);
    vector<Vehicle> readVehicle() const;

    void printVehicleInfo(int currentRow, int currentCol);
    void printArray(int currentRow, int currentCol);
    void gotoxy(int x, int y);
    void showParkingLotService();

    void loadDataFromFile(const string & filePath);


    string getUserId();
    void setUserId(string & userId);

    // Getter and Setter for rows
    int getRows();
    void setRows(int rows);

    // Getter and Setter for cols
    int getCols();
    void setCols(int cols);

    // Getter and Setter for targetX
    int getTargetX();
    void setTargetX(int targetX);

    // Getter and Setter for targetY
    int getTargetY();
    void setTargetY(int targetY);

    // Getter and Setter for fee
    double getFee();
    void setFee(double fee);

    // Getter and Setter for vehicleFilePath
    string getVehicleFilePath();
    void setVehicleFilePath(const string & vehicleFilePath);
    
};
#endif // PARKINGLOTSERVICE_H