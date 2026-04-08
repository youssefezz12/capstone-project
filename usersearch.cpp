#include "usersearch.h"
#include "ui_usersearch.h"

UserSearch::UserSearch(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserSearch)
{
    ui->setupUi(this);
}

UserSearch::~UserSearch()
{
    delete ui;
}
