#include "UserService.h"

// Constructor that stores a reference to the logged-in user
UserService::UserService(User& user) : loggedInUser(user) {}

// Displays the menu and executes the selected function
void UserService::showMenu() {
    int choice;
    while (true) {
        cout << "+------------------------------------------+\n";
        cout << "|                User Menu                 |\n";
        cout << "+------------------------------------------+\n";

        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Change Password\n";
        cout << "4. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            parkVehicle();
        }
        else if (choice == 2) {
            removeVehicle();
        }
        else if (choice == 3) {
            changePassword();
        }
        else if (choice == 4) {
            cout << "Logging out...\n";
            break;
        }
        else {
            cout << "Invalid option. Please choose again.\n";
        }
    }
}

// Function to park a vehicle (enter the vehicle number)
void UserService::parkVehicle() {
    string vehicleNumber;
    cout << "Enter vehicle number to park: ";
    cin >> vehicleNumber;

    // Here, you can implement the logic to associate this vehicle number with the user
    cout << "Vehicle " << vehicleNumber << " parked successfully.\n";
}

// Function to remove a vehicle (enter the vehicle number)
void UserService::removeVehicle() {
    string vehicleNumber;
    cout << "Enter vehicle number to remove: ";
    cin >> vehicleNumber;

    // Here, you can implement the logic to disassociate this vehicle number from the user
    cout << "Vehicle " << vehicleNumber << " removed successfully.\n";
}

// Function to change the user's password
void UserService::changePassword() {
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;

    loggedInUser.setPassword(newPassword);

    cout << "Password changed successfully.\n";
}
