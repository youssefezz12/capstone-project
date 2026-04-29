#include "System.h"
#include <QDebug>
#include <fstream>
#include <sstream>


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
    return true;
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


