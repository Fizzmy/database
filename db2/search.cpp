#include "search.h"
#include "ui_search.h"

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    connect(ui->returnButton,SIGNAL(clicked()),this,SLOT(navigateToMainPage()));
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(searchData()));
}
void search::navigateToMainPage()
{
    this->hide();
    emit showMainPage();
}
void search::showSearchPage()
{
    this->show();
    ui->name->setText("");
    ui->id->setText("");
}
void search::searchData()
{
    QSqlQuery query;
    row=0,column=0;
    QString sql;
    sql=(QString("SELECT sc.sclass,sc.sno,sname,ssex,sage,sdept,sc.cno,cname,cpno,ccredit,grade FROM s,c,sc WHERE s.sclass=sc.sclass AND s.sno=sc.sno AND c.cno=sc.cno AND sc.sclass='%1' AND sc.sno='%2'").arg(ui->name->text()).arg(ui->id->text()));
    qDebug()<<sql;
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
            if (!sqlRecord.value(j).isNull())
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(sqlRecord.value(j).toString()));
            else ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));
        }
    }
}
search::~search()
{
    delete ui;
}
