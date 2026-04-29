#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "System.h"
#include "loginscreen.h"
#include "usersearch.h"
#include "providerdashboard.h"
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(System*);
    ~MainWindow();

private slots:
    void showLogin();
    void showCustomerDashboard();
    void showProviderDashboard();
    void handleSearch(QString cat);
    void handleLogin(QString username, QString password, bool isProvider);
    void handleRegister(QString username, QString password, bool isProvider);
    void on_readReady();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    LoginScreen *loginScreen;
    UserSearch *usersearch;
    System* sys;
    ProviderDashboard *providerDashboard;
    QTcpSocket *socket;
    bool isProvider;
};

#endif
