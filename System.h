#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string>
#include <QString>
#include "User.h"
#include "Provider.h"
#include "Booking.h"

class System {
private:
    std::vector<User> users;
    std::vector<Provider> providers;
    std::vector<Booking> bookings;

public:
    System();
    void registerUser(std::string username, std::string password);
    bool login(std::string username, std::string password);

    void addProvider(const Provider& provider);
    std::vector<Provider> filterByCategory(std::string category);

    bool bookService(std::string user, std::string provider, std::string date);

    std::vector<Booking> getBookings() const;
    std::vector<Provider> getProviders();
    ~System();
};

#endif
