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
    std::vector<Provider> providers;
    std::vector<Booking>  bookings;
    DatabaseManager*      db;

public:
    System();
    ~System();

    void registerUser(QString username, QString password);
    bool login(QString username, QString password);
    bool loginProvider(QString name, QString password);

    void addProvider(const Provider& provider);

    std::vector<Provider> filterByCategory(QString category);
    bool bookService(User user, Provider provider, QString date);

    std::vector<Booking>  getBookings() const;

    // Returns all providers from DB (used by dashboard to resolve current provider)
    std::vector<Provider> getProviders();

    // Convenience: find one provider by name via DB
    Provider* findProviderByName(const QString& name);
};

#endif
