#ifndef SCANWINDOW_H
#define SCANWINDOW_H

#include <QWidget>
#include <vector>


namespace Ui {
class ScanWindow;
}

class QTreeWidgetItem;
class QTreeWidget;


enum TreeType {SECTION_TREE, RESULT_TREE};

class ScanWindow : public QWidget
{
    Q_OBJECT

    typedef std::vector<int> Vector;

private:
    QTreeWidgetItem* createTreeItem(QTreeWidget*, const QString&);
    QTreeWidgetItem* createTreeChildItem(QTreeWidgetItem* par, const QString&, int col = 0);
    void createTreeChildItems(QTreeWidgetItem* par, const QStringList&, int col = 0);

public:
    explicit ScanWindow(QWidget *parent = 0);

    void addTreeItems(TreeType, const QString&, const QStringList&);
    void selectedSections(Vector&, int);

    ~ScanWindow();

public slots:
    // Change a checkbox for each a child item.
    void slotChangeItem(QTreeWidgetItem*, int);

signals:
    void signalStartScan();

private:
    Ui::ScanWindow *ui;
    std::vector<QTreeWidgetItem*> trees;
};

#endif // SCANWINDOW_H
