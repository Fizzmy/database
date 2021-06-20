#ifndef MODIFY_H
#define MODIFY_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class modify;
}

class modify : public QWidget
{
    Q_OBJECT

public:
    explicit modify(QWidget *parent = nullptr);
    ~modify();

private:
    Ui::modify *ui;
    QSqlQueryModel *queryModel;
    QLabel *name[10];
    QLineEdit *value[10];
    int k=0,column,tag;
private slots:
    void showModifyPage(int,QStringList,bool);
    void submitData();
    void back();
signals:
    void sendData(int,QStringList,bool);
};

#endif // MODIFY_H
