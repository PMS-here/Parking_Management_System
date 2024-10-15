#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
private:
    string id;              //ID
    string email;           //e-mail
    string password;        //PW
    int x;                  //주차장 x
    int y;                  //주차장 y
    int tx;                 //주차장 타겟 x
    int ty;                 //주차장 타겟 y

public:
    User() : x(0), y(0), tx(0), ty(0) {}

    User(const string& id, const string& email, const string& password, int x, int y, int tx, int ty)
        : id(id), email(email), password(password), x(x), y(y), tx(tx), ty(ty) {}


    string getId() const;
    void setId(const string& id);

    string getEmail() const;
    void setEmail(const string& email);

    string getPassword() const;
    void setPassword(const string& password);

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    int getTx() const;
    void setTx(int tx);

    int getTy() const;
    void setTy(int ty);

};

#endif 
