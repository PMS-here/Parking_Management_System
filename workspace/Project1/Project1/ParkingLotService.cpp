#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <conio.h>   // _getch
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include "ParkingLotService.h"
#include "Vehicle.h"

using namespace std;

ParkingLotService::ParkingLotService()
    : userId(""), rows(10), cols(10), targetX(0), targetY(0), fee(50.0), vehicleFilePath("") {
    // map의 동적 메모리 할당 (10x10)
    map = new Vehicle * [rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new Vehicle[cols];
    }
}

ParkingLotService::ParkingLotService(int rows, int cols)
    : rows(rows), cols(cols), userId(""), targetX(0), targetY(0), fee(0.0), vehicleFilePath("")
{   
    map = new Vehicle * [rows];
    if (map == nullptr) {
        throw bad_alloc(); // 메모리 할당 실패 시 예외 발생
    }
    for (int i = 0; i < rows; ++i) {
        map[i] = new Vehicle[cols];
        throw bad_alloc(); // 메모리 할당 실패 시 예외 발생
    }
}

ParkingLotService::ParkingLotService(const string& filePath, const string& userId)
    : userId(userId) {
    loadDataFromFile(filePath);
    vehicleFilePath = userId + "_vehicles.csv";
    //initializeParkingLot();
}


void ParkingLotService::initializeParkingLot(int aa, int bb) {
    setRows(aa);
    setCols(bb);
    rows = aa;
    cols = bb;
    for (int i = 0; i < rows; ++i) {//rows
        for (int j = 0; j < cols; ++j) { //cols
            map[i][j] = Vehicle();
        }
    }
    // 번호판 모델 타임 
    map[0][0] = Vehicle("12A1234", "GASOLINE", 0.6);
    map[0][1] = Vehicle("22B7755", "ELECTRIC", 3.2);
    map[1][0] = Vehicle("31E1452", "ELECTRIC", 5.4);
    map[2][0] = Vehicle("65T7842", "ELECTRIC", 0.9);
    map[3][1] = Vehicle("39J1547", "GASOLINE", 1.6);

}
void ParkingLotService::userinitializeParkingLot(int aa, int bb)
{
    setRows(aa);
    setCols(bb);
    rows = aa;
    cols = bb;
    if (map == nullptr) {
        throw std::runtime_error("ERROR : Parking Lot is not initialized."); // map이 nullptr일 경우 예외 발생
    }

    int** path = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        path[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) { // rows
        for (int j = 0; j < cols; ++j) { // cols
            // map[i][j]가 비어 있는지 확인
            if (!map[i][j].isEmpty()) {
                cout << "It's already parked!" << endl;
            }
            else{ 
                string licensePlate, model;
                double parkingTime;

                cout << "(" << i << "," << j << ") INPUT vehicle information." << endl;

                cout << "Vehicle license plate (input if none): ";
                cin.ignore();
                getline(cin, licensePlate);
                /*
                while (true) {
                    cout << "Vehicle license plate (input if none): ";
                    cin.ignore();
                    getline(cin, licensePlate);
                    cout << licensePlate <<'\n';
                    if (isValidLicensePlate(licensePlate)) {
                        cout << "Valid license plate entered: " << licensePlate << endl;
                        break; // 유효한 번호판이면 루프 종료
                    }
                    else {
                        cout << "Invalid license plate format. Please enter in the format '00[A-Z]0000'." << endl;
                    }
                }
                */

                if (licensePlate.empty()) licensePlate = "";
                cout << "Vehicle model (input if none): ";
                //cin.ignore();
                getline(cin, model);
                if (model.empty()) model = "";

                cout << "Parked time (set to 0.0 if none): ";
                string parkingTimeInput;
                //cin.ignore();
                getline(cin, parkingTimeInput);
                if (parkingTimeInput.empty()) parkingTime = 0.0;
                else {
                    stringstream ss(parkingTimeInput);
                    ss >> parkingTime;
                }

                // Vehicle 객체를 생성하여 map에 저장
                map[i][j] = Vehicle(licensePlate, model, parkingTime);
            }

            // path 배열을 map[i][j]의 상태에 따라 초기화
            if (map[i][j].isEmpty()) {
                path[i][j] = 0; // 비어 있으면 0으로 설정
            }
            else {
                path[i][j] = 1; // 차량이 있으면 1로 설정
            }
        }
    }

    // path 배열은 이후에 필요한 로직에서 사용됩니다.
    // 작업이 끝난 후 path 배열의 메모리 해제
    for (int i = 0; i < rows; ++i) {
        delete[] path[i];
    }
    delete[] path;
}
Vehicle ParkingLotService::getVehicle(int i, int j){
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw out_of_range("ERROR : Index is out of range.");
    }
    return map[i][j];
}

void ParkingLotService::setVehicle(int i, int j, const Vehicle& vehicle) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw out_of_range("ERROR : Index is out of range.");
    }
    map[i][j] = vehicle;
}

void ParkingLotService::enterVehicle(const Vehicle& vehicle)
{
}



