#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string>
#include <QString>
#include "User.h"
#include "Provider.h"
#include "Booking.h"
#include "Databasemanager.h"

class System {
private:
    std::vector<User>     users;
    std::vector<Provider> providers;   // local cache for findProviderByName
    std::vector<Booking>  bookings;
    DatabaseManager*      db;

public:
    System();
    ~System();

    // Auth
    void registerUser(QString username, QString password);
    bool login(QString username, QString password);
    bool loginProvider(QString name, QString password);

    // Providers
    void addProvider(const Provider& provider);
    void updateProvider(const Provider& provider);          //  persists dashboard edits
    std::vector<Provider> filterByCategory(QString category);
    std::vector<Provider> getProviders();
    Provider* findProviderByName(const QString& name);      // used by server getProviderByName

    // Bookings
    bool bookService(User user, Provider provider, QString date);
    std::vector<Booking> getBookings() const;

    // Notifications (stub — returns empty list until implemented)
    std::vector<std::string> getUserNotifications(const QString& username);
};

#endif
