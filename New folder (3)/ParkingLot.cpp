#include "ParkingLot.h"

ParkingLot::ParkingLot() : sizex(0),sizey(0),targetx(0),targety(0), fee(0.0) {}

int ParkingLot::getSizeX()  
{
    return sizex;
}

void ParkingLot::setSizeX(int sizex) 
{
    this->sizex = sizex;
}

int ParkingLot::getSizeY() 
{
    return sizey;
}

void ParkingLot::setSizeY(int sizey)
{
    this->sizey = sizey;
}

int ParkingLot::getTargetX()
{
    return targetx;
}

void ParkingLot::setTargetX(int targetx)
{
    this->targetx = targetx;
}

int ParkingLot::getTargetY()
{
    return targetx;
}

void ParkingLot::setTargetY(int targetx)
{
    this->targetx = targetx;
}

double ParkingLot::getFee()  
{
    return fee;
}

void ParkingLot::setFee(double fee) 
{
    this->fee = fee;
}
