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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProviderDashboard
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QLabel *categoryLabel;
    QLabel *priceLabel;
    QLabel *statusLabel;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label;
    QListWidget *bookingList;

    void setupUi(QWidget *ProviderDashboard)
    {
        if (ProviderDashboard->objectName().isEmpty())
            ProviderDashboard->setObjectName("ProviderDashboard");
        ProviderDashboard->resize(451, 373);
        verticalLayout_2 = new QVBoxLayout(ProviderDashboard);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        nameLabel = new QLabel(ProviderDashboard);
        nameLabel->setObjectName("nameLabel");

        verticalLayout->addWidget(nameLabel);

        categoryLabel = new QLabel(ProviderDashboard);
        categoryLabel->setObjectName("categoryLabel");

        verticalLayout->addWidget(categoryLabel);

        priceLabel = new QLabel(ProviderDashboard);
        priceLabel->setObjectName("priceLabel");

        verticalLayout->addWidget(priceLabel);

        statusLabel = new QLabel(ProviderDashboard);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);


        gridLayout->addLayout(verticalLayout, 0, 0, 4, 1);

        label_5 = new QLabel(ProviderDashboard);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(ProviderDashboard);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 1, 1, 1);

        label_7 = new QLabel(ProviderDashboard);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 2, 1, 1, 1);

        label_8 = new QLabel(ProviderDashboard);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 3, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        label = new QLabel(ProviderDashboard);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        bookingList = new QListWidget(ProviderDashboard);
        bookingList->setObjectName("bookingList");

        verticalLayout_2->addWidget(bookingList);


        retranslateUi(ProviderDashboard);

        QMetaObject::connectSlotsByName(ProviderDashboard);
    } // setupUi

    void retranslateUi(QWidget *ProviderDashboard)
    {
        ProviderDashboard->setWindowTitle(QCoreApplication::translate("ProviderDashboard", "Form", nullptr));
        nameLabel->setText(QCoreApplication::translate("ProviderDashboard", "Name:", nullptr));
        categoryLabel->setText(QCoreApplication::translate("ProviderDashboard", "Category:", nullptr));
        priceLabel->setText(QCoreApplication::translate("ProviderDashboard", "Price:", nullptr));
        statusLabel->setText(QCoreApplication::translate("ProviderDashboard", "Status :", nullptr));
        label_5->setText(QCoreApplication::translate("ProviderDashboard", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("ProviderDashboard", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("ProviderDashboard", "TextLabel", nullptr));
        label_8->setText(QCoreApplication::translate("ProviderDashboard", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("ProviderDashboard", "Your Bookings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProviderDashboard: public Ui_ProviderDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVIDERDASHBOARD_H
