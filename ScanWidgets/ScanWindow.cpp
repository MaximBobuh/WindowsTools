#include <QRegularExpression>

#include "ScanWindow.h"
#include "ui_scanwindow.h"

#include <QDebug>

ScanWindow::ScanWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanWindow)
{
    ui->setupUi(this);
    ui->treeResult->header()->resizeSection(0, 130);
    ui->treeResult->header()->resizeSection(1, 400);
    //ui->treeResult->header()->resizeSection(2, 100);

    connect(ui->pushButton, SIGNAL(clicked(bool)), SIGNAL(signalStartScan()));
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this,
            SLOT(slotChangeItem(QTreeWidgetItem*,int)));
    connect(ui->treeResult, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this,
            SLOT(slotChangeItem(QTreeWidgetItem*,int)));
}

ScanWindow::~ScanWindow()
{
    delete ui;
    for(auto tree : trees)
        delete tree;
}

//------------------------------------------


QTreeWidgetItem* ScanWindow::createTreeItem(QTreeWidget* par, const QString& name)
{
    QTreeWidgetItem* root = new QTreeWidgetItem(par);
    root->setText(0, name);
    root->setFlags(root->flags() | Qt::ItemIsUserCheckable);
    root->setCheckState(0, Qt::Checked);

    trees.push_back(root);
    return root;
}

//------------------------------------------

QTreeWidgetItem* ScanWindow::createTreeChildItem(QTreeWidgetItem* par, const QString& itemName, int col)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(col, itemName);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(0, Qt::Checked);
    par->addChild(item);

    return item;
}


void ScanWindow::createTreeChildItems(QTreeWidgetItem* par, const QStringList& itemNames, int col)
{
    for(auto str : itemNames)
        createTreeChildItem(par, str, col);
}

//------------------------------------------


void ScanWindow::addTreeItems(TreeType type, const QString& name, const QStringList& subItems)
{
    QTreeWidget* tree;
    int colomn;

    if(type == SECTION_TREE)
    {
        tree = ui->treeWidget;
        colomn = 0;
    }
    else
    {
        tree = ui->treeResult;
        colomn = 1;
    }

    QTreeWidgetItem* root = createTreeItem(tree, name);
    createTreeChildItems(root, subItems, colomn);
    tree->expandItem(root);
}

//------------------------------------------

void ScanWindow::selectedSections(Vector& section_index, int type)
{
    auto tree = (type == 0 ? ui->treeWidget : ui->treeResult);
    auto root = tree->topLevelItem(0);

    for(int i = 0; i < root->childCount(); ++i)
    {
        if(root->child(i)->checkState(0) == Qt::Checked)
            section_index.push_back(i);
    }
}

//------------------------------------------

void ScanWindow::slotChangeItem(QTreeWidgetItem* item, int col)
{
    Qt::CheckState state = item->checkState(col);
    for(int i = 0; i < item->childCount(); ++i)
        item->child(i)->setCheckState(col, state);
}
