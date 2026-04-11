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

void UserSearch::editSearchTable(std::vector<Provider> searchResult)
{
    ui->searchTable->setRowCount(searchResult.size());
    for(int i=0; i<searchResult.size(); i++)
    {   ui->searchTable->setItem(i,0, new QTableWidgetItem(QString::fromStdString(searchResult[i].getUserName())));
        ui->searchTable->setItem(i,1, new QTableWidgetItem(QString::fromStdString(searchResult[i].getCategory())));
        ui->searchTable->setItem(i, 2, new QTableWidgetItem(QString::number(searchResult[i].getPrice(), 'f', 2)));
    }
}

