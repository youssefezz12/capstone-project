#ifndef USERSEARCH_H
#define USERSEARCH_H

#include <QDialog>
#include "Provider.h"
#include <string>

namespace Ui {
class UserSearch;
}

class UserSearch : public QDialog
{
    Q_OBJECT

public:
    explicit UserSearch(QWidget *parent = nullptr);
    void editSearchTable(const QJsonArray&);
    ~UserSearch();

signals:
    void searchButtonClicked(QString);

private slots:
    void on_search_button_clicked();

private:
    Ui::UserSearch *ui;
};

#endif // USERSEARCH_H
