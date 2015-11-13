#ifndef SCANNER_H
#define SCANNER_H


#include <QObject>
#include "ScanAlgorithm.h"
#include "ScanWindow.h"
#include "DialogScan.h"

class Scanner : public QObject
{
    Q_OBJECT

    void analysisNotes(const QStringList&);

public:
    Scanner(ScanAlgorithm*);

public slots:
    void slotStartScan();

signals:
    void signalStopScan();

private:
    ScanAlgorithm* algorithm;
    ScanWindow sWindow;
    DialogScan* dialog;
};

#endif // SCANNER_H
