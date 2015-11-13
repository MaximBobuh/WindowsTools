#include <QMessageBox>

#include "DialogScan.h"
#include "ui_dialogscan.h"

DialogScan::DialogScan(int s, QWidget *parent) :
    QDialog(parent), size(s), stop(false),
    ui(new Ui::DialogScan)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(size);
    ui->label->setText("Found: 0");

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(slotStop()));
}


DialogScan::~DialogScan()
{
    delete ui;
}

void DialogScan::closeEvent(QCloseEvent* ev)
{
    if(stop)
        QWidget::closeEvent(ev);
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Scanning"),
                              QString::fromUtf8("Are you sure?"),
                              QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            emit signalStop();
            QWidget::closeEvent(ev);
        }
        else
            ev->ignore();
    }
}

//----------------------------------------------------

void DialogScan::setNextValue()
{
    int value = (ui->progressBar->value() + 1) % (ui->progressBar->maximum() + 1);
    ui->progressBar->setValue(value);
}

void DialogScan::setInfo(const QString& str)
{
    ui->textEdit->setText(str);
}

void DialogScan::setFound(int val)
{
    ui->label->setText("Found: " + QString::number(val));
}

void DialogScan::setNextFound()
{
    setFound(++size);
}

void DialogScan::setStop(bool val)
{
    stop = val;
}

//----------------------------------------------------


bool DialogScan::slotStop()
{
    close();
}


