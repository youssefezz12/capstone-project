#include "usersearch.h"
#include "ui_usersearch.h"
#include <QJsonObject>
#include <QDate>
#include <QMessageBox>

UserSearch::UserSearch(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::UserSearch)
{
    ui->setupUi(this);
}

UserSearch::~UserSearch()
{
    delete ui;
}

// Populate search results table from the JSON array the server sends back.
// Columns: 0 = Name, 1 = Category, 2 = Price
void UserSearch::editSearchTable(const QJsonArray& results)
{
    ui->searchTable->setRowCount(results.size());
    ui->searchTable->setColumnCount(3);
    ui->searchTable->setHorizontalHeaderLabels({"Name", "Category", "Price"});

    for (int i = 0; i < results.size(); i++)
    {
        QJsonObject obj = results[i].toObject();
        ui->searchTable->setItem(i, 0,
                                 new QTableWidgetItem(obj["name"].toString()));
        ui->searchTable->setItem(i, 1,
                                 new QTableWidgetItem(obj["category"].toString()));
        ui->searchTable->setItem(i, 2,
                                 new QTableWidgetItem(
                                     QString::number(obj["price"].toDouble(), 'f', 2)));
    }
}

void UserSearch::on_search_button_clicked()
{
    emit searchButtonClicked(ui->categoryLineEdit->text());
}

// Called when the user clicks the Book button.
// Reads the selected row from searchTable to get the provider name,
// and uses today's date as a placeholder (add a date picker to the UI later).
void UserSearch::on_book_button_clicked()
{
    int row = ui->searchTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection",
                             "Please select a provider from the list first.");
        return;
    }

    QString providerName = ui->searchTable->item(row, 0)->text();
    QString date         = QDate::currentDate().toString("yyyy-MM-dd");

    emit bookServiceRequested(providerName, date);
}
