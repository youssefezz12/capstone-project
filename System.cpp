#include "System.h"
#include <QDebug>

System::System()
{
    providers.clear();
    users.clear();
    bookings.clear();
}
void System::registerUser(std::string username, std::string password) {
    users.push_back(User(username, password));
}

bool System::login(std::string username, std::string password) {
    for (const auto& user : users) {
        if (user.getUserName() == username && user.checkPassword(password)) {
            return true;
        }
    }
    return false;
}

void System::addProvider(const Provider& provider) {
    providers.push_back(provider);
}

std::vector<Provider> System::filterByCategory(string category) {
    std::vector<Provider> result;

    for (const auto& p : providers) {
        qDebug() << "inside the provider vector";
        if (p.getCategory() == category) {
            result.push_back(p);
        }
    }

    return result;
}

bool System::bookService(std::string user, std::string provider, std::string date) {
    bookings.push_back(Booking(user, provider, date));
    return true;
}

std::vector<Booking> System::getBookings() const {
    return bookings;
}

System::~System()
{
    providers.clear();
}

std::vector<Provider> System::getProviders()
{
    // for(const auto& p: providers)
    // {
    //     qDebug() << QString::fromStdString(p.getUserName()) << Qt::endl;
    // }
    return providers;
}
