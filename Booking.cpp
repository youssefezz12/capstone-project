#include "Booking.h"

Booking::Booking(std::string u, std::string p, std::string d)
    : user(u), provider(p), date(d) {}

std::string Booking::getUser() const {
    return user;
}

std::string Booking::getProvider() const {
    return provider;
}

std::string Booking::getDate() const {
    return date;
}
