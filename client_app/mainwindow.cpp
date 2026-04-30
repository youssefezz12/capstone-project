#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(System *system)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
    , sys(system)
{
    ui->setupUi(this);

    // socket start
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::on_readReady);
    socket->connectToHost("127.0.0.1", 12345);

    if(!socket->waitForConnected(3000))
        qDebug() << "Connection failed.";
    else
        qDebug() << "Connected to server.";
    // socket end

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
    QJsonObject authReq;

    authReq["name"] = username;
    authReq["password"] = password;

    if (isProvider)
    {
        authReq["command"] = "loginProvider";
    } else
    {
        authReq["command"] = "login";
    }
    QJsonDocument doc(authReq);
    socket->write(doc.toJson(QJsonDocument::Compact));
    this->isProvider = isProvider;
}

void MainWindow::on_readReady()
{
    QByteArray data = socket->readAll();

    QJsonParseError er;
    QJsonDocument doc = QJsonDocument::fromJson(data, &er);

    if(er.error != QJsonParseError::NoError)
    {
        qDebug() << "Json Parse Error: " << er.errorString();
        return;
    }

    QJsonObject response = doc.object();

    QString status = response["status"].toString();
    QString message = response["message"].toString();
    QString cmd = response["command"].toString();

    qDebug() << response;

    if(status == "success" && (cmd == "login" || cmd == "loginProvider" || cmd == "addUser" || cmd == "addProvider"))
    {
        qDebug() << "Success for command:" << cmd << "Message:" << message;
            if(isProvider)
                showProviderDashboard();
            else
                showCustomerDashboard();
    }
    else if(status == "success" && cmd == "filterByCategory")
    {
        QJsonArray results = response["results"].toArray();

        usersearch->editSearchTable(results);

    }
    else
        QMessageBox::warning(this, "Login Failed", message);

}

void MainWindow::handleRegister(QString username, QString password, bool isProvider)
{
    QJsonObject authReq;

    authReq["name"] = username;
    authReq["password"] = password;

    if (isProvider)
    {
        authReq["command"] = "addProvider";
    } else
    {
        authReq["command"] = "addUser";
    }
    QJsonDocument doc(authReq);
    socket->write(doc.toJson(QJsonDocument::Compact));
    this->isProvider = isProvider;
}

void MainWindow::handleSearch(QString cat)
{
    QJsonObject request;
    request["category"] = cat;
    request["command"] = "filterByCategory";

    QJsonDocument doc(request);
    socket->write(doc.toJson(QJsonDocument::Compact));

}
