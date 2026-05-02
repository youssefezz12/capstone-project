#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <boost/json.hpp>
#include "System.h"

namespace json = boost::json;

class JsonHandler
{
public:
    static json::object processRequest(json::value& request, std::shared_ptr<System> system);

private:
    static json::object handleLogin(json::value& request, std::shared_ptr<System> system);
    static json::object loginProvider(json::value& request, std::shared_ptr<System> system);
    static json::object addUser(json::value& request, std::shared_ptr<System> system);
    static json::object addProvider(json::value& request, std::shared_ptr<System> system);
    static json::object handleSearch(json::value& request, std::shared_ptr<System> system);


    static json::object getBookings(json::value& request, std::shared_ptr<System> system);
    static json::object bookService(json::value& request, std::shared_ptr<System> system);
    static json::object getProviderByName(json::value& request, std::shared_ptr<System> system);
    static json::object updateProvider(json::value& request, std::shared_ptr<System> system);
    static json::object handleNotifications(json::value& request, std::shared_ptr<System> system);
};

#endif // JSONHANDLER_H
