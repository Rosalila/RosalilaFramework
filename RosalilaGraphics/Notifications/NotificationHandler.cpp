#include "NotificationHandler.h"

void NotificationHandler::update()
{
    if(notifications.size()>0)
    {
        Notification* current_notification = *notifications.begin();
        if(notifications.size()>1)
        {
            interruptCurrentNotification();
        }
        current_notification->update();
        if(current_notification->isFinished())
        {
            notifications.pop_front();
            delete current_notification;
        }
    }
}

void NotificationHandler::interruptCurrentNotification()
{
    if(notifications.size()>0)
    {
        Notification* current_notification = *notifications.begin();
        current_notification->frame = current_notification->duration;
    }
}
