#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

#include "eventmanager.h"

const int BUFFER_SIZE = 20000;
const std::string EVENT_TYPE[] = {"", "ERROR_EVENT", "WARNING_EVENT", "", "INFORMATION_EVENT"};

void Event_Manager::showEvents()
{
    HANDLE hEventLog;
    LPCTSTR logName = L"Application";
    EVENTLOGRECORD* eventInfo;
    DWORD noteSize, nextNoteSize, eventLogCounter = 0;
    BYTE buffer[BUFFER_SIZE];


    hEventLog = OpenEventLog(NULL, logName);
    if(logName == NULL)
        std::cout << "Could not open event log!";

    eventInfo = (EVENTLOGRECORD*)&buffer;
    GetOldestEventLogRecord(hEventLog, &eventLogCounter);

    std::cout << eventLogCounter;

    while(ReadEventLog(hEventLog, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
                       0, eventInfo, BUFFER_SIZE, &noteSize, &nextNoteSize))
    {
        while(noteSize > 0)
        {
//            std::cout << eventLogCounter++ << "   EVENT ID: " << std::setw(12) << eventInfo->EventID
//                      << "  EVENT TYPE: "  << eventInfo->EventType << "  EVENT SOURCE: "
//                      << (char*)((LPBYTE)eventInfo + sizeof(EVENTLOGRECORD)) << std::endl;

//            std::cout << eventLogCounter++ << "   Event ID: " << std::setw(12) << eventInfo->EventID
//                      << "  EventType: "  << EVENT_TYPE[eventInfo->EventType] << "  Source: "
//                      << (char*)((LPBYTE)eventInfo + sizeof(EVENTLOGRECORD)) << std::endl;

            for(int i = 0; i < 20; ++i)
                std::cout << (char*)((LPBYTE)eventInfo + sizeof(EVENTLOGRECORD) + i);
            std::cout << std::endl;

            noteSize -= eventInfo->Length;
            eventInfo = (EVENTLOGRECORD*)((LPBYTE)eventInfo + eventInfo->Length);

        }
        eventInfo = (EVENTLOGRECORD*)&buffer;
    }
}


