#ifndef USERSEARCH_H
#define USERSEARCH_H

#include <QDialog>
#include <QJsonArray>
#include "Provider.h"
#include <string>

namespace Ui { class UserSearch; }

class UserSearch : public QDialog
{
    Q_OBJECT

public:
    explicit UserSearch(QWidget* parent = nullptr);
    ~UserSearch();

    // Populates the table from a JSON array returned by the server.
    // Each element: { "name": "...", "category": "...", "price": 0.0 }
    void editSearchTable(const QJsonArray& results);

signals:
    void searchButtonClicked(QString category);

    // Emitted when the user selects a provider row and clicks Book.
    // MainWindow catches this and sends a bookService command to the server.
    void bookServiceRequested(QString providerName, QString date);

private slots:
    void on_search_button_clicked();
    void on_book_button_clicked();   // NEW: connect in .ui or manually

private:
    Ui::UserSearch* ui;
};

#endif // USERSEARCH_H