void ParkingLotService::loadDataFromFile(const string& filePath) {
    ifstream file(filePath);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id == userId) {
            ss >> rows;
            ss.ignore();
            ss >> cols;
            ss.ignore();
            ss >> targetX;
            ss.ignore();
            ss >> targetY;
            ss.ignore();
            ss >> fee;
            break;
        }
    }
    file.close();
}

/*
void ParkingLotService::enterVehicle(const Vehicle& vehicle) {
    ofstream file(vehicleFilePath, ios::app); // append mode
    if (file.is_open()) {
        file << vehicle.getLicensePlate() << ","
            << vehicle.getModel() << ","
            << time(nullptr) << endl; // 현재 시각 저장
        file.close();
    }
    else {
        cerr << "Unable to open file for writing." << endl;
    }
}
*/

void ParkingLotService::exitVehicle(const string& licensePlate) {
    ifstream file(vehicleFilePath);
    ofstream tempFile("temp.csv");
    string line;

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string plate;
            getline(ss, plate, ',');

            if (plate != licensePlate) {
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();

        remove(vehicleFilePath.c_str());
        rename("temp.csv", vehicleFilePath.c_str());
    }
    else {
        cerr << "Unable to open file for reading/writing." << endl;
    }
}

vector<Vehicle> ParkingLotService::readVehicle() const {
    ifstream file(vehicleFilePath);
    vector<Vehicle> vehicles;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string licensePlate, model;
            double parkingTime;

            getline(ss, licensePlate, ',');
            getline(ss, model, ',');
            ss >> parkingTime;

            Vehicle vehicle(licensePlate, model, parkingTime);
            vehicle.setParkingTime(parkingTime);
            vehicles.push_back(vehicle);
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for reading." << endl;
    }
    return vehicles;
}



ParkingLotService::~ParkingLotService() {
    for (int i = 0; i < rows; ++i) {
        delete[] map[i];
    }
    delete[] map;
}



/*
void ParkingLotService::initializeParkingLot() {
    parkingLotManager.loadSettings();
}
*/
void ParkingLotService::printVehicleInfo(int currentRow, int currentCol) {
    Vehicle currentInfo = map[currentRow][currentCol];
    if (!currentInfo.isEmpty()) {
        cout << "Vehicle number: " << currentInfo.getLicensePlate() << endl;
        cout << "Vehicle type: " << currentInfo.getModel() << endl;
        cout << "Parked Time: " << currentInfo.getParkedTime() << endl;
    }
    else {
        cout << "This position is empty." << endl;
    }
}

void ParkingLotService::printArray(int currentRow, int currentCol) {
    system("cls");

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == currentRow && j == currentCol) {
                cout << "[ X ] ";
            }
            else {
                if (map[i][j].isEmpty()) {
                    cout << "[ 0 ] "; // 빈 공간
                }
                else {
                    cout << "[ 1 ] "; // 차가 있는 공간
                }
            }
        }
        cout << endl;
    }

    gotoxy(0, rows + 2);
    printVehicleInfo(currentRow, currentCol);
}

void ParkingLotService::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ParkingLotService::showParkingLotService() {
    int currentRow = 0, currentCol = 0;

    while (true) {
        printArray(currentRow, currentCol);

        int key = _getch();

        if (key == 224) {
            key = _getch();

            if (key == 72 && currentRow > 0) {
                currentRow--;
            }
            else if (key == 80 && currentRow < rows - 1) {
                currentRow++;
            }
            else if (key == 75 && currentCol > 0) {
                currentCol--;
            }
            else if (key == 77 && currentCol < cols - 1) {
                currentCol++;
            }
        }
        else if (key == 27) {
            break;
        }
    }
}

void ParkingLotService::initializeAtPosition(int tx, int ty, int aa, int bb)
{
    setRows(aa);
    setCols(bb);
    rows = aa;
    cols = bb;
    setTargetX(tx);
    setTargetY(ty);
    // 좌표가 주차장의 범위를 벗어났는지 확인
    if (tx < 0 || tx >= rows || ty < 0 || ty >= cols) {
        cout << "Invalid. Please enter the correct coordinates." << endl;
        return;
    }

    // 해당 좌표가 비어 있는지 확인
    if (map[tx][ty].isEmpty()) {
        string licensePlate, model;
        double parkingTime;

        cout << "(" << tx << ", " << ty << ") The vehicle is coming in!" << endl;

        cout << "Vehicle License Plate: ";
        cin.ignore();
        getline(cin, licensePlate);

        /*//정규표현식 오류
        while (true) {
            cout << "Vehicle License Plate: ";
            cin.ignore();
            getline(cin, licensePlate);

            if (isValidLicensePlate(licensePlate)) {
                cout << "Valid license plate entered: " << licensePlate << endl;
                break; // 유효한 번호판이면 루프 종료
            }
            else {
                cout << "Invalid license plate format. Please enter in the format '00[A-Z]0000'." << endl;
            }
        }
        */

        if (licensePlate.empty()) licensePlate = "";
        cout << "Vehicle Model: ";
        getline(cin, model);
        if (model.empty()) model = "";
        cout << "Parked time: ";
        string parkingTimeInput;
        getline(cin, parkingTimeInput);
        if (parkingTimeInput.empty()) parkingTime = 0.0;
        else {
            stringstream ss(parkingTimeInput);
            ss >> parkingTime;
        }

        // 입력된 정보를 바탕으로 Vehicle 객체를 생성하고 map[tx][ty]에 저장
        map[tx][ty] = Vehicle(licensePlate, model, parkingTime);
        cout << "(" << tx << ", " << ty << ") Parking done" << endl;
    }
    else {
        cout << "There is already a car parked at those coordinates." << endl;
    }
}

