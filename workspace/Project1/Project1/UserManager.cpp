#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

UserManager::UserManager(vector<User>& users) : users(users) {}

// 사용자 관리자 메뉴 함수
void UserManager::userManagerMenu()
{
    int choice;
    string id, newEmail;

    while (true)
    {
        cout << "+------------------------------------------+\n";
        cout << "|            User Manager Menu             |\n";
        cout << "+------------------------------------------+\n";

        cout << "1. Delete User\n";
        cout << "2. Change User Email\n";
        cout << "3. User Information Query\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter the ID of the user to delete: ";
            cin >> id;
            deleteUser(id);
        }
        else if (choice == 2)
        {
            cout << "Enter the ID of the user to change email: ";
            cin >> id;
            cout << "Enter the new email: ";
            cin >> newEmail;
            changeEmail(id, newEmail);
        }
        else if (choice == 3)
        {
            showUsers();
        }
        else if (choice == 4) {
            break;
        }
        else
        {
            cout << "Invalid option. Please choose again.\n";
        }
    }
}

// 계정 삭제 함수
void UserManager::deleteUser(const string& id)
{
    bool found = false;
    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if (it->getId() == id)
        {
            users.erase(it);
            found = true;
            cout << "User with ID: " << id << " has been deleted.\n";
            break;
        }
    }

    if (!found) {
        cout << "User with ID: " << id << " not found.\n";
        return;
    }

    // CSV 파일 업데이트
    ofstream file("users.csv");
    if (!file.is_open()) {
        cout << "Failed to open users.csv file for writing." << endl;
        return;
    }

    for (const auto& user : users) {
        file << user.getId() << "," << user.getEmail() << "," << user.getPassword() << endl;
    }

    file.close();
}

// 이메일 변경 함수
void UserManager::changeEmail(const string& id, const string& newEmail)
{
    bool found = false;
    for (auto& user : users)
    {
        if (user.getId() == id)
        {
            user.setEmail(newEmail);
            found = true;
            cout << "Email for user with ID: " << id << " has been changed to " << newEmail << ".\n";
            break;
        }
    }

    if (!found) {
        cout << "User with ID: " << id << " not found.\n";
        return;
    }

    // CSV 파일 업데이트
    ofstream file("users.csv");
    if (!file.is_open()) {
        cout << "Failed to open users.csv file for writing." << endl;
        return;
    }

    for (const auto& user : users) {
        file << user.getId() << "," << user.getEmail() << "," << user.getPassword() << endl;
    }

    file.close();
}

void UserManager::showUsers()
{
    ifstream file("users.csv"); // CSV 파일을 열기
    if (!file.is_open()) {
        cout << "Failed to open users.csv file." << endl;
        return;
    }

    string line;
    cout << "+------------------------------------------+\n";
    cout << "|              User Information            |\n";
    cout << "+------------------------------------------+\n";
    cout << "ID\t\tEmail\t\tPassword" << endl;
    cout << "--------------------------------------------" << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, email, password;

        // CSV 파일의 각 필드를 콤마로 구분하여 읽음
        getline(ss, id, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        // 사용자 정보를 출력
        cout << id << "\t\t" << email << "\t\t" << password << endl;
    }

    file.close(); // 파일 닫기
}