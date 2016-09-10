#ifndef NOTIFICATION_HANDLER_H
#define NOTIFICATION_HANDLER_H

#include <list>
#include "Notification.h"

using namespace std;

class Notification;

class NotificationHandler
{
public:
    list<Notification*>notifications;
    void update();
    void interruptCurrentNotification();
};

#endif
