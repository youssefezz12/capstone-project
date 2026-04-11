#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "System.h"
#include <QStackedWidget>
#include "loginscreen.h"
#include "usersearch.h"

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
    void handleSearch(QString);

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    LoginScreen *loginScreen;
    UserSearch *usersearch;
    System* system;
};

#endif
