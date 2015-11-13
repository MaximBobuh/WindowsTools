#ifndef TEMPSCANALGORITHM_H
#define TEMPSCANALGORITHM_H

#include "ScanAlgorithm.h"

class TempScanAlgorithm : public ScanAlgorithm
{
public:
    TempScanAlgorithm();

    void scanSection(int, QStringList&);
};

#endif // TEMPSCANALGORITHM_H
