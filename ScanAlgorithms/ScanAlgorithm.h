#ifndef SCANALGORITHM_H
#define SCANALGORITHM_H

#include <QStringList>

class ScanAlgorithm
{
public:
    ScanAlgorithm(const QString&) : NAME(name) {}

    virtual void scanSection(int, QStringList&) = 0;
    const QStringList& getScanSection() const { return sections; }

    virtual ~ScanAlgorithm(){}

    const QString NAME;

protected:
    QStringList sections;
    QStringList fullSectionNames;
};


#endif // SCANALGORITHM_H
