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
    emit loginAttempt(
        ui->lineEdit->text(),
        ui->lineEdit_2->text()
        );
}

void LoginScreen::on_registerButton_clicked()
{
    emit registerAttempt(
        ui->lineEdit->text(),
        ui->lineEdit_2->text()
        );
}
