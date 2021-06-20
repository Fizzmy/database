#include "detail.h"
#include "ui_detail.h"

detail::detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detail)
{
    ui->setupUi(this);
    connect(ui->returnButton,SIGNAL(clicked()),this,SLOT(navigateToMainPage()));
    connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(deleteData()));
    connect(ui->modifyButton,SIGNAL(clicked()),this,SLOT(navigateToModify()));
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(navigateToAdd()));
}
void detail::navigateToAdd()
{
    QStringList header;
    emit showModifyPage(kind,header,0);
}
void detail::deleteData()
{
    QString del=ui->deleteLine->text();
    int pos=del.toInt();
    if (pos>=1&&pos<=row)
    {
        ui->deleteLine->setText("");
        QString a;
        if (kind==1)
        {
            a="DELETE FROM s WHERE ";
            a.append("sclass='");
            a.append(queryModel->record(pos-1).value(0).toString());
            a.append("' AND sno='");
            a.append(queryModel->record(pos-1).value(1).toString());
            a.append("'");
        }
        else if (kind==2)
        {
            a="DELETE FROM c WHERE ";
            a.append("cno='");
            a.append(queryModel->record(pos-1).value(0).toString());
            a.append("'");
        }
        else
        {
            a="DELETE FROM sc WHERE ";
            a.append("sclass='");
            a.append(queryModel->record(pos-1).value(0).toString());
            a.append("' AND sno='");
            a.append(queryModel->record(pos-1).value(1).toString());
            a.append("' AND cno='");
            a.append(queryModel->record(pos-1).value(2).toString());
            a.append("'");
        }
        QSqlQuery query;
        query.exec(a);
        this->getdata(kind);
    }
    else QMessageBox::warning(this,"错误","数据不合法");

}
void detail::navigateToMainPage()
{
    this->hide();
    emit showMainPage();
}
void detail::navigateToModify()
{
    int x=ui->modifyLine->text().toInt();

    if (x>=1&&x<=row)
    {
        ui->modifyLine->setText("");
        QStringList header;
        if (kind==1) header<<queryModel->record(x-1).value(0).toString()<<queryModel->record(x-1).value(1).toString();
        else if (kind==2) header<<queryModel->record(x-1).value(0).toString();
        else if (kind==3) header<<queryModel->record(x-1).value(0).toString()<<queryModel->record(x-1).value(1).toString()<<queryModel->record(x-1).value(2).toString();

        if (kind==1) pre1=queryModel->record(x-1).value(0).toInt(),pre2=queryModel->record(x-1).value(1).toInt();
        else if (kind==2) pre1=queryModel->record(x-1).value(0).toInt();
        else pre1=queryModel->record(x-1).value(0).toInt(),pre2=queryModel->record(x-1).value(1).toInt(),pre3=queryModel->record(x-1).value(2).toInt();
        emit showModifyPage(kind,header,1);
    }
    else
        QMessageBox::warning(this,"错误","数据不合法");

}
void detail::showDetailPage(int x)
{
    kind=x;
    if (x==1)
    {
        this->setWindowTitle("学生信息表");
        ui->label->setText("学生信息表");
        getdata(1);
    }
    else if (x==2)
    {
        this->setWindowTitle("课程信息表");
        ui->label->setText("课程信息表");
        getdata(2);
    }
    else if (x==3)
    {
        this->setWindowTitle("成绩信息表");
        ui->label->setText("成绩信息表");
        getdata(3);
    }
    this->show();
}
void detail::getdata(int x)
{
    QSqlQuery query;
    row=0,column=0;
    QString sql;
    if (x==1)
        sql=QString("select * from s");
    else if (x==2)
        sql=QString("select * from c");
    else sql=QString("select * from sc");
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
void detail::getData(int k,QStringList data,bool tag)
{
    if (tag==0)
    {
        QString a;
        if (k==1)
            a="INSERT INTO s VALUES (";
        else if (k==2) a="INSERT INTO c VALUES (";
        else a="INSERT INTO sc VALUES (";
        for (int i=0;i<data.count();i++)
        {
            if (data[i]=="")
            {
                a.append("NULL,");
            }
            else
            {
                a.append("'");
                a.append(data[i]);
                a.append("'");
                a.append(",");
            }
            //qDebug()<<a;

        }
        a.chop(1);
        a.append(")");
        QSqlQuery query;
        //qDebug()<<a;
        query.exec(a);
    }
    else
    {
        QSqlQuery query;
        QSqlRecord sqlRecord;

        sqlRecord=queryModel->record();
        QString nw;
        QString sql;
        //qDebug()<<tag;
        if (k==1)
        {
            sql="update s set ";
            for (int j=0;j<column;j++)
            {
                nw=data[j];
                if (nw!=sqlRecord.value(j).toString())
                {
                    if (nw!="")
                        sql.append(QString("%1='%2',").arg(sqlRecord.fieldName(j)).arg(nw));
                    else
                        sql.append(QString("%1=NULL,").arg(sqlRecord.fieldName(j)));

                }
            }
            sql.chop(1);
            sql.append(QString(" where sclass='%1' AND sno='%2'").arg(pre1).arg(pre2));
        }
        else if (k==2)
        {
            sql="update c set ";
            for (int j=0;j<column;j++)
            {
                nw=data[j];
                if (nw!=sqlRecord.value(j).toString())
                {
                    if (nw!="")
                        sql.append(QString("%1='%2',").arg(sqlRecord.fieldName(j)).arg(nw));
                    else
                        sql.append(QString("%1=NULL,").arg(sqlRecord.fieldName(j)));

                }
            }
            sql.chop(1);
            sql.append(QString(" where cno='%1'").arg(pre1));
        }
        else
        {
            sql="update sc set ";
            for (int j=0;j<column;j++)
            {
                nw=data[j];
                if (nw!=sqlRecord.value(j).toString())
                {
                    if (nw!="")
                        sql.append(QString("%1='%2',").arg(sqlRecord.fieldName(j)).arg(nw));
                    else
                        sql.append(QString("%1=NULL,").arg(sqlRecord.fieldName(j)));

                }
            }
            sql.chop(1);
            sql.append(QString(" where sclass='%1' AND sno='%2' AND cno='%3'").arg(pre1).arg(pre2).arg(pre3));
        }
        //qDebug()<<sql;
        query.exec(sql);
    }
    getdata(kind);
}
detail::~detail()
{
    delete ui;
}
