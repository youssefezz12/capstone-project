#ifndef PROVIDER_H
#define PROVIDER_H
#include "User.h"
#include <string>
using namespace std;

class Provider: public User
{
    private:
        string category;
        double price;
        bool available;

    public:
        Provider(string, string, string , double =0);
        bool isAvailable() const;
        string getCategory() const;
};
#endif
