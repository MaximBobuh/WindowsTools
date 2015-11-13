#include <QProcess>
#include <QWindow>
#include <QDir>
#include <windows.h>
#include <QDebug>

#include "RegCleaner.h"

RegCleaner::RegCleaner(QWidget *parent) : QWidget(parent)
{
    QProcess *vec = new QProcess;
    QDir::setCurrent("C:\\Users\\Maxim\\Documents\\Visual Studio 2013\\Projects\\Scn\\Scn\\bin\\Debug");
    vec->startDetached("Scn.exe");


    HWND handle = 0;
    while(handle == 0)
        handle = FindWindow(NULL,L"Form1");

    WId wid = (WId)handle;
    QWindow *win = QWindow::fromWinId(wid);

    QWidget::createWindowContainer(win, this)->setFixedSize(win->size());
    setFixedSize(win->size());


    qDebug() << win->size();
}
