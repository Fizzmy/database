#include "modify.h"
#include "ui_modify.h"

modify::modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modify)
{
    ui->setupUi(this);
    connect(ui->submit,SIGNAL(clicked()),this,SLOT(submitData()));
    connect(ui->return_2,SIGNAL(clicked()),this,SLOT(back()));
    name[0]=ui->label1;name[1]=ui->label2;name[2]=ui->label3;
    name[3]=ui->label4;name[4]=ui->label5;name[5]=ui->label6;
    value[0]=ui->lineEdit1;value[1]=ui->lineEdit2;value[2]=ui->lineEdit3;
    value[3]=ui->lineEdit4;value[4]=ui->lineEdit5;value[5]=ui->lineEdit6;
    QWidget::setTabOrder(value[0], value[1]);
    QWidget::setTabOrder(value[1], value[2]);
    QWidget::setTabOrder(value[2], value[3]);
    QWidget::setTabOrder(value[3], value[4]);
    QWidget::setTabOrder(value[4], value[5]);



}
void modify::back()
{
    this->hide();
}
void modify::showModifyPage(int kind,QStringList data,bool x)
{
    k=kind;tag=x;
    if (x)
    {
        this->setWindowTitle("修改数据");
        ui->label->setText("修改数据");
        QString a;
        if (kind==1)
        {
            a="SELECT * FROM s WHERE ";
            a.append("sclass='");
            a.append(data[0]);
            a.append("' AND sno='");
            a.append(data[1]);
            a.append("'");
        }
        else if (kind==2)
        {
            a="SELECT * FROM c WHERE ";
            a.append("cno='");
            a.append(data[0]);
            a.append("'");
        }
        else
        {
            a="SELECT * FROM sc WHERE ";
            a.append("sclass='");
            a.append(data[0]);
            a.append("' AND sno='");
            a.append(data[1]);
            a.append("' AND cno='");
            a.append(data[2]);
            a.append("'");
        }
        QSqlQuery query;
        QString sql=a;
        query.exec(sql);
        //qDebug()<<sql<<endl;
        queryModel = new QSqlQueryModel();
        queryModel->setQuery(query);
        column = queryModel->columnCount();
        for (int i=column;i<6;i++) name[i]->setVisible(0),value[i]->setVisible(0);
        for (int i=0;i<column;i++)
        {
            name[i]->setVisible(1),value[i]->setVisible(1);
            name[i]->setText(queryModel->record(0).fieldName(i));
            if (!queryModel->record(0).value(i).isNull())
                value[i]->setText(queryModel->record(0).value(i).toString());
            else value[i]->setText("");
        }
    }
    else
    {
        this->setWindowTitle("添加数据");
        ui->label->setText("添加数据");
        QString a;
        if (kind==1)
            a="SELECT * FROM s";
        else if (kind==2)
            a="SELECT * FROM c";
        else
            a="SELECT * FROM sc";
        QSqlQuery query;
        QString sql=a;
        query.exec(sql);
        queryModel = new QSqlQueryModel();
        queryModel->setQuery(query);
        column = queryModel->columnCount();
        for (int i=column;i<6;i++) name[i]->setVisible(0),value[i]->setVisible(0);
        for (int i=0;i<column;i++)
        {
            name[i]->setVisible(1),value[i]->setVisible(1);
            name[i]->setText(queryModel->record(0).fieldName(i));
            value[i]->setText("");
        }
    }
    this->show();

}
void modify::submitData()
{
    QStringList data;
    QString a;
    //qDebug()<<column;
    for (int i=0;i<column;i++)
        data<<value[i]->text();
    //qDebug()<<data;
    emit sendData(k,data,tag);
    this->hide();

}
modify::~modify()
{
    delete ui;
}
