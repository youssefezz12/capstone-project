#include "notifications.h"

void Notifications::addNotification(std::string user, std::string msg)
{
    notifications[user].push_back(msg);
}

std::vector<std::string> Notifications::getNotifications(std::string user)
{
    return notifications[user];
}
