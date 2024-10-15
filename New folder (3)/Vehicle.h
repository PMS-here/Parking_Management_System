#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>
using namespace std;
class Vehicle {
private:
    string licensePlate;
    string model;
    time_t parkingTime;

public:
    Vehicle(string licensePlate, string model);

    string getLicensePlate() const;
    string getModel() const;
    int getParkedHours() const;
    void setParkingTime(time_t parkingTime);
};

#endif
