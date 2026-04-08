#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include "usersearch.h"

namespace Ui { class LoginScreen; }

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = nullptr);
    ~LoginScreen();

signals:
    void loginAsCustomer();
    void loginAsProvider();
    void registerClicked();

private slots:
    void handleLogin();

    void on_registerButton_clicked();

private:
    Ui::LoginScreen *ui;
    UserSearch *usersearch;
};

#endif
