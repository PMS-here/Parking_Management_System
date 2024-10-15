#include "ParkingLotManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

ParkingLotManager::ParkingLotManager(ParkingLot& parkingLot, const string& userId)
    : parkingLot(parkingLot), userId(userId) {
    loadSettings();  // Load settings for this user from CSV
}

void ParkingLotManager::loadSettings() {
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cout << "Failed to open " << fileName << "\n";
        return;
    }

    bool userFound = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string csvUserId, sizex, sizey, targetx, targety, fee;

        getline(ss, csvUserId, ',');
        if (csvUserId == userId) {
            userFound = true;
            getline(ss, sizex, ',');
            getline(ss, sizey, ',');
            getline(ss, targetx, ',');
            getline(ss, targety, ',');
            getline(ss, fee, ',');

            parkingLot.setSizeX(stoi(sizex));
            parkingLot.setSizeY(stoi(sizey));
            parkingLot.setTargetX(stoi(targetx));
            parkingLot.setTargetY(stoi(targety));
            parkingLot.setFee(stod(fee));

            cout << "Settings loaded for user " << userId << "\n";
            break;
        }
    }

    if (!userFound) {
        cout << "No settings found for user " << userId << ". Creating new entry.\n";
        saveSettings();  // Save a new entry for this user
    }

    file.close();
}

void ParkingLotManager::saveSettings() {
    ifstream fileIn(fileName);
    ofstream fileOut("temp.csv");
    string line;
    bool userFound = false;

    if (!fileIn.is_open()) {
        cout << "Failed to open " << fileName << "\n";
        return;
    }

    while (getline(fileIn, line)) {
        stringstream ss(line);
        string csvUserId;
        getline(ss, csvUserId, ',');

        if (csvUserId == userId) {
            userFound = true;
            fileOut << userId << ","
                << parkingLot.getSizeX() << ","
                << parkingLot.getSizeY() << ","
                << parkingLot.getTargetX() << ","
                << parkingLot.getTargetY() << ","
                << parkingLot.getFee() << "\n";
        }
        else {
            fileOut << line << "\n";
        }
    }

    if (!userFound) {
        fileOut << userId << ","
            << parkingLot.getSizeX() << ","
            << parkingLot.getSizeY() << ","
            << parkingLot.getTargetX() << ","
            << parkingLot.getTargetY() << ","
            << parkingLot.getFee() << "\n";
    }

    fileIn.close();
    fileOut.close();

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());
}

void ParkingLotManager::parkingLotManagerMenu()
{
    int choice;

    while (true)
    {
        cout << "+------------------------------------------+\n";
        cout << "|          Parking Lot Manager Menu        |\n";
        cout << "+------------------------------------------+\n";
        cout << "1. Start Parking Lot Service\n";
        cout << "2. Set Parking Lot Size\n";
        cout << "3. Set Parking Lot Target\n";
        cout << "4. Set Parking Fee\n";
        cout << "5. Calculate Fee\n";
        cout << "6. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            //파킹랏 서비스
        }
        else if (choice == 2)
        {
            setParkingLotSize();
        }
        else if (choice == 3)
        {
            setParkingLotTarget();
        }
        else if (choice == 4)
        {
            setParkingFee();
        }
        else if (choice == 5)
        {
            //정산확인
        }
        else if (choice == 6)
        {
            cout << "Logging out...\n";
            saveSettings();  // Save settings on logout
            break;
        }
        else
        {
            cout << "Invalid option. Please choose again.\n";
        }
    }
}

void ParkingLotManager::setParkingLotSize()
{
    int sizex, sizey;
    cout << "Enter the new size X of the parking lot: ";
    cin >> sizex;
    parkingLot.setSizeX(sizex);
    cout << "Enter the new size Y of the parking lot: ";
    cin >> sizey;
    parkingLot.setSizeY(sizey);
    cout << "Parking lot size set to " << sizex << "x" << sizey << " spots.\n";
}

void ParkingLotManager::setParkingLotTarget()
{
    int targetx, targety;
    cout << "Enter the new target X of the parking lot: ";
    cin >> targetx;
    parkingLot.setTargetX(targetx);
    cout << "Enter the new target Y of the parking lot: ";
    cin >> targety;
    parkingLot.setTargetY(targety);
    cout << "Parking lot target set to " << targetx << "x" << targety << " spots.\n";
}

void ParkingLotManager::setParkingFee()
{
    double fee;
    cout << "Enter the new parking fee per hour: ";
    cin >> fee;
    parkingLot.setFee(fee);
    cout << "Parking fee set to $" << fee << " per hour.\n";
}
