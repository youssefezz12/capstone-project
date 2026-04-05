#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    loginScreen = new LoginScreen(this);
    stackedWidget->addWidget(loginScreen);

    // Connect login signals
    connect(loginScreen, &LoginScreen::loginAsCustomer, this, &MainWindow::showCustomerDashboard);
    connect(loginScreen, &LoginScreen::loginAsProvider, this, &MainWindow::showProviderDashboard);
}

MainWindow::~MainWindow()
{
    delete ui;}

void MainWindow::showLogin()
{
    stackedWidget->setCurrentWidget(loginScreen);
}
void MainWindow::showCustomerDashboard()
{}
void MainWindow::showProviderDashboard()
{}
