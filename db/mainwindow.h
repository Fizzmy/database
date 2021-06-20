#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void search();
    void search2();
private:
    Ui::MainWindow *ui;
    QSqlQueryModel* queryModel;
    void dbInit();
    void getdata();
    void getquery(QString);
    int row,column;
};
#endif // MAINWINDOW_H
