#include "System.h"
#include <QDebug>
#include <fstream>
#include <sstream>


System::System()
{
    providers.clear();
    users.clear();
    bookings.clear();


    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != std::string::npos) {
            std::string username = line.substr(0, comma);
            std::string password = line.substr(comma + 1);
            users.push_back(User(username, password));
        }
    }
    std::ifstream pfile("providers.txt");

    while (std::getline(pfile, line)) {
        std::stringstream ss(line);
        std::string username, password, category, priceStr, availableStr;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, category, ',');
        getline(ss, priceStr, ',');
        getline(ss, availableStr, ',');

        double price = std::stod(priceStr);
        bool available = std::stoi(availableStr);

        Provider p(username, password, category, price);
        providers.push_back(p);
    }
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
    std::ofstream file("providers.txt", std::ios::app);
    file << provider.getUserName() << ","
         << provider.getPassword() << ","
         << provider.getCategory() << ","
         << provider.getPrice() << ","
         << provider.isAvailable()
         << "\n";
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

void System::registerUser(std::string username, std::string password)
{
    users.push_back(User(username, password));

    std::ofstream file("users.txt", std::ios::app);
    file << username << "," << password << "\n";
}

std::vector<Provider> System::getProviders()
{
    return providers;
}
System::~System()
{
    providers.clear();
}


