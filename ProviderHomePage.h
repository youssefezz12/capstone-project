#ifndef PROVIDERHOMEPAGE_H
#define PROVIDERHOMEPAGE_H

#include <QWidget>
#include "System.h"
#include "Provider.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProviderHomePage; }
QT_END_NAMESPACE

class ProviderHomePage : public QWidget
{
    Q_OBJECT

private:
    Ui::ProviderHomePage *ui;
    System* system;
    Provider currentProvider;

public:
    explicit ProviderHomePage(System* sys, Provider provider, QWidget *parent = nullptr);
    ~ProviderHomePage();

    void loadProviderData();
};

#endif
