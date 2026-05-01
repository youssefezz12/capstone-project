#ifndef SYSTEM_H
#define SYSTEM_H
#include "notifications.h"
#include <vector>
#include <string>
#include <QString>
#include "User.h"
#include "Provider.h"
#include "Booking.h"
#include "Databasemanager.h"

class System {
private:
    std::vector<User> users;
    std::vector<Provider> providers;
    std::vector<Booking> bookings;
    DatabaseManager *db;
    Notifications notifier;
    int bookingVersion = 0;

public:
    System();
    void registerUser(QString username, QString password);
    bool login(QString username, QString password);
    bool loginProvider(QString name, QString password);

    void addProvider(const Provider& provider);
    std::vector<Provider> filterByCategory(QString category);

    bool bookService(User user, Provider provider, QString date);
    std::vector<std::string> getUserNotifications(QString username);
    int getVersion() const;
    std::vector<Booking> getBookings() const;
    std::vector<Provider> getProviders();
    ~System();
};

#endif
