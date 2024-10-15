#ifndef PARKINGLOT_H
#define PARKINGLOT_H

class ParkingLot {
public:
    ParkingLot();

    int getSizeX();
    void setSizeX(int sizex);
    int getSizeY();
    void setSizeY(int sizey);

    int getTargetX();
    void setTargetX(int targetx);
    int getTargetY();
    void setTargetY(int targety);

    double getFee();
    void setFee(double fee);

private:
    int sizex, sizey;       // 주차장 사이즈
    int targetx, targety;   // 주차장 타겟
    double fee;             // 요금
};

#endif
