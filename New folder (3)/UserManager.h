#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include "User.h"

class UserManager {
public:
    UserManager(vector<User>& users);

    void userManagerMenu();                                             // 유저 매니저 메뉴

private:
    vector<User>& users;

    void deleteUser(const string& id);                                  // 유저 삭제함수
    void changeEmail(const string& id, const string& newEmail);         // 이메일 변경 함수
};

#endif
