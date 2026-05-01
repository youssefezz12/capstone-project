#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <map>
#include <vector>
#include <string>

class Notifications
{
private:
    std::map<std::string, std::vector<std::string>> notifications;

public:
    void addNotification(std::string user, std::string msg);
    std::vector<std::string> getNotifications(std::string user);
};

#endif
