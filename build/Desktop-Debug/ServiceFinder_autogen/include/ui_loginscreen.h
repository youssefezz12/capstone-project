/********************************************************************************
** Form generated from reading UI file 'loginscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSCREEN_H
#define UI_LOGINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginScreen
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QWidget *widget_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QRadioButton *customerRadio;
    QRadioButton *providerRadio;
    QPushButton *loginButton;
    QPushButton *registerButton;

    void setupUi(QWidget *LoginScreen)
    {
        if (LoginScreen->objectName().isEmpty())
            LoginScreen->setObjectName("LoginScreen");
        LoginScreen->resize(733, 429);
        verticalLayout = new QVBoxLayout(LoginScreen);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(LoginScreen);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"background-color: #e8f4fd;\n"
"}"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(160, 10, 371, 391));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color:white;\n"
"border-radius:16 px;\n"
"}"));
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 10, 141, 61));
        QFont font;
        font.setPointSize(24);
        font.setItalic(true);
        label->setFont(font);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 90, 66, 18));
        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(30, 120, 241, 26));
        lineEdit->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color: #e8f4fd;\n"
"}"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 170, 66, 18));
        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(30, 200, 241, 26));
        lineEdit_3 = new QLineEdit(widget_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(30, 200, 241, 26));
        lineEdit_3->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color: #e8f4fd;\n"
"}"));
        lineEdit_3->setEchoMode(QLineEdit::EchoMode::Password);
        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 250, 66, 18));
        customerRadio = new QRadioButton(widget_2);
        customerRadio->setObjectName("customerRadio");
        customerRadio->setGeometry(QRect(80, 250, 110, 23));
        providerRadio = new QRadioButton(widget_2);
        providerRadio->setObjectName("providerRadio");
        providerRadio->setGeometry(QRect(210, 250, 110, 23));
        loginButton = new QPushButton(widget_2);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(30, 300, 94, 26));
        registerButton = new QPushButton(widget_2);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(170, 300, 94, 26));

        verticalLayout->addWidget(widget);


        retranslateUi(LoginScreen);

        QMetaObject::connectSlotsByName(LoginScreen);
    } // setupUi

    void retranslateUi(QWidget *LoginScreen)
    {
        LoginScreen->setWindowTitle(QCoreApplication::translate("LoginScreen", "Form", nullptr));
        label->setText(QCoreApplication::translate("LoginScreen", "ServLink", nullptr));
        label_2->setText(QCoreApplication::translate("LoginScreen", "Email:", nullptr));
        lineEdit->setText(QCoreApplication::translate("LoginScreen", "enter your email", nullptr));
        label_3->setText(QCoreApplication::translate("LoginScreen", "Password:", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("LoginScreen", "enter your password", nullptr));
        label_4->setText(QCoreApplication::translate("LoginScreen", "Role: ", nullptr));
        customerRadio->setText(QCoreApplication::translate("LoginScreen", "Customer", nullptr));
        providerRadio->setText(QCoreApplication::translate("LoginScreen", "Provider", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginScreen", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginScreen", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginScreen: public Ui_LoginScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSCREEN_H
