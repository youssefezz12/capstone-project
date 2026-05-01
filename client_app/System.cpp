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

bool System::login(QString username, QString password) {

    if(db->verifyUser(username, password))
        return true;
    return false;
}
bool System::loginProvider(QString name, QString password)
{
    if(db->verifyProvider(name, password))
        return true;
    return false;
}
void System::addProvider(const Provider& provider) {

    db->addProvider(provider);
}

std::vector<Provider> System::filterByCategory(QString category) {
    std::vector<Provider> result;

    result= db->getProviders(category);

    return result;
}

bool System::bookService(User user, Provider provider, QString date) {
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

void System::registerUser(QString username, QString password)
{
    db->registerUser(username, password);
}

System::~System()
{
    delete db;
}


