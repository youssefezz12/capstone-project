#include "System.h"
#include <QDebug>

System::System()
{
    db = new DatabaseManager();
}

System::~System()
{
    delete db;
}

// ─────────────────────────────────────────────────────────────────────────────
// Auth
// ─────────────────────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────────────────────
// Providers
// ─────────────────────────────────────────────────────────────────────────────

void System::addProvider(const Provider& provider)
{
    db->addProvider(provider);
}

// Persists changes made in the provider dashboard (price, category, availability).
void System::updateProvider(const Provider& provider)
{
    db->updateProvider(provider);
}

std::vector<Provider> System::filterByCategory(QString category)
{
    return db->getProviders(category);
}

// Returns ALL providers — uses getAllProviders() so an empty string does not
// produce zero results (the old getProviders("") bug).
std::vector<Provider> System::getProviders()
{
    providers = db->getAllProviders();
    return providers;
}

// Fetches a single provider by username directly from the DB.
// Returns a pointer into the local cache — valid until the next getProviders() call.
Provider* System::findProviderByName(const QString& name)
{
    // Refresh local cache from DB so we always have up-to-date data
    providers = db->getAllProviders();
    for (auto& p : providers) {
        if (p.getUserName() == name.toStdString())
            return &p;
    }
    return nullptr;
}

// ─────────────────────────────────────────────────────────────────────────────
// Bookings
// ─────────────────────────────────────────────────────────────────────────────

bool System::bookService(User user, Provider provider, QString date)
{
    db->saveBooking(user, provider, date);
    return true;
}

std::vector<Booking> System::getBookings() const
{
    return db->getBooking();
}

// ─────────────────────────────────────────────────────────────────────────────
// Notifications (stub — wire to a Notifications table when ready)
// ─────────────────────────────────────────────────────────────────────────────

std::vector<std::string> System::getUserNotifications(const QString& username)
{
    Q_UNUSED(username)
    // Return empty list until a Notifications table is added to the DB.
    return {};
}
