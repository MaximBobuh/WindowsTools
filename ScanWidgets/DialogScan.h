#ifndef DIALOGSCAN_H
#define DIALOGSCAN_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class DialogScan;
}

class DialogScan : public QDialog
{
    Q_OBJECT

public:
    explicit DialogScan(int s, QWidget *parent = 0);
    ~DialogScan();

    void setFound(int);
    void setNextFound();
    void setNextValue();
    void setInfo(const QString&);
    void setStop(bool);

    void closeEvent(QCloseEvent*);

public slots:
    bool slotStop();

signals:
    void signalStop();

private:
    int size;
    bool stop;
    Ui::DialogScan *ui;
};

#endif // DIALOGSCAN_H
