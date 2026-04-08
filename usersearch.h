#ifndef USERSEARCH_H
#define USERSEARCH_H

#include <QDialog>

namespace Ui {
class UserSearch;
}

class UserSearch : public QDialog
{
    Q_OBJECT

public:
    explicit UserSearch(QWidget *parent = nullptr);
    ~UserSearch();

private:
    Ui::UserSearch *ui;
};

#endif // USERSEARCH_H
