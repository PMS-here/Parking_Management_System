#ifndef PARKINGLOTMANAGER_H
#define PARKINGLOTMANAGER_H

#include "ParkingLot.h"
#include <string>
using namespace std;

class ParkingLotManager {
public:
    ParkingLotManager(ParkingLot& parkingLot, const string& userId);

    void parkingLotManagerMenu();  // Handles the Parking Lot Manager menu

private:
    ParkingLot& parkingLot;
    string userId;
    const string fileName = "parkinglot.csv";

    void loadSettings();                // Load settings from CSV
    void saveSettings();                // Save settings to CSV

    void setParkingLotSize();           // 주차장 크기 설정함수
    void setParkingLotTarget();         // 주차장 타겟 설정함수
    void setParkingFee();               // 주차장 요금 설정함수
};

#endif
