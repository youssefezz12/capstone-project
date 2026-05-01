#include "notifications.h"

void NotificationManager::addNotification(std::string user, std::string msg)
{
    notifications[user].push_back(msg);
}

std::vector<std::string> NotificationManager::getNotifications(std::string user)
{
    return notifications[user];
}
