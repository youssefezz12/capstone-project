#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QtSql>
#include "User.h"
#include "Provider.h"
#include "Booking.h"
#include <vector>

class DatabaseManager
{
private:
    QSqlDatabase db;
    QString dbPath;
public:
    DatabaseManager();
    void registerUser(QString username, QString pass);
    bool verifyUser(QString name, QString pass);
    void addProvider(Provider p);
    vector<Provider> getProviders(QString cat);
    void saveBooking(User u, Provider p, QString date);
    vector<Booking> getBooking();
};

#endif // DATABASEMANAGER_H
