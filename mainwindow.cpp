#include "mainwindow.h"
#include "System.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>

MainWindow::MainWindow(System *system)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow), system(system)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    loginScreen = new LoginScreen(this);
    usersearch = new UserSearch(this);
    stackedWidget->addWidget(loginScreen);
    stackedWidget->addWidget(usersearch);

    // Connect login signals
    connect(loginScreen, &LoginScreen::loginAsCustomer, this, &MainWindow::showCustomerDashboard);
    connect(loginScreen, &LoginScreen::loginAsProvider, this, &MainWindow::showProviderDashboard);

    connect(usersearch, &UserSearch::searchButtonClicked, this, &MainWindow::handleSearch);

}
MainWindow::~MainWindow()
{
    delete ui;}

void MainWindow::showLogin()
{
    stackedWidget->setCurrentWidget(loginScreen);
}
void MainWindow::showCustomerDashboard()
{
    stackedWidget->setCurrentWidget(usersearch);
}
void MainWindow::handleSearch(QString cat)
{
    auto searchResult = system->filterByCategory(cat.toStdString());
    usersearch->editSearchTable(searchResult);

}
void MainWindow::showProviderDashboard()
{}
