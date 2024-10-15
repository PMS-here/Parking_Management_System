#include "LoginService.h"

#ifdef _WIN32
#include <windows.h>
#endif

LoginService::LoginService(const string& filename) : filename(filename) {
    loadFromCSV();
}

// 텍스트 색상을 설정하는 함수 (Windows에서만 동작)
void LoginService::setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#endif
}

// 테두리 출력 함수
void LoginService::printBorder() {
    cout << "+------------------------------------------+\n";
}

// 사용자 정보를 CSV 파일에 저장하는 함수
void LoginService::saveToCSV() {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.getId() << "," << user.getEmail() << "," << user.getPassword() << "," << user.getX() << "," << user.getY() << user.getTx() << "," << user.getTy() << "\n";
        }
        file.close();
    }
    else {
        setColor(12); // Red
        cout << "Unable to open file for writing.\n";
        setColor(7);  // Reset to default
    }
}

// CSV 파일에서 사용자 정보를 불러오는 함수
void LoginService::loadFromCSV() {
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, email, password;
            int x, y, tx, ty;

            if (getline(ss, id, ',') && getline(ss, email, ',') && getline(ss, password, ',') && ss >> x && ss.ignore() && ss >> y && ss >> tx && ss >> ty) {
                User user;
                user.setId(id);
                user.setEmail(email);
                user.setPassword(password);
                user.setX(x);
                user.setY(y);
                user.setTx(x);
                user.setTy(y);

                users.push_back(user);
            }
        }
        file.close();
    }
    else {
        setColor(12); // Red
        cout << "Unable to open file for reading.\n";
        setColor(7);  // Reset to default
    }
}

// 사용자 등록 함수
void LoginService::registerUser() {
    User newUser;

    printBorder();
    setColor(11); // Cyan
    cout << "|             User Registration            |\n";
    printBorder();

    setColor(7); // Reset to default
    string id, email, password;
    int x, y, tx, ty;

    cout << "Enter id: ";
    cin >> id;
    newUser.setId(id);

    cout << "Enter email: ";
    cin >> email;
    newUser.setEmail(email);

    cout << "Enter password: ";
    cin >> password;
    newUser.setPassword(password);

    cout << "Enter x value: ";
    cin >> x;
    newUser.setX(x);

    cout << "Enter y value: ";
    cin >> y;
    newUser.setY(y);

    cout << "Enter tx value: ";
    cin >> tx;
    newUser.setTx(tx);

    cout << "Enter ty value: ";
    cin >> ty;
    newUser.setTy(ty);

    users.push_back(newUser);
    saveToCSV();

    setColor(10); // Green
    cout << "User registered successfully!\n";
    setColor(7);  // Reset to default
}

// 사용자 로그인 함수
bool LoginService::loginUser() {
    string id, password;

    printBorder();
    setColor(11); // Cyan
    cout << "|                 User Login               |\n";
    printBorder();

    setColor(7); // Reset to default
    cout << "Enter id: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    for (const auto& user : users)
    {
        if ((id == "root") && (password == "0000"))
        {
            setColor(10); // Green
            cout << "Root Login successful! Welcome, " << ".\n";
            setColor(7);  // Reset to default
            return true;
        }


        else if (user.getId() == id && user.getPassword() == password)
        {
            setColor(10); // Green
            cout << "Login successful! Welcome, " << user.getId() << ".\n";
            setColor(7);  // Reset to default

            UserService userService(user);
            userService.showMenu();


            return true;
        }
    }

    setColor(12); // Red
    cout << "Login failed. Please check your id and password.\n";
    setColor(7);  // Reset to default
    return false;
}

// 비밀번호 찾기 함수
void LoginService::findPassword() {
    string id, email;

    printBorder();
    setColor(11); // Cyan
    cout << "|              Find Password               |\n";
    printBorder();

    setColor(7); // Reset to default
    cout << "Enter id: ";
    cin >> id;
    cout << "Enter email: ";
    cin >> email;

    for (const auto& user : users) {
        if (user.getId() == id && user.getEmail() == email) {
            setColor(10); // Green
            cout << "Your password is: " << user.getPassword() << "\n";
            setColor(7);  // Reset to default
            return;
        }
    }

    setColor(12); // Red
    cout << "No matching user found. Please check your id and email.\n";
    setColor(7);  // Reset to default
}

// 메인 메뉴 실행 함수
void LoginService::run() {
    int choice;
    while (true) {
        printBorder();
        setColor(11); // Cyan
        cout << "|                Main Menu                 |\n";
        printBorder();

        setColor(7); // Reset to default
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Find Password\n";  // 비밀번호 찾기 옵션 추가
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            loginUser();
        }
        else if (choice == 2)
        {

            registerUser();
        }
        else if (choice == 3)
        {
            findPassword();  // 비밀번호 찾기 실행
        }
        else if (choice == 4)
        {
            setColor(10); // Green
            cout << "Exiting the program.\n";
            setColor(7);  // Reset to default
            break;
        }
        else
        {
            setColor(12); // Red
            cout << "Invalid option. Please choose again.\n";
            setColor(7);  // Reset to default
        }
    }
}



