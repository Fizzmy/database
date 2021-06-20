#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class search;
}

class search : public QWidget
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();
private slots:
    void showSearchPage();
    void searchData();
    void navigateToMainPage();
signals:
    void showMainPage();
private:
    Ui::search *ui;
    int row,column;
    QSqlQueryModel *queryModel;
};

#endif // SEARCH_H
