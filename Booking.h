#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
private:
    std::string user;
    std::string provider;
    std::string date;

public:
    Booking(std::string user, std::string provider, std::string date);

    std::string getUser() const;
    std::string getProvider() const;
    std::string getDate() const;
};

#endif
