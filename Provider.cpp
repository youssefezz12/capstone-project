#include "Provider.h"
using namespace std;


Provider:: Provider(string n, string p, string c, double pr) : User(n,p)
{
    category = c;
    price = pr;
}

bool Provider:: isAvailable() const
{
    return available;
}
