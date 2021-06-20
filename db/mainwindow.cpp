#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbInit();
    getdata();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(ui->search,SIGNAL(clicked()),this,SLOT(search()));
    connect(ui->search_2,SIGNAL(clicked()),this,SLOT(search2()));
}
void MainWindow::dbInit()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1"); //数据库服务器IP
    db.setUserName("root"); //数据库用户名
    db.setPassword("1234"); //数据库密码
    db.setDatabaseName("information");
    if( !db.open() ){ //数据库打开失败
       QMessageBox::warning(this,"错误",db.lastError().text());
       return;
    }
}
void MainWindow::getdata()
{
    QSqlQuery query;
    row=0,column=0;
    QString sql=QString("select * from s");
    query.exec(sql);
    queryModel = new QSqlQueryModel();
    queryModel->setQuery(query);
    row = queryModel->rowCount();
    ui->tableWidget->setRowCount(row);
    column = queryModel->columnCount();
    ui->tableWidget->setColumnCount(column);

    QSqlRecord sqlRecord=queryModel->record(0);
    QStringList header;
    for (int i=0;i<sqlRecord.count();i++)
        header<<sqlRecord.fieldName(i);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for (int i=0;i<row;i++)
    {
        sqlRecord=queryModel->record(i);
        for (int j=0;j<column;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(sqlRecord.value(j).toString()));
        }
    }
}
void MainWindow::getquery(QString sql)
{
    QSqlQuery query;
    query.exec(sql);
    queryModel = new QSqlQueryModel();
    queryModel->setQuery(query);
    row = queryModel->rowCount();
    ui->tableWidget->setRowCount(row);
    column = queryModel->columnCount();
    //qDebug()<<row<<" "<<column;
    QSqlRecord sqlRecord=queryModel->record(0);
    for (int i=0;i<row;i++)
    {
        sqlRecord=queryModel->record(i);
        for (int j=0;j<column;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(sqlRecord.value(j).toString()));
        }
    }
}
void MainWindow::search2()
{
    QString tag=ui->lineEdit->text();
    QString sql=QString("SELECT * FROM S WHERE Saddr LIKE \'\%%1\%\'").arg(tag);
    getquery(sql);
}
void MainWindow::search()
{
    QString tag=ui->lineEdit->text();
    QString sql=QString("SELECT * FROM S WHERE Saddr=\'%1\'").arg(tag);
    getquery(sql);
}
MainWindow::~MainWindow()
{
    delete ui;
}

