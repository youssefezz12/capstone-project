#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QtSql>
#include <vector>
#include "User.h"
#include "Provider.h"
#include "Booking.h"

using std::vector;

class DatabaseManager
{
private:
    QSqlDatabase db;

public:
    DatabaseManager();

    // Users
    void registerUser(QString username, QString pass);
    bool verifyUser(QString name, QString pass);

    // Providers
    bool verifyProvider(QString name, QString pass);
    void addProvider(Provider p);
    void updateProvider(Provider p);               // NEW: saves price/category changes
    vector<Provider> getProviders(QString cat);    // existing: filter by category
    vector<Provider> getAllProviders();             // NEW: no WHERE clause
    Provider*        getProviderByName(QString name); // NEW: single provider lookup

    // Bookings
    void           saveBooking(User u, Provider p, QString date);
    vector<Booking> getBooking();
    vector<Booking> getBookingsForProvider(QString providerName); // NEW: filtered
};

#endif // DATABASEMANAGER_H
