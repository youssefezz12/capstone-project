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

    // ── TCP socket ─────────────────────────────────────────────────────────
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

    stackedWidget->addWidget(loginScreen);
    stackedWidget->addWidget(usersearch);
    stackedWidget->addWidget(providerDashboard);
    setCentralWidget(stackedWidget);

    // ── Signals ────────────────────────────────────────────────────────────
    connect(loginScreen, &LoginScreen::loginAttempt,
            this, &MainWindow::handleLogin);
    connect(loginScreen, &LoginScreen::registerAttempt,
            this, &MainWindow::handleRegister);
    connect(usersearch, &UserSearch::searchButtonClicked,
            this, &MainWindow::handleSearch);

    // Wire the "Book" button in UserSearch through MainWindow to the server
    connect(usersearch, &UserSearch::bookServiceRequested,
            this, &MainWindow::handleBookService);

    // When provider saves their profile, persist the change via the server
    connect(providerDashboard, &ProviderDashboard::profileUpdated,
            this, [this](const Provider& p) {
                QJsonObject req;
                req["command"]  = "updateProvider";
                req["name"]     = QString::fromStdString(p.getUserName());
                req["category"] = QString::fromStdString(p.getCategory());
                req["price"]    = p.getPrice();
                req["available"]= p.isAvailable() ? 1 : 0;
                sendJson(req);
            });

    showLogin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::sendJson(const QJsonObject& obj)
{
    socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
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

// Called after the server returns a successful getProviderByName response.
// By that point providerDashboard->loadForProvider() has already been called.
void MainWindow::showProviderDashboard()
{
    stackedWidget->setCurrentWidget(providerDashboard);
}

// ─────────────────────────────────────────────────────────────────────────────
// Outgoing commands
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::handleLogin(QString username, QString password, bool isProvider)
{
    loggedInUsername = username;
    this->isProvider = isProvider;

    QJsonObject req;
    req["name"]     = username;
    req["password"] = password;
    req["command"]  = isProvider ? "loginProvider" : "login";
    sendJson(req);
}

void MainWindow::handleRegister(QString username, QString password, bool isProvider)
{
    loggedInUsername = username;
    this->isProvider = isProvider;

    QJsonObject req;
    req["name"]     = username;
    req["password"] = password;
    req["command"]  = isProvider ? "addProvider" : "addUser";
    sendJson(req);
}

void MainWindow::handleSearch(QString category)
{
    QJsonObject req;
    req["command"]  = "filterByCategory";
    req["category"] = category;
    sendJson(req);
}

// Triggered when the user clicks "Book" on a provider row in UserSearch.
void MainWindow::handleBookService(QString providerName, QString date)
{
    QJsonObject req;
    req["command"]      = "bookService";
    req["customerName"] = loggedInUsername;
    req["providerName"] = providerName;
    req["date"]         = date;
    sendJson(req);
}

// ─────────────────────────────────────────────────────────────────────────────
// Incoming responses
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

    qDebug() << "Server response:" << response;

    // ── Auth success → request provider profile OR go to customer dashboard ──
    if (status == "success" &&
        (cmd == "login" || cmd == "loginProvider" ||
         cmd == "addUser" || cmd == "addProvider"))
    {
        if (isProvider) {
            // Before showing the dashboard, fetch the full provider profile
            // so the dashboard has name/category/price/availability to display.
            QJsonObject req;
            req["command"] = "getProviderByName";
            req["name"]    = loggedInUsername;
            sendJson(req);
        } else {
            showCustomerDashboard();
        }
        return;
    }

    // ── Provider profile loaded → populate dashboard and show it ─────────────
    if (status == "success" && cmd == "getProviderByName")
    {
        // Build a temporary Provider from the server response so the dashboard
        // does not need to call System directly (stays fully decoupled from DB).
        std::string name     = response["name"].toString().toStdString();
        std::string category = response["category"].toString().toStdString();
        double      price    = response["price"].toDouble();

        Provider p(name, "pass", category, price);
        providerDashboard->loadFromProvider(p, sys);
        showProviderDashboard();

        // Also immediately request this provider's bookings
        QJsonObject bookReq;
        bookReq["command"]      = "getBookings";
        bookReq["providerName"] = loggedInUsername;
        sendJson(bookReq);
        return;
    }

    // ── Bookings loaded → populate dashboard booking lists ───────────────────
    if (status == "success" && cmd == "getBookings")
    {
        QJsonArray bookings = response["bookings"].toArray();
        providerDashboard->loadBookingsFromJson(bookings);
        // Make sure we are actually showing the dashboard
        // (getBookings response can arrive before showProviderDashboard in rare cases)
        if (stackedWidget->currentWidget() != providerDashboard)
            showProviderDashboard();
        return;
    }

    // ── Search results ────────────────────────────────────────────────────────
    if (status == "success" && cmd == "filterByCategory")
    {
        QJsonArray results = response["results"].toArray();
        usersearch->editSearchTable(results);
        return;
    }

    // ── bookService confirmation ──────────────────────────────────────────────
    if (status == "success" && cmd == "bookService")
    {
        QMessageBox::information(this, "Booking Confirmed", message);
        return;
    }

    // ── updateProvider confirmation (silent — no popup needed) ───────────────
    if (status == "success" && cmd == "updateProvider")
    {
        qDebug() << "Provider profile updated on server.";
        return;
    }

    // ── Any failure ───────────────────────────────────────────────────────────
    if (status == "failure")
    {
        QMessageBox::warning(this, "Error", message);
        return;
    }
}
