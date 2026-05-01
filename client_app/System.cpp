#include "System.h"
#include <QDebug>
#include <fstream>
#include <sstream>
#include <string>


System::System()
{
    providers.clear();
    users.clear();
    bookings.clear();
    db = new DatabaseManager();
}

System::~System()
{
    delete db;
}

bool System::login(QString username, QString password)
{
    return db->verifyUser(username, password);
}

bool System::loginProvider(QString name, QString password)
{
    return db->verifyProvider(name, password);
}

void System::registerUser(QString username, QString password)
{
    db->registerUser(username, password);
}

void System::addProvider(const Provider& provider)
{
    db->addProvider(provider);
}

std::vector<Provider> System::filterByCategory(QString category)
{
    return db->getProviders(category);
}

bool System::bookService(User user, Provider provider, QString date)
{
    db->saveBooking(user, provider, date);
    bookingVersion++;
    std::string providerName = provider.getUserName();
    std::string userName = user.getUserName();

    notifier.addNotification(
        providerName,
        "New booking from " + userName
        );

    notifier.addNotification(
        userName,
        "Booking confirmed with " + providerName
        );
    return true;
}

std::vector<std::string> System::getUserNotifications(QString username)
{
    return notifier.getNotifications(username.toStdString());
}

int System::getVersion() const
{
    return bookingVersion;
}

std::vector<Booking> System::getBookings() const {
    auto result = db->getBooking();        // add implementation of this function
    return result;
}

std::vector<Provider> System::getProviders()
{
    // Pass empty string to get all providers (assumes DB supports it)
    return db->getProviders("");
}

// Finds a provider by name by fetching all from DB.
// Returns a pointer into a locally-allocated Provider; caller must not
// store this pointer long-term (use a copy instead for safety).
Provider* System::findProviderByName(const QString& name)
{
    providers = db->getProviders("");   // refresh local cache
    for (auto& p : providers) {
        if (p.getUserName() == name.toStdString())
            return &p;
    }
    return nullptr;
}
