#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(System *system)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
    , sys(system)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    loginScreen = new LoginScreen(this);
    usersearch = new UserSearch(this);
    providerDashboard = new ProviderDashboard(this);

    stackedWidget->addWidget(loginScreen);
    stackedWidget->addWidget(usersearch);
    stackedWidget->addWidget(providerDashboard);

    connect(loginScreen, &LoginScreen::loginAttempt,
            this, &MainWindow::handleLogin);

    connect(loginScreen, &LoginScreen::registerAttempt,
            this, &MainWindow::handleRegister);

    connect(usersearch, &UserSearch::searchButtonClicked,
            this, &MainWindow::handleSearch);

    showLogin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLogin()
{
    stackedWidget->setCurrentWidget(loginScreen);
}

void MainWindow::showCustomerDashboard()
{
    stackedWidget->setCurrentWidget(usersearch);
}

void MainWindow::showProviderDashboard()
{
    stackedWidget->setCurrentWidget(providerDashboard);
}

void MainWindow::handleLogin(QString username, QString password, bool isProvider)
{
    if (sys->login(username.toStdString(), password.toStdString())) {

        if (isProvider) {
            showProviderDashboard();
        } else {
            showCustomerDashboard();
        }
    }
}

void MainWindow::handleRegister(QString username, QString password, bool isProvider)
{
    sys->registerUser(username.toStdString(), password.toStdString());

    if (isProvider) {
        showProviderDashboard();
    } else {
        showCustomerDashboard();
    }
}

void MainWindow::handleSearch(QString cat)
{
    auto result = sys->filterByCategory(cat.toStdString());
    usersearch->editSearchTable(result);
}
