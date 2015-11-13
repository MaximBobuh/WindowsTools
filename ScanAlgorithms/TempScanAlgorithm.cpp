#include <QDir>
#include <QDebug>
#include "TempScanAlgorithm.h"

TempScanAlgorithm::TempScanAlgorithm() :  ScanAlgorithm("Temp files Scanner")
{
    QString userName = QDir::home().dirName();
    sections << userName + " Temp" << "Default Temp" << "All Users Temp" << "Windows Temp";
    fullSectionNames << "C:\\Users\\" + userName + "\\AppData\\Local\\Temp"
                     << "C:\\Users\\Default\\AppData\\Local\\Temp"
                     << "C:\\Users\\All Users\\TEMP" << "C:\\Windows\\Temp";
}

void TempScanAlgorithm::scanSection(int i, QStringList& result)
{
    QString name = fullSectionNames.at(i);
    QDir dir(name);
    result = dir.entryList(QDir::Files);

    for(auto pos = result.begin(); pos != result.end(); ++pos)
    {
       QString str(name + "\\" + *pos);
       *pos = str;
    }

}
