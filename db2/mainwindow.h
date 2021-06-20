#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QProcess>

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
    void navigateToStudentPage();
    void navigateToCoursePage();
    void navigateToGradePage();
    void showMainPage();
    void navigateToSearch();
    void backup();
    void rebackup();
signals:
    void showDetailPage(int x);
    void showSearchPage();
private:
    Ui::MainWindow *ui;
    void dbInit();
};
#endif // MAINWINDOW_H
