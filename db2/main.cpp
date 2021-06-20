#include "mainwindow.h"
#include <detail.h>
#include <modify.h>
#include <search.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    detail detailPage;
    modify modifyPage;
    search searchPage;
    w.show();
    QObject::connect(&w,SIGNAL(showDetailPage(int)),&detailPage,SLOT(showDetailPage(int)));
    QObject::connect(&detailPage,SIGNAL(showMainPage()),&w,SLOT(showMainPage()));
    QObject::connect(&w,SIGNAL(showSearchPage()),&searchPage,SLOT(showSearchPage()));
    QObject::connect(&searchPage,SIGNAL(showMainPage()),&w,SLOT(showMainPage()));
    QObject::connect(&detailPage,SIGNAL(showModifyPage(int,QStringList,bool)),&modifyPage,SLOT(showModifyPage(int,QStringList,bool)));
    QObject::connect(&modifyPage,SIGNAL(sendData(int,QStringList,bool)),&detailPage,SLOT(getData(int,QStringList,bool)));
    return a.exec();
}
