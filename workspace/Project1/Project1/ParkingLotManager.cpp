#include "ParkingLotManager.h"
#include "ParkingLotService.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
int NN, MM, TX, TY;
double FF;
ParkingLotManager::ParkingLotManager(const string& filePath, const string& userId)
    : filePath(filePath), userId(userId) {
    loadData();  // 사용자 데이터를 로드하거나 초기화
}

void ParkingLotManager::loadData() {
    ifstream file(filePath);
    string line, token;
    bool userExists = false;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 6 && tokens[0] == userId) {
            parkingLot.setSizeX(stoi(tokens[1]));
            parkingLot.setSizeY(stoi(tokens[2]));
            parkingLot.setTargetX(stoi(tokens[3]));
            parkingLot.setTargetY(stoi(tokens[4]));
            parkingLot.setFee(stod(tokens[5]));
            userExists = true;
            break;
        }
    }

    if (!userExists) {
        parkingLot.setSizeX(0);
        parkingLot.setSizeY(0);
        parkingLot.setTargetX(0);
        parkingLot.setTargetY(0);
        parkingLot.setFee(0.0);
        saveData();  // 초기화된 데이터를 저장
    }

    file.close();
}

void ParkingLotManager::saveData() {
    ifstream file(filePath);
    vector<string> lines;
    string line;
    bool userExists = false;

    while (getline(file, line)) {
        if (line.find(userId) == 0) {
            stringstream ss;
            ss << userId << ","
                << parkingLot.getSizeX() << ","
                << parkingLot.getSizeY() << ","
                << parkingLot.getTargetX() << ","
                << parkingLot.getTargetY() << ","
                << parkingLot.getFee();
            lines.push_back(ss.str());
            userExists = true;
        }
        else {
            lines.push_back(line);
        }
    }

    if (!userExists) {
        stringstream ss;
        ss << userId << ","
            << parkingLot.getSizeX() << ","
            << parkingLot.getSizeY() << ","
            << parkingLot.getTargetX() << ","
            << parkingLot.getTargetY() << ","
            << parkingLot.getFee();
        lines.push_back(ss.str());
    }

    file.close();

    ofstream outFile(filePath, ios::trunc);
    for (const string& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();
}

void ParkingLotManager::setParkingLotSize() {
    int sizex, sizey;
    cout << "Enter the new size X of the parking lot: ";
    cin >> sizex;
    NN = sizex;
    parkingLot.setSizeX(sizex);
    cout << "Enter the new size Y of the parking lot: ";
    cin >> sizey;
    MM = sizey;
    parkingLot.setSizeY(sizey);
    cout << "Parking lot size set to " << sizex << "x" << sizey << " spots.\n";
    saveData();  // 데이터 변경 시 저장
}

void ParkingLotManager::setParkingLotTarget() {
    int targetx, targety;
    cout << "Enter the new target X of the parking lot: ";
    cin >> targetx;
    TX = targetx;
    parkingLot.setTargetX(targetx);
    cout << "Enter the new target Y of the parking lot: ";
    cin >> targety;
    TY = targety;
    parkingLot.setTargetY(targety);
    cout << "Parking lot target set to " << targetx << " x " << targety << " spots.\n";
    saveData();  // 데이터 변경 시 저장
}

void ParkingLotManager::setParkingFee() {
    double fee;
    cout << "Enter the new parking fee per hour: ";
    cin >> fee;
    FF = fee;
    parkingLot.setFee(fee);
    cout << "Parking fee set to $" << fee << " per hour.\n";
    saveData();  // 데이터 변경 시 저장
}

void ParkingLotManager::showMenu() {
    int choice;

    while (true) {
        cout << "+------------------------------------------+\n";
        cout << "|          Parking Lot Manager Menu        |\n";
        cout << "+------------------------------------------+\n";
        cout << "1. Show Status\n";
        cout << "2. Set Parking Lot Size\n";
        cout << "3. Set Parking Target\n";
        cout << "4. Initialize Inputs\n";
        cout << "5. Enter at target\n";
        cout << "6. EXIT and Payment at target\n";
        cout << "7. Set Parking Fee\n";
        cout << "8. Parking Spot Recommendation (BFS)\n";
        cout << "9. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;

        // 스테이터스 확인
        if (choice == 1) {
            parkingLotService.showParkingLotService();
        }
        // 주차장 기본 초기화
        else if (choice == 2) {
            setParkingLotSize();
            parkingLotService.initializeParkingLot(NN,MM);
        }
        // 타겟 좌표 설정
        else if (choice == 3) {
            setParkingLotTarget();
        }
        // 배열로 일일히 초기화
        else if (choice == 4) {
            parkingLotService.userinitializeParkingLot(NN, MM);
        }
        // 특정 좌표 입차
        else if (choice == 5) {
            parkingLotService.initializeAtPosition(TX,TY,NN,MM);
        }
        // 특정 좌표 출차
        else if (choice == 6) {
            parkingLotService.removeVehicleAtPosition(TX, TY, FF);
        }
        // 시간당 주차 요금 설정
        else if (choice == 7) {
            setParkingFee();
        }
        // BFS
        else if (choice == 8) {
            // path 배열 동적 할당
            int** path = new int* [NN];
            for (int i = 0; i < NN; ++i) {
                path[i] = new int[MM];
            }
            for (int i = 0; i < NN; ++i) { // rows
                for (int j = 0; j < MM; ++j) { // cols
                    if (parkingLotService.map[i][j].isEmpty()) {
                        path[i][j] = 0; // 비어 있으면 0으로 설정
                    }
                    else {
                        path[i][j] = 1; // 차량이 있으면 1로 설정
                    }
                }
            }
            cout << "T : Target, X : Occupied, N : NON" << '\n';
            cout << "TARGET DIST" << '\n';
            cout << parkingLotService.BFS(path,NN,MM,TX,TY) << '\n';
        }
        else if (choice == 9) {
            cout << "Logging out...\n";
            break;
        }
        else {
            cout << "Invalid option. Please choose again.\n";
        }
    }
}
