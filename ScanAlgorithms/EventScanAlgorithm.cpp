#include "EventScanAlgorithm.h"
#include <iostream>


const int BUFFER_SIZE = 20000;


EventScanAlgorithm::EventScanAlgorithm() : ScanAlgorithm("Warning and Error Scanner")
{    
    fullSectionNames << "Application" << "System";
    sections = fullSectionNames;
}

//-------------------------------------------------

void EventScanAlgorithm::scanSection(int i, QStringList& res)
{
    getEvent(sections.at(i).toStdString(), EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE);
    res = result;
    result.clear();
}

//-------------------------------------------------
void EventScanAlgorithm::getEvent(const std::string& logName, EVENT_TYPE type)
{
    HANDLE hEventLog;
    EVENTLOGRECORD* eventInfo;
    DWORD noteSize, nextNoteSize;
    BYTE buffer[BUFFER_SIZE];

    static int eventLogCounter = 0;


    hEventLog = OpenEventLog(NULL, std::wstring(logName.begin(), logName.end()).c_str());
    if(hEventLog == NULL)
        std::cout << "Could not open event log!";

    eventInfo = (EVENTLOGRECORD*)&buffer;
    //GetOldestEventLogRecord(hEventLog, &eventLogCounter);


    while(ReadEventLog(hEventLog, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
                       0, eventInfo, BUFFER_SIZE, &noteSize, &nextNoteSize))
    {
        while(noteSize > 0)
        {
            // Show event that contains a specified type.
            if(eventInfo->EventType & type)
            {
                std::cout << eventLogCounter++;
                showEvent(eventInfo);
            }

            noteSize -= eventInfo->Length;
            eventInfo = (EVENTLOGRECORD*)((LPBYTE)eventInfo + eventInfo->Length); // Next record.

        }
        eventInfo = (EVENTLOGRECORD*)&buffer;
    }
    CloseHandle(hEventLog);
}

//----------------------------------------------------

void EventScanAlgorithm::showEvent(const EVENTLOGRECORD* record)
{
    static const std::wstring eventName[] = {L" Error", L"Warning", L"Information",
                                            L"Success/Failure Audit"};

    int nameIndex = log(record->EventType) / log(2);
    std::wstring sourceName(reinterpret_cast<const wchar_t*>(
                                reinterpret_cast<const unsigned char*>(record) + sizeof(EVENTLOGRECORD)));

    // Getting a description error by the error(warning) code.
    wchar_t* errorMess = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL, record->EventID, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
                  (wchar_t*)&errorMess, 0, NULL);

    QString tmp;
    tmp = QString::fromStdWString(eventName[nameIndex]) + "   " + QString::fromStdWString(sourceName)
            + ":  " + QString::number((int)record->EventID);

    result << tmp;

    /*
    if(errorMess == NULL)
    {
        errorMess = L"No description";
    }

    //----------------------------------



    std::wcout << " Event ID: "  << record->EventID << "  EventType: " << eventName[nameIndex]
               << "  Source: " << sourceName << std::endl
               << "Description: " << errorMess << std::endl << std::endl;


    std::wfstream file("report.txt", std::ios_base::out | std::ios_base::app);
    file << " Event ID: " << record->EventID << "  EventType: " << eventName[nameIndex]
         << "  Source: " << sourceName << std::endl
         << "Description: " << errorMess << std::endl << std::endl;
     */

    LocalFree((void*)errorMess);
}

//----------------------------------------------------

//void EventScanAlgorithm::run()
//{
//    getEvent("Application", EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE);
//    getEvent("System", EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE);
//}
