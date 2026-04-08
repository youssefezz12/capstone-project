#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <QMessageBox>
#include "usersearch.h"

LoginScreen::LoginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginScreen::handleLogin);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginScreen::registerClicked);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::handleLogin()
{
    if (ui->customerRadio->isChecked())
        emit loginAsCustomer();
    else if (ui->providerRadio->isChecked())
        emit loginAsProvider();
}

void LoginScreen::on_registerButton_clicked()
{
    QMessageBox::information(this, "Register", "The User has been created successfully");
    usersearch = new UserSearch(this);
    usersearch->show();
}

