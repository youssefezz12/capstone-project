/********************************************************************************
** Form generated from reading UI file 'providerdashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVIDERDASHBOARD_H
#define UI_PROVIDERDASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProviderDashboard
{
public:
    QWidget *widget;
    QWidget *widget_2;
    QStackedWidget *stackedWidget;
    QWidget *ProfilePage;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *priceInput;
    QTextEdit *descriptionInput;
    QPushButton *saveProfileBtn;
    QLabel *priceLabel;
    QLabel *categoryLabel;
    QLabel *nameLabel;
    QLabel *label_6;
    QLabel *statusLabel;
    QWidget *AvailabilityPage;
    QLabel *label_5;
    QPushButton *availabilityBtnToggle;
    QWidget *ReviewsPage;
    QListWidget *reviewsList;
    QWidget *EarningsPage;
    QLabel *earningsLabel;
    QLabel *jobLabel;
    QWidget *BookingsPage;
    QListWidget *bookingList;
    QWidget *widget_3;
    QPushButton *profileBtn;
    QPushButton *bookingsBtn;
    QPushButton *reviewsBtn;
    QPushButton *availabilityBtn;
    QPushButton *earningsBtn;
    QLabel *welcomeLabel;

    void setupUi(QWidget *ProviderDashboard)
    {
        if (ProviderDashboard->objectName().isEmpty())
            ProviderDashboard->setObjectName("ProviderDashboard");
        ProviderDashboard->resize(771, 546);
        widget = new QWidget(ProviderDashboard);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 20, 411, 341));
        widget->setStyleSheet(QString::fromUtf8("border-color: rgb(109, 51, 255);\n"
"background-color: rgb(223, 255, 219);"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(151, 41, 241, 271));
        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 20, 201, 241));
        ProfilePage = new QWidget();
        ProfilePage->setObjectName("ProfilePage");
        label = new QLabel(ProfilePage);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 57, 14));
        label_2 = new QLabel(ProfilePage);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 57, 14));
        label_3 = new QLabel(ProfilePage);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 40, 57, 14));
        label_4 = new QLabel(ProfilePage);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 60, 81, 16));
        priceInput = new QLineEdit(ProfilePage);
        priceInput->setObjectName("priceInput");
        priceInput->setGeometry(QRect(50, 40, 51, 22));
        descriptionInput = new QTextEdit(ProfilePage);
        descriptionInput->setObjectName("descriptionInput");
        descriptionInput->setGeometry(QRect(0, 100, 161, 121));
        saveProfileBtn = new QPushButton(ProfilePage);
        saveProfileBtn->setObjectName("saveProfileBtn");
        saveProfileBtn->setGeometry(QRect(80, 220, 91, 22));
        priceLabel = new QLabel(ProfilePage);
        priceLabel->setObjectName("priceLabel");
        priceLabel->setGeometry(QRect(110, 40, 57, 14));
        categoryLabel = new QLabel(ProfilePage);
        categoryLabel->setObjectName("categoryLabel");
        categoryLabel->setGeometry(QRect(110, 20, 57, 14));
        nameLabel = new QLabel(ProfilePage);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setGeometry(QRect(110, 0, 57, 14));
        label_6 = new QLabel(ProfilePage);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 80, 57, 14));
        statusLabel = new QLabel(ProfilePage);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(80, 80, 57, 14));
        stackedWidget->addWidget(ProfilePage);
        AvailabilityPage = new QWidget();
        AvailabilityPage->setObjectName("AvailabilityPage");
        label_5 = new QLabel(AvailabilityPage);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 161, 16));
        availabilityBtnToggle = new QPushButton(AvailabilityPage);
        availabilityBtnToggle->setObjectName("availabilityBtnToggle");
        availabilityBtnToggle->setGeometry(QRect(0, 40, 141, 22));
        stackedWidget->addWidget(AvailabilityPage);
        ReviewsPage = new QWidget();
        ReviewsPage->setObjectName("ReviewsPage");
        reviewsList = new QListWidget(ReviewsPage);
        reviewsList->setObjectName("reviewsList");
        reviewsList->setGeometry(QRect(0, 60, 211, 161));
        stackedWidget->addWidget(ReviewsPage);
        EarningsPage = new QWidget();
        EarningsPage->setObjectName("EarningsPage");
        earningsLabel = new QLabel(EarningsPage);
        earningsLabel->setObjectName("earningsLabel");
        earningsLabel->setGeometry(QRect(0, 40, 131, 16));
        jobLabel = new QLabel(EarningsPage);
        jobLabel->setObjectName("jobLabel");
        jobLabel->setGeometry(QRect(0, 90, 111, 16));
        stackedWidget->addWidget(EarningsPage);
        BookingsPage = new QWidget();
        BookingsPage->setObjectName("BookingsPage");
        bookingList = new QListWidget(BookingsPage);
        bookingList->setObjectName("bookingList");
        bookingList->setGeometry(QRect(30, 30, 131, 191));
        stackedWidget->addWidget(BookingsPage);
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(17, 41, 111, 271));
        profileBtn = new QPushButton(widget_3);
        profileBtn->setObjectName("profileBtn");
        profileBtn->setGeometry(QRect(0, 40, 80, 22));
        bookingsBtn = new QPushButton(widget_3);
        bookingsBtn->setObjectName("bookingsBtn");
        bookingsBtn->setGeometry(QRect(0, 70, 80, 22));
        reviewsBtn = new QPushButton(widget_3);
        reviewsBtn->setObjectName("reviewsBtn");
        reviewsBtn->setGeometry(QRect(0, 100, 80, 22));
        availabilityBtn = new QPushButton(widget_3);
        availabilityBtn->setObjectName("availabilityBtn");
        availabilityBtn->setGeometry(QRect(0, 130, 80, 22));
        earningsBtn = new QPushButton(widget_3);
        earningsBtn->setObjectName("earningsBtn");
        earningsBtn->setGeometry(QRect(0, 160, 80, 22));
        welcomeLabel = new QLabel(widget);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setGeometry(QRect(30, 10, 57, 14));

        retranslateUi(ProviderDashboard);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ProviderDashboard);
    } // setupUi

    void retranslateUi(QWidget *ProviderDashboard)
    {
        ProviderDashboard->setWindowTitle(QCoreApplication::translate("ProviderDashboard", "Form", nullptr));
        label->setText(QCoreApplication::translate("ProviderDashboard", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("ProviderDashboard", "Category :", nullptr));
        label_3->setText(QCoreApplication::translate("ProviderDashboard", "Price : ", nullptr));
        label_4->setText(QCoreApplication::translate("ProviderDashboard", "Description :", nullptr));
        saveProfileBtn->setText(QCoreApplication::translate("ProviderDashboard", "Save Changes", nullptr));
        priceLabel->setText(QString());
        categoryLabel->setText(QString());
        nameLabel->setText(QString());
        label_6->setText(QCoreApplication::translate("ProviderDashboard", "Status: ", nullptr));
        statusLabel->setText(QString());
        label_5->setText(QCoreApplication::translate("ProviderDashboard", "Availability Status :", nullptr));
        availabilityBtnToggle->setText(QCoreApplication::translate("ProviderDashboard", "Toggle Availability", nullptr));
        earningsLabel->setText(QCoreApplication::translate("ProviderDashboard", "Total earnings :", nullptr));
        jobLabel->setText(QCoreApplication::translate("ProviderDashboard", "Completed Jobs :", nullptr));
        profileBtn->setText(QCoreApplication::translate("ProviderDashboard", "Profile", nullptr));
        bookingsBtn->setText(QCoreApplication::translate("ProviderDashboard", "Bookings", nullptr));
        reviewsBtn->setText(QCoreApplication::translate("ProviderDashboard", "Reviews", nullptr));
        availabilityBtn->setText(QCoreApplication::translate("ProviderDashboard", "Availability", nullptr));
        earningsBtn->setText(QCoreApplication::translate("ProviderDashboard", "Earnings", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("ProviderDashboard", "Welcome ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProviderDashboard: public Ui_ProviderDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVIDERDASHBOARD_H
