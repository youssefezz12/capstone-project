#include "Provider.h"
#include <string>
using namespace std;


Provider:: Provider(string n, string p, string c, double pr) : User(n,p)
{
    category = c;
    price = pr;
    available = true;
}

bool Provider:: isAvailable() const
{
    return available;
}

string Provider::getCategory() const
{
    return category;
}

double Provider::getPrice() const
{
    return price;
}