// Getter and Setter for userId
string ParkingLotService::getUserId() {
    return userId;
}

void ParkingLotService::setUserId( string& userId) {
    this->userId = userId;
}

void ParkingLotService::removeVehicleAtPosition(int tx, int ty,int rate=5000)
{
    setTargetX(tx);
    setTargetY(ty);

    // 좌표가 주차장의 범위를 벗어났는지 확인
    if (tx < 0 || tx >= rows || ty < 0 || ty >= cols) {
        cout << "Invalid! Please enter the correct coordinates." << endl;
        return;
    }

    // 해당 좌표가 비어 있는지 확인
    if (map[tx][ty].isEmpty()) {
        cout << "Empty! It cannot be deleted!" << endl;
        return;
    }

    // 차량 정보 가져오기
    Vehicle vehicle = map[tx][ty];

    // 주차 요금 계산
    double parkingFee = vehicle.getParkedTime() * rate;

    // 차량 삭제
    map[tx][ty] = Vehicle(); // 또는 map[tx][ty] = ""; // 비어 있는 상태로 초기화

    // 요금 및 삭제 메시지 출력
    cout << "Vehicle License Plate: " << vehicle.getLicensePlate() << " EXIT" << endl;
    cout << "Parking fee : $" << parkingFee  << endl;
    cout << "Goodbye!" << endl;
}

// Getter and Setter for rows
int ParkingLotService::getRows()  {
    return rows;
}

void ParkingLotService::setRows(int rows) {
    this->rows = rows;
}

// BFS 하는 함수
int ParkingLotService::BFS(int** a, int x, int y, int tx, int ty)
{
    const int INF = 987987987;
    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };
    vector<vector<int>> dist(x, vector<int>(y, INF));
    vector<pair<int, int>>board;
    queue<pair<int, int>> q;
    q.push({ 0, 0 });
    dist[0][0] = 0;

    while (!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        if (curX == tx && curY == ty) {
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    if (dist[i][j] == dist[curX][curY] && a[i][j] == 0 ){
                        board.push_back({ i,j });
                    }
                    if (i == tx && j == ty) cout << "T ";
                    else if (dist[i][j] == INF) cout << "N ";
                    else if (a[i][j] == 0) {
                        cout << dist[i][j] << " ";
                    }
                    else cout << "X ";
                }
                cout << '\n';
            }
            if (a[tx][ty] == 1) {
                cout << "Already occupied!\n";
                cout << "Recommend different coordinates of the same distance\n";
                for (int i = 0; i < board.size(); i++) {
                    cout << i+1 << " : (" << board[i].first << "," << board[i].second <<  ")\n";
                }
                cout << '\n';
            }
            else {
                cout << "\nPARKING AVAILABLE\n";
            }
            cout << "TARGET DIST: ";
            return dist[curX][curY];
        }

        for (int i = 0; i < 4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            if (nx < 0 || nx >= x || ny < 0 || ny >= y) continue;
            if (dist[nx][ny] <= dist[curX][curY] + 1) continue;

            dist[nx][ny] = dist[curX][curY] + 1;
            q.push({ nx, ny });
        }
    }
    return -1;
}

// 정규 표현식 체크 하는 함수 
bool ParkingLotService::isValidLicensePlate(const string& plate)
{
    regex pattern(R"(^[0-9]{2}[A-Z][0-9]{4}$)");
    return regex_match(plate, pattern);
}

// Getter and Setter for cols
int ParkingLotService::getCols()  {
    return cols;
}

void ParkingLotService::setCols(int cols) {
    this->cols = cols;
}



// Getter and Setter for targetX
int ParkingLotService::getTargetX(){
    return targetX;
}

void ParkingLotService::setTargetX(int targetX) {
    this->targetX = targetX;
}

// Getter and Setter for targetY
int ParkingLotService::getTargetY() {
    return targetY;
}

void ParkingLotService::setTargetY(int targetY) {
    this->targetY = targetY;
}

// Getter and Setter for fee
double ParkingLotService::getFee() {
    return fee;
}

void ParkingLotService::setFee(double fee) {
    this->fee = fee;
}

// Getter and Setter for vehicleFilePath
string ParkingLotService::getVehicleFilePath()  {
    return vehicleFilePath;
}

void ParkingLotService::setVehicleFilePath(const string& vehicleFilePath) {
    this->vehicleFilePath = vehicleFilePath;
}