#include <vector>
#include <QApplication>
#include "Scanner.h"

Scanner::Scanner(ScanAlgorithm* scanAlg) : algorithm(scanAlg), dialog(0)
{
    connect(&sWindow, SIGNAL(signalStartScan()), this, SLOT(slotStartScan()));

    sWindow.addTreeItems(SECTION_TREE, "Section to Scan", scanAlg->getScanSection());

    sWindow.setWindowTitle(algorithm->NAME);
    sWindow.show();
}

//-------------------------------------------------

void Scanner::slotStartScan()
{
    std::vector<int> section_index;
    sWindow.selectedSections(section_index, 0);

    if(!section_index.empty())
    {
        if(dialog)
            delete dialog;
        dialog = new DialogScan(section_index.size());
        dialog->show();

        const QStringList sections = algorithm->getScanSection();

        for(auto index : section_index)
        {
            QStringList result;
            algorithm->scanSection(index, result);
            analysisNotes(result);
            if(result.size() != 0)
                sWindow.addTreeItems(RESULT_TREE, sections.at(index), result);
            dialog->setNextValue();
        }
        delete dialog;
    }
}

//-------------------------------------------------

void Scanner::analysisNotes(const QStringList& list)
{
    for(auto str : list)
    {
        QApplication::processEvents();
        dialog->setInfo(str);
        dialog->setNextFound();
    }
}

//-------------------------------------------------

Scanner::~Scanner() { delete algorithm; }

//-------------------------------------------------
