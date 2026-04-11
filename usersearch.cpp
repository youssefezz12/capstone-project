#include "usersearch.h"
#include "ui_usersearch.h"
#include <string>
#include "System.h"

UserSearch::UserSearch(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserSearch)
{
    ui->setupUi(this);
    //connect(search_button, &on_search_button::clicked, this, &MainWindow::showCustomerDashboard);
}

UserSearch::~UserSearch()
{
    delete ui;
}




void UserSearch::on_search_button_clicked()
{
    QString text = ui->categoryLineEdit->text();
    emit searchButtonClicked(text);
}

