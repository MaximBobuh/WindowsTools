#ifndef EVENTSCANALGORITHM_H
#define EVENTSCANALGORITHM_H

#include <string>
#include <windows.h>
#include <QStringList>

#include "ScanAlgorithm.h"




class EventScanAlgorithm : public ScanAlgorithm
{
    typedef int EVENT_TYPE;

    void getEvent(const std::string&, EVENT_TYPE);
    void showEvent(const EVENTLOGRECORD*);

public:
    EventScanAlgorithm();
    void scanSection(int, QStringList&);

private:
    QStringList result;
};

#endif // EVENTSCANALGORITHM_H
