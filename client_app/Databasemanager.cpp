#include "Databasemanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DatabaseManager::DatabaseManager() {

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../service_finder.db");

    if (!db.open()) {
        qDebug() << "Error: Connection with database failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected to:" << QDir::currentPath;

        QSqlQuery query;

        query.exec("CREATE TABLE IF NOT EXISTS Users ("
                   "username TEXT PRIMARY KEY, "
                   "password TEXT)");

        query.exec("CREATE TABLE IF NOT EXISTS Providers ("
                   "username TEXT PRIMARY KEY, "
                   "password TEXT, "
                   "category TEXT, "
                   "price REAL, "
                   "available INTEGER)");

        query.exec("CREATE TABLE IF NOT EXISTS Bookings ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "customer_user TEXT, "
                   "provider_user TEXT, "
                   "booking_date TEXT)");
    }
}


void DatabaseManager::registerUser(QString username, QString pass) {
    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, password) VALUES (:user, :pass)");
    query.bindValue(":user", username);
    query.bindValue(":pass", pass);

    if (!query.exec()) {
        qDebug() << "Register User Error:" << query.lastError().text();
    }
}


bool DatabaseManager::verifyUser(QString name, QString pass) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE username = :user AND password = :pass");
    query.bindValue(":user", name);
    query.bindValue(":pass", pass);

    if (query.exec() && query.next()) {
        return true; // Match found
    }
    return false;
}

bool DatabaseManager::verifyProvider(QString name, QString pass)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Providers WHERE username = :user AND password = :pass");
    query.bindValue(":user", name);
    query.bindValue(":pass", pass);

    if(query.exec() && query.next())
        return true;
    return false;
}


void DatabaseManager::addProvider(Provider p) {
    QSqlQuery query;
    query.prepare("INSERT INTO Providers (username, password, category, price, available) "
                  "VALUES (:user, :pass, :cat, :price, :avail)");
    query.bindValue(":user", QString::fromStdString(p.getUserName()));
    query.bindValue(":pass", QString::fromStdString(p.getPassword()));
    query.bindValue(":cat", QString::fromStdString(p.getCategory()));
    query.bindValue(":price", p.getPrice());
    query.bindValue(":avail", p.isAvailable() ? 1 : 0);

    if (!query.exec()) {
        qDebug() << "Add Provider Error:" << query.lastError().text();
    }
}


vector<Provider> DatabaseManager::getProviders(QString cat) {
    vector<Provider> results;
    QSqlQuery query;
    query.prepare("SELECT * FROM Providers WHERE category = :cat");
    query.bindValue(":cat", cat);

    if (query.exec()) {
        while (query.next()) {
            Provider p(
                query.value("username").toString().toStdString(),
                query.value("password").toString().toStdString(),
                query.value("category").toString().toStdString(),
                query.value("price").toDouble()
                );
            results.push_back(p);
        }
    }
    return results;
}


void DatabaseManager::saveBooking(User u, Provider p, QString date) {
    QSqlQuery query;
    query.prepare("INSERT INTO Bookings (customer_user, provider_user, booking_date) "
                  "VALUES (:cust, :prov, :date)");
    query.bindValue(":cust", QString::fromStdString(u.getUserName()));
    query.bindValue(":prov", QString::fromStdString(p.getUserName()));
    query.bindValue(":date", date);

    if (!query.exec()) {
        qDebug() << "Save Booking Error:" << query.lastError().text();
    }
}

vector<Booking> DatabaseManager::getBooking()
{
    vector<Booking> result;

    QSqlQuery query("SELECT * FROM Bookings");

    while(query.next())
    {
        result.push_back(
            Booking(
                query.value("customer_user").toString().toStdString(),
                query.value("provider_user").toString().toStdString(),
                query.value("booking_date").toString().toStdString()
            )
        );
    }

    return result;
}
