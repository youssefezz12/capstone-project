#include "mainwindow.h"
#include "System.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>

MainWindow::MainWindow(System *system)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
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
    connect(usersearch, &UserSearch::searchButtonClicked, [&](QString category)
            { qDebug() << "Search triggered";
            qDebug() << "Category:" << category;
            system->getProviders();}); //The whole program crashes here!!!!
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
void MainWindow::showProviderDashboard()
{}
