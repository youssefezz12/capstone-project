#include "providerdashboard.h"
#include "ui_providerdashboard.h"

ProviderDashboard::ProviderDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProviderDashboard)
{
    ui->setupUi(this);

    // 🔹 Navigation
    connect(ui->profileBtn, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->bookingsBtn, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->availabilityBtn, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->reviewsBtn, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(3);
    });

    connect(ui->earningsBtn, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(4);
    });

    // 🔹 Save profile (price update)
    connect(ui->saveProfileBtn, &QPushButton::clicked, [=]() {
        double newPrice = ui->priceInput->text().toDouble();

        // temporary update (since no setter exists)
        currentProvider = new Provider("Name", "pass", "Cooking" , 100);

        ui->priceLabel->setText(QString::number(newPrice));
    });

    // 🔹 Availability toggle (UI only for now)
    connect(ui->availabilityBtnToggle, &QPushButton::clicked, [=]() {
        if (ui->statusLabel->text() == "Available")
            ui->statusLabel->setText("Not Available");
        else
            ui->statusLabel->setText("Available");
    });

    //loadData();
}

ProviderDashboard::~ProviderDashboard()
{
    delete currentProvider;
delete ui;
}

void ProviderDashboard::loadData()
{
    // 🔹 Welcome
    ui->welcomeLabel->setText(
        "Welcome, " + QString::fromStdString(currentProvider->getUserName())
        );

    // 🔹 Provider info
    ui->nameLabel->setText(QString::fromStdString(currentProvider->getUserName()));
    ui->categoryLabel->setText(QString::fromStdString(currentProvider->getCategory()));
    ui->priceLabel->setText(QString::number(currentProvider->getPrice()));

    // 🔹 Fill input field
    ui->priceInput->setText(QString::number(currentProvider->getPrice()));

    if (currentProvider->isAvailable())
        ui->statusLabel->setText("Available");
    else
        ui->statusLabel->setText("Not Available");

    // 🔹 Bookings
    ui->bookingList->clear();

    auto bookings = system->getBookings();

    for (const auto& b : bookings)
    {
        if (b.getProvider() == currentProvider->getUserName())
        {
            QString item = QString::fromStdString(
                b.getUser() + " - " + b.getDate()
                );

            ui->bookingList->addItem(item);
        }
    }
}
