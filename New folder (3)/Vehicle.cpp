#include "Vehicle.h"
#include <ctime>

Vehicle::Vehicle(std::string licensePlate, string model)
    : licensePlate(licensePlate), model(model), parkingTime(time(nullptr)) {}

std::string Vehicle::getLicensePlate() const {
    return licensePlate;
}

std::string Vehicle::getModel() const {
    return model;
}

int Vehicle::getParkedHours() const {
    time_t now = time(nullptr);
    return static_cast<int>(difftime(now, parkingTime) / 3600);
}

void Vehicle::setParkingTime(time_t parkingTime) {
    this->parkingTime = parkingTime;
}
