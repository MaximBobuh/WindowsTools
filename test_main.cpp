#include <QApplication>

#include "Scanner.h"
#include "TempScanAlgorithm.h"
#include "EventScanAlgorithm.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Scanner scanner1(new EventScanAlgorithm);
    Scanner scanner2(new TempScanAlgorithm);

    return app.exec();
}

