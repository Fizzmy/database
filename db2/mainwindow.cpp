#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <search.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->showStudent,SIGNAL(clicked()),this,SLOT(navigateToStudentPage()));
    connect(ui->showCourse,SIGNAL(clicked()),this,SLOT(navigateToCoursePage()));
    connect(ui->showGrade,SIGNAL(clicked()),this,SLOT(navigateToGradePage()));
    connect(ui->searchStudent,SIGNAL(clicked()),this,SLOT(navigateToSearch()));
    connect(ui->backupButton,SIGNAL(clicked()),this,SLOT(backup()));
    connect(ui->rebackupButton,SIGNAL(clicked()),this,SLOT(rebackup()));
    dbInit();
}
void MainWindow::backup()
{
    QString Cmd = QString("mysqldump -u%1 -p%2 information2 s c sc").arg("root","1234");
    QString Path = QString("%1").arg("E://qt//backup.sql");

    QProcess *poc=new QProcess;

    poc->setStandardOutputFile(Path);

    poc->start(Cmd);
    poc->waitForFinished();

    char* error=poc->readAllStandardError().data();
    QString a="执行操作成功，返回信息：\n";
    a.append(error);
    QMessageBox::information(0, "YES", a);
}
void MainWindow::rebackup()
{
    QString Cmd = QString("mysql -u%1 -p%2 information2").arg("root","1234");
    QString Path = QString("%1").arg("E://qt//backup.sql");

    QProcess *poc=new QProcess;

    poc->setStandardInputFile(Path);

    poc->start(Cmd);
    poc->waitForFinished();
    char* error=poc->readAllStandardError().data();
    QString a="执行操作成功，返回信息：\n";
    a.append(error);
    QMessageBox::information(0, "YES", a);

}
void MainWindow::dbInit()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1"); //数据库服务器IP
    db.setUserName("root"); //数据库用户名
    db.setPassword("1234"); //数据库密码
    db.setDatabaseName("information2");
    if( !db.open() ){ //数据库打开失败
       QMessageBox::warning(this,"错误",db.lastError().text());
       return;
    }
}
void MainWindow::showMainPage()
{
    this->show();
}
void MainWindow::navigateToStudentPage()
{
    this->hide();
    emit showDetailPage(1);
}
void MainWindow::navigateToCoursePage()
{
    this->hide();
    emit showDetailPage(2);
}
void MainWindow::navigateToGradePage()
{
    this->hide();
    emit showDetailPage(3);
}
void MainWindow::navigateToSearch()
{
    this->hide();
    emit showSearchPage();
}
MainWindow::~MainWindow()
{
    delete ui;
}

