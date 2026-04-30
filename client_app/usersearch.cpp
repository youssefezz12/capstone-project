#include "usersearch.h"
#include "ui_usersearch.h"
#include <string>
#include "System.h"

UserSearch::UserSearch(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserSearch)
{
    ui->setupUi(this);
    ui->searchTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

void UserSearch::editSearchTable(const QJsonArray &searchResult)
{
    ui->searchTable->setRowCount(searchResult.size());

    for(int i=0; i<searchResult.size(); i++)
    {
        QJsonObject object = searchResult[i].toObject();
        ui->searchTable->setItem(i,0, new QTableWidgetItem(object["name"].toString()));
        ui->searchTable->setItem(i,1, new QTableWidgetItem(object["category"].toString()));
        ui->searchTable->setItem(i, 2, new QTableWidgetItem(QString::number(object["price"].toDouble(), 'f', 2)));
    }
}

