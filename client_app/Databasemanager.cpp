#include "Databasemanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../service_finder.db");

    if (!db.open()) {
        qDebug() << "Error: Connection with database failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected.";

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

// ─────────────────────────────────────────────────────────────────────────────
// Users
// ─────────────────────────────────────────────────────────────────────────────

void DatabaseManager::registerUser(QString username, QString pass)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, password) VALUES (:user, :pass)");
    query.bindValue(":user", username);
    query.bindValue(":pass", pass);
    if (!query.exec())
        qDebug() << "registerUser error:" << query.lastError().text();
}

bool DatabaseManager::verifyUser(QString name, QString pass)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM Users WHERE username = :user AND password = :pass");
    query.bindValue(":user", name);
    query.bindValue(":pass", pass);
    return query.exec() && query.next();
}

// ─────────────────────────────────────────────────────────────────────────────
// Providers
// ─────────────────────────────────────────────────────────────────────────────

bool DatabaseManager::verifyProvider(QString name, QString pass)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM Providers WHERE username = :user AND password = :pass");
    query.bindValue(":user", name);
    query.bindValue(":pass", pass);
    return query.exec() && query.next();
}

void DatabaseManager::addProvider(Provider p)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Providers (username, password, category, price, available) "
                  "VALUES (:user, :pass, :cat, :price, :avail)");
    query.bindValue(":user",  QString::fromStdString(p.getUserName()));
    query.bindValue(":pass",  QString::fromStdString(p.getPassword()));
    query.bindValue(":cat",   QString::fromStdString(p.getCategory()));
    query.bindValue(":price", p.getPrice());
    query.bindValue(":avail", p.isAvailable() ? 1 : 0);
    if (!query.exec())
        qDebug() << "addProvider error:" << query.lastError().text();
}

// Updates price, category, and availability for an existing provider.
void DatabaseManager::updateProvider(Provider p)
{
    QSqlQuery query;
    query.prepare("UPDATE Providers SET category = :cat, price = :price, available = :avail "
                  "WHERE username = :user");
    query.bindValue(":cat",   QString::fromStdString(p.getCategory()));
    query.bindValue(":price", p.getPrice());
    query.bindValue(":avail", p.isAvailable() ? 1 : 0);
    query.bindValue(":user",  QString::fromStdString(p.getUserName()));
    if (!query.exec())
        qDebug() << "updateProvider error:" << query.lastError().text();
}

// Returns providers matching a category.
vector<Provider> DatabaseManager::getProviders(QString cat)
{
    vector<Provider> results;
    QSqlQuery query;
    query.prepare("SELECT * FROM Providers WHERE category = :cat");
    query.bindValue(":cat", cat);
    if (query.exec()) {
        while (query.next()) {
            results.push_back(Provider(
                query.value("username").toString().toStdString(),
                query.value("password").toString().toStdString(),
                query.value("category").toString().toStdString(),
                query.value("price").toDouble()
                ));
        }
    }
    return results;
}

// Returns ALL providers regardless of category.
vector<Provider> DatabaseManager::getAllProviders()
{
    vector<Provider> results;
    QSqlQuery query("SELECT * FROM Providers");
    while (query.next()) {
        results.push_back(Provider(
            query.value("username").toString().toStdString(),
            query.value("password").toString().toStdString(),
            query.value("category").toString().toStdString(),
            query.value("price").toDouble()
            ));
    }
    return results;
}

// Returns a heap-allocated Provider for the given username, or nullptr.
// Caller takes ownership — store in a unique_ptr or delete manually.
Provider* DatabaseManager::getProviderByName(QString name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Providers WHERE username = :user");
    query.bindValue(":user", name);
    if (query.exec() && query.next()) {
        return new Provider(
            query.value("username").toString().toStdString(),
            query.value("password").toString().toStdString(),
            query.value("category").toString().toStdString(),
            query.value("price").toDouble()
            );
    }
    return nullptr;
}

// ─────────────────────────────────────────────────────────────────────────────
// Bookings
// ─────────────────────────────────────────────────────────────────────────────

void DatabaseManager::saveBooking(User u, Provider p, QString date)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Bookings (customer_user, provider_user, booking_date) "
                  "VALUES (:cust, :prov, :date)");
    query.bindValue(":cust", QString::fromStdString(u.getUserName()));
    query.bindValue(":prov", QString::fromStdString(p.getUserName()));
    query.bindValue(":date", date);
    if (!query.exec())
        qDebug() << "saveBooking error:" << query.lastError().text();
}

// Returns all bookings in the table.
vector<Booking> DatabaseManager::getBooking()
{
    vector<Booking> result;
    QSqlQuery query("SELECT * FROM Bookings");
    while (query.next()) {
        result.push_back(Booking(
            query.value("customer_user").toString().toStdString(),
            query.value("provider_user").toString().toStdString(),
            query.value("booking_date").toString().toStdString()
            ));
    }
    return result;
}

// Returns only the bookings where provider_user matches the given name.
vector<Booking> DatabaseManager::getBookingsForProvider(QString providerName)
{
    vector<Booking> result;
    QSqlQuery query;
    query.prepare("SELECT * FROM Bookings WHERE provider_user = :prov");
    query.bindValue(":prov", providerName);
    if (query.exec()) {
        while (query.next()) {
            result.push_back(Booking(
                query.value("customer_user").toString().toStdString(),
                query.value("provider_user").toString().toStdString(),
                query.value("booking_date").toString().toStdString()
                ));
        }
    }
    return result;
}
