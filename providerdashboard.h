#ifndef PROVIDERDASHBOARD_H
#define PROVIDERDASHBOARD_H

#include <QWidget>
#include "System.h"
#include "Provider.h"

namespace Ui {
class ProviderDashboard;
}

class ProviderDashboard : public QWidget
{
    Q_OBJECT

public:
   explicit ProviderDashboard(QWidget *parent = nullptr);
    ~ProviderDashboard();

private:
    Ui::ProviderDashboard *ui;

    System* system;
    Provider* currentProvider;

    void loadData();
};

#endif
