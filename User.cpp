#include "User.h"

using namespace std;

int User::idCounter = 1002600;

User:: User(string n, string p)
{
    username =n;
    password = p;
    id = idCounter++;
}

string User::getUserName() const
{
    return username;
}
string User::getPassword() const {
    return password;
}

bool User::checkPassword(string p) const
{
    return password==p;
}

int User::getUserId() const
{
    return id;
}
