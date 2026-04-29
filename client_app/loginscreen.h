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
    void loginAttempt(QString username, QString password, bool isProvider);
    void registerAttempt(QString username, QString password, bool isProvider);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::LoginScreen *ui;
    UserSearch *usersearch;
};

#endif
