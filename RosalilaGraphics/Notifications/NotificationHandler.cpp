#include "NotificationHandler.h"

void NotificationHandler::update()
{
    if(notifications.size()>0)
    {
        Notification* current_notification = *notifications.begin();
        current_notification->update();
        if(current_notification->isFinished())
        {
            notifications.pop_front();
            delete current_notification;
        }
    }
}
