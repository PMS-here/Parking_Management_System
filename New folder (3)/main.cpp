#include "LoginService.h"

using namespace std;

int main() {
    LoginService loginService("users.csv");
    loginService.run();
    return 0;
}