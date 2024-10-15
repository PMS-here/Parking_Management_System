#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
private:
    string id;              //ID
    string email;           //e-mail
    string password;        //PW


public:
    User() {}
    User(const string& id, const string& email, const string& password)
        : id(id), email(email), password(password) {}


    string getId() const;
    void setId(const string& id);

    string getEmail() const;
    void setEmail(const string& email);

    string getPassword() const;
    void setPassword(const string& password);


};

#endif 
