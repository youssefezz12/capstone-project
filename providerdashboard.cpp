#include "providerdashboard.h"
#include "ui_providerdashboard.h"

ProviderDashboard::ProviderDashboard(System* sys, Provider provider, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProviderDashboard)
    , system(sys)
    , currentProvider(provider)
{
    ui->setupUi(this);

    loadData();
}

ProviderDashboard::~ProviderDashboard()
{
    delete ui;
}

void ProviderDashboard::loadData()
{
    // Provider info
    ui->nameLabel->setText(QString::fromStdString(currentProvider.getUserName()));
    ui->categoryLabel->setText(QString::fromStdString(currentProvider.getCategory()));
    ui->priceLabel->setText(QString::number(currentProvider.getPrice()));

    if (currentProvider.isAvailable())
        ui->statusLabel->setText("Available");
    else
        ui->statusLabel->setText("Not Available");

    // Bookings
    auto bookings = system->getBookings();

    for (const auto& b : bookings)
    {
        if (b.getProvider() == currentProvider.getUserName())
        {
            QString item = QString::fromStdString(
                b.getUser() + " - " + b.getDate()
                );

            ui->bookingList->addItem(item);
        }
    }
}
