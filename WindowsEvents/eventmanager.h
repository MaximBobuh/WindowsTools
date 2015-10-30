#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <windows.h>


typedef int EVENT_TYPE;

class EventManager
{
    void getEvent(const std::string&, EVENT_TYPE);
    void showEvent(const EVENTLOGRECORD*);

public:
    void run();
};

#endif // EVENTMANAGER_H

