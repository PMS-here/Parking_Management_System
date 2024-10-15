#include "UserManager.h"
#include <iostream>

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
        cout << "3. Back to Main Menu\n";
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
    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if (it->getId() == id)
        {
            users.erase(it);
            cout << "User with ID: " << id << " has been deleted.\n";
            return;
        }
    }
    cout << "User with ID: " << id << " not found.\n";
}

// 이메일 변경 함수
void UserManager::changeEmail(const string& id, const string& newEmail)
{
    for (auto& user : users)
    {
        if (user.getId() == id)
        {
            user.setEmail(newEmail);
            cout << "Email for user with ID: " << id << " has been changed to " << newEmail << ".\n";
            return;
        }
    }
    cout << "User with ID: " << id << " not found.\n";
}
