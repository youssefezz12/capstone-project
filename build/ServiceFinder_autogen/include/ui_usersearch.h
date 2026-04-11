/********************************************************************************
** Form generated from reading UI file 'usersearch.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSEARCH_H
#define UI_USERSEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserSearch
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *welcome_label;
    QHBoxLayout *horizontalLayout;
    QPushButton *search_button;
    QLineEdit *categoryLineEdit;
    QTableWidget *searchTable;

    void setupUi(QDialog *UserSearch)
    {
        if (UserSearch->objectName().isEmpty())
            UserSearch->setObjectName("UserSearch");
        UserSearch->resize(1023, 525);
        verticalLayout = new QVBoxLayout(UserSearch);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(UserSearch);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        welcome_label = new QLabel(widget);
        welcome_label->setObjectName("welcome_label");

        verticalLayout_2->addWidget(welcome_label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        search_button = new QPushButton(widget);
        search_button->setObjectName("search_button");

        horizontalLayout->addWidget(search_button);

        categoryLineEdit = new QLineEdit(widget);
        categoryLineEdit->setObjectName("categoryLineEdit");

        horizontalLayout->addWidget(categoryLineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        searchTable = new QTableWidget(widget);
        if (searchTable->columnCount() < 3)
            searchTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        searchTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        searchTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        searchTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        searchTable->setObjectName("searchTable");

        verticalLayout_2->addWidget(searchTable);


        verticalLayout->addWidget(widget);


        retranslateUi(UserSearch);

        QMetaObject::connectSlotsByName(UserSearch);
    } // setupUi

    void retranslateUi(QDialog *UserSearch)
    {
        UserSearch->setWindowTitle(QCoreApplication::translate("UserSearch", "Dialog", nullptr));
        welcome_label->setText(QCoreApplication::translate("UserSearch", "Welcome back!", nullptr));
        search_button->setText(QCoreApplication::translate("UserSearch", "Search", nullptr));
        categoryLineEdit->setText(QCoreApplication::translate("UserSearch", "What service do you need?", nullptr));
        QTableWidgetItem *___qtablewidgetitem = searchTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserSearch", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = searchTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserSearch", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = searchTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserSearch", "Rating", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserSearch: public Ui_UserSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSEARCH_H
