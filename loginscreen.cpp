#include "loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_loginButton_clicked()
{
    bool isProvider = ui->providerRadio->isChecked();

    emit loginAttempt(
        ui->lineEdit->text(),
        ui->lineEdit_3->text(),
        isProvider
        );
}

void LoginScreen::on_registerButton_clicked()
{
    bool isProvider = ui->providerRadio->isChecked();

    emit registerAttempt(
        ui->lineEdit->text(),
        ui->lineEdit_3->text(),
        isProvider
        );
}
