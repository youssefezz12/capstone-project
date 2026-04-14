#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User
{
    private:
        string username;
        int id;
        string password;
        static int idCounter;

    public:
    User(string username, string password);
    string getUserName() const;
    bool checkPassword(string password) const;
    int getUserId() const;
    string getPassword() const;
};


#endif 
