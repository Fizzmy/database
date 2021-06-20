#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class detail;
}

class detail : public QWidget
{
    Q_OBJECT

public:
    explicit detail(QWidget *parent = nullptr);
    ~detail();
private slots:
    void showDetailPage(int);
    void navigateToMainPage();
    void deleteData();
    void navigateToModify();
    void getData(int,QStringList,bool);
    void navigateToAdd();

signals:
    void showModifyPage(int,QStringList,bool);
    void showMainPage();
private:
    Ui::detail *ui;
    void getdata(int);
    int pre1,pre2,pre3;
    int row,column;
    int kind=0;
    QSqlQueryModel *queryModel;
};

#endif // DETAIL_H
