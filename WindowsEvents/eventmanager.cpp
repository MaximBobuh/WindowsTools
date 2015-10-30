#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "eventmanager.h"


const int BUFFER_SIZE = 20000;


void EventManager::getEvent(const std::string& logName, EVENT_TYPE type)
{
    HANDLE hEventLog;
    EVENTLOGRECORD* eventInfo;
    DWORD noteSize, nextNoteSize, eventLogCounter = 0;
    BYTE buffer[BUFFER_SIZE];


    hEventLog = OpenEventLog(NULL, std::wstring(logName.begin(), logName.end()).c_str());
    if(hEventLog == NULL)
        std::cout << "Could not open event log!";

    eventInfo = (EVENTLOGRECORD*)&buffer;
    GetOldestEventLogRecord(hEventLog, &eventLogCounter);


    while(ReadEventLog(hEventLog, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
                       0, eventInfo, BUFFER_SIZE, &noteSize, &nextNoteSize))
    {
        while(noteSize > 0)
        {
            // Show event that contains a specified type.
            if(eventInfo->EventType & type)
                showEvent(eventInfo);

            noteSize -= eventInfo->Length;
            eventInfo = (EVENTLOGRECORD*)((LPBYTE)eventInfo + eventInfo->Length); // Next record.

        }
        eventInfo = (EVENTLOGRECORD*)&buffer;
    }
    CloseHandle(hEventLog);
}

//----------------------------------------------------

void EventManager::showEvent(const EVENTLOGRECORD* record)
{
    static const std::string eventName[] = {"Error", "Warning", "Information",
                                            "Success/Failure Audit"};
    int nameIndex = log(record->EventType) / log(2);

    std::wstring sourceName(reinterpret_cast<const wchar_t*>(
                                reinterpret_cast<const unsigned char*>(record) + sizeof(EVENTLOGRECORD)));

    std::cout << "Event ID: " << std::setw(12) << record->EventID << "  EventType: " << eventName[nameIndex]
              << "  Source: " << std::string(sourceName.begin(), sourceName.end()) << std::endl;
}

//----------------------------------------------------

void EventManager::run()
{
    getEvent("Application", EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE);
    getEvent("System", EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE);
}


