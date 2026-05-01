#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(System* system)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
    , sys(system)
    , isProvider(false)
{
    ui->setupUi(this);

    // ── TCP socket setup ───────────────────────────────────────────────────
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::on_readReady);
    socket->connectToHost("127.0.0.1", 12345);
    if (!socket->waitForConnected(3000))
        qDebug() << "Connection failed.";
    else
        qDebug() << "Connected to server.";

    // ── Screens ────────────────────────────────────────────────────────────
    stackedWidget     = new QStackedWidget(this);
    loginScreen       = new LoginScreen(this);
    usersearch        = new UserSearch(this);
    providerDashboard = new ProviderDashboard(this);

    stackedWidget->addWidget(loginScreen);        // index 0
    stackedWidget->addWidget(usersearch);         // index 1
    stackedWidget->addWidget(providerDashboard);  // index 2
    setCentralWidget(stackedWidget);

    // ── Signal wiring ──────────────────────────────────────────────────────
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

// ─────────────────────────────────────────────────────────────────────────────
// Navigation
// ─────────────────────────────────────────────────────────────────────────────

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
    // Load the dashboard with the system + the username captured at login.
    // This is the bridge between the no-arg slot (matching friends' code)
    // and the dashboard's need to know which provider is logged in.
    providerDashboard->loadForProvider(sys, loggedInUsername);
    stackedWidget->setCurrentWidget(providerDashboard);
}

// ─────────────────────────────────────────────────────────────────────────────
// Outgoing socket commands
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::handleLogin(QString username, QString password, bool isProvider)
{
    loggedInUsername  = username;
    this->isProvider  = isProvider;

    QJsonObject req;
    req["name"]     = username;
    req["password"] = password;
    req["command"]  = isProvider ? "loginProvider" : "login";

    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact));
}

void MainWindow::handleRegister(QString username, QString password, bool isProvider)
{
    loggedInUsername  = username;
    this->isProvider  = isProvider;

    QJsonObject req;
    req["name"]     = username;
    req["password"] = password;
    req["command"]  = isProvider ? "addProvider" : "addUser";

    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact));
}

void MainWindow::handleSearch(QString category)
{
    QJsonObject req;
    req["category"] = category;
    req["command"]  = "filterByCategory";
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact));
}

// ─────────────────────────────────────────────────────────────────────────────
// Incoming socket responses
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_readReady()
{
    QByteArray data = socket->readAll();

    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseErr);
    if (parseErr.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseErr.errorString();
        return;
    }

    QJsonObject response = doc.object();
    QString status  = response["status"].toString();
    QString message = response["message"].toString();
    QString cmd     = response["command"].toString();

    qDebug() << response;

    if (status == "success" &&
        (cmd == "login" || cmd == "loginProvider" ||
         cmd == "addUser" || cmd == "addProvider"))
    {
        qDebug() << "Auth success for command:" << cmd;
        if (isProvider)
            showProviderDashboard();
        else
            showCustomerDashboard();
    }
    else if (status == "success" && cmd == "filterByCategory")
    {
        QJsonArray results = response["results"].toArray();
        usersearch->editSearchTable(results);
    }
    else
    {
        QMessageBox::warning(this, "Error", message);
    }
}
