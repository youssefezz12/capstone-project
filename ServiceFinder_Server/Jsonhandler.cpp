#include "Jsonhandler.h"
#include "Provider.h"

json::object JsonHandler::processRequest(json::value& request, std::shared_ptr<System> system)
{
    std::string command = request.as_object()["command"].as_string().c_str();

    if (command == "login")
        return handleLogin(request, system);
    else if (command == "loginProvider")
        return loginProvider(request, system);
    else if (command == "addUser")
        return addUser(request, system);
    else if (command == "addProvider")
        return addProvider(request, system);
    else if (command == "filterByCategory")
        return handleSearch(request, system);
    else if (command == "getBookings")
        return getBookings(request, system);
    else if (command == "bookService")
        return bookService(request, system);
    else if (command == "getProviderByName")
        return getProviderByName(request, system);
    else if (command == "updateProvider")
        return updateProvider(request, system);
    else if (command == "notifications")
        return handleNotifications(request, system);
    else
    {
        json::object response;
        response["status"]  = "failure";
        response["command"] = command;
        response["message"] = "Unknown command: " + command;
        return response;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Existing handlers (unchanged logic, just cleaned up)
// ─────────────────────────────────────────────────────────────────────────────

json::object JsonHandler::handleLogin(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name     = request.as_object()["name"].as_string().c_str();
    std::string password = request.as_object()["password"].as_string().c_str();

    if (system->login(QString::fromStdString(name), QString::fromStdString(password)))
    {
        response["status"]  = "success";
        response["command"] = "login";
        response["message"] = name + " logged in successfully.";
    }
    else
    {
        response["status"]  = "failure";
        response["command"] = "login";
        response["message"] = "Invalid username or password.";
    }
    return response;
}

json::object JsonHandler::loginProvider(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name     = request.as_object()["name"].as_string().c_str();
    std::string password = request.as_object()["password"].as_string().c_str();

    if (system->loginProvider(QString::fromStdString(name), QString::fromStdString(password)))
    {
        response["status"]  = "success";
        response["command"] = "loginProvider";
        response["message"] = name + " logged in successfully.";
    }
    else
    {
        response["status"]  = "failure";
        response["command"] = "loginProvider";
        response["message"] = "Invalid username or password.";
    }
    return response;
}

json::object JsonHandler::addUser(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name     = request.as_object()["name"].as_string().c_str();
    std::string password = request.as_object()["password"].as_string().c_str();

    system->registerUser(QString::fromStdString(name), QString::fromStdString(password));
    response["status"]  = "success";
    response["command"] = "addUser";
    response["message"] = name + " registered as user successfully.";
    return response;
}

json::object JsonHandler::addProvider(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name     = request.as_object()["name"].as_string().c_str();
    std::string password = request.as_object()["password"].as_string().c_str();

    // Category and price can be set from the provider dashboard after registration
    Provider p(name, password, "Default", 0.0);
    system->addProvider(p);

    response["status"]  = "success";
    response["command"] = "addProvider";
    response["message"] = name + " registered as provider successfully.";
    return response;
}

json::object JsonHandler::handleSearch(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    QString category = QString::fromStdString(
        request.as_object()["category"].as_string().c_str()
        );

    auto providers = system->filterByCategory(category);

    json::array results;
    for (const auto& p : providers)
    {
        json::object obj;
        obj["name"]      = p.getUserName();
        obj["category"]  = p.getCategory();
        obj["price"]     = p.getPrice();
        results.push_back(obj);
    }

    response["status"]  = "success";
    response["command"] = "filterByCategory";
    response["results"] = results;
    return response;
}


// Returns all bookings that belong to a given provider username.
// Client sends: { "command": "getBookings", "providerName": "Alice" }
json::object JsonHandler::getBookings(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string providerName = request.as_object()["providerName"].as_string().c_str();

    auto allBookings = system->getBookings();

    json::array results;
    for (const auto& b : allBookings)
    {
        if (b.getProvider() == providerName)
        {
            json::object obj;
            obj["user"]     = b.getUser();
            obj["provider"] = b.getProvider();
            obj["date"]     = b.getDate();
            results.push_back(obj);
        }
    }

    response["status"]   = "success";
    response["command"]  = "getBookings";
    response["bookings"] = results;
    return response;
}

// Creates a new booking.
// Client sends: { "command": "bookService", "customerName": "Bob",
//                 "providerName": "Alice", "date": "2026-06-01" }
json::object JsonHandler::bookService(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string customerName = request.as_object()["customerName"].as_string().c_str();
    std::string providerName = request.as_object()["providerName"].as_string().c_str();
    std::string date         = request.as_object()["date"].as_string().c_str();

    // Look up User and Provider objects so System::bookService can use them
    User     u(customerName, "");
    Provider p(providerName, "", "Default", 0.0);

    system->bookService(u, p, QString::fromStdString(date));

    response["status"]  = "success";
    response["command"] = "bookService";
    response["message"] = customerName + " booked " + providerName + " on " + date;
    return response;
}

// Fetches a single provider's full profile by username.
// Client sends: { "command": "getProviderByName", "name": "Alice" }
json::object JsonHandler::getProviderByName(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name = request.as_object()["name"].as_string().c_str();

    Provider* p = system->findProviderByName(QString::fromStdString(name));

    if (p)
    {
        response["status"]    = "success";
        response["command"]   = "getProviderByName";
        response["name"]      = p->getUserName();
        response["category"]  = p->getCategory();
        response["price"]     = p->getPrice();
        response["available"] = p->isAvailable() ? 1 : 0;
    }
    else
    {
        response["status"]  = "failure";
        response["command"] = "getProviderByName";
        response["message"] = "Provider not found: " + name;
    }
    return response;
}

// Updates an existing provider's category, price, and availability.
// Client sends: { "command": "updateProvider", "name": "Alice",
//                 "category": "Cooking", "price": 75.0, "available": 1 }
json::object JsonHandler::updateProvider(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name     = request.as_object()["name"].as_string().c_str();
    std::string category = request.as_object()["category"].as_string().c_str();
    double      price    = request.as_object()["price"].as_double();

    // Reconstruct a Provider with the updated fields and persist via System
    Provider p(name, "", category, price);
    system->updateProvider(p);

    response["status"]  = "success";
    response["command"] = "updateProvider";
    response["message"] = name + " profile updated.";
    return response;
}

// Returns notifications for a user.
// Client sends: { "command": "notifications", "username": "Bob" }
json::object JsonHandler::handleNotifications(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    QString user = QString::fromStdString(
        request.as_object()["username"].as_string().c_str()
        );

    auto notes = system->getUserNotifications(user);

    json::array arr;
    for (auto& n : notes)
        arr.push_back(json::string(n));

    response["status"]        = "success";
    response["command"]       = "notifications";
    response["notifications"] = arr;
    return response;
}
