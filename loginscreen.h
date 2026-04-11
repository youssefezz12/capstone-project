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

private slots:
    void handleLogin();
    void registerClicked();

private:
    Ui::LoginScreen *ui;
    UserSearch *usersearch;
};

#endif
