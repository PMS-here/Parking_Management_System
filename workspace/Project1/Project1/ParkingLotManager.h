#ifndef PARKINGLOTMANAGER_H
#define PARKINGLOTMANAGER_H
#include "ParkingLotManager.h"
#include "ParkingLot.h"
#include "ParkingLotService.h"
#include <string>

using namespace std;

class ParkingLotManager {
private:
    ParkingLot parkingLot;
    ParkingLotService parkingLotService;
    string filePath;
    string userId;

    void loadData();
    void saveData();

public:
    ParkingLotManager(const string& filePath, const string& userId);
    void setParkingLotSize();
    void setParkingLotTarget();
    void setParkingFee();
    void showMenu();
};

#endif // PARKINGLOTMANAGER_H
