#ifndef PROVIDERDASHBOARD_H
#define PROVIDERDASHBOARD_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QProgressBar>
#include <QFrame>
#include <QSet>
#include <QDate>
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

    // Called by MainWindow::showProviderDashboard() after successful login.
    // Fetches the matching Provider from the DB via System and loads all pages.
    void loadForProvider(System* sys, const QString& providerName);

private slots:
    void showPage(int index);

    void onSaveProfile();

    void onToggleAvailability();
    void onDateSelected(const QDate& date);
    void onClearBlockedDates();

    void onAcceptBooking();
    void onRejectBooking();
    void onBookingSelectionChanged();

    void onSaveSchedule();

private:
    Ui::ProviderDashboard* ui;
    System*   system;

    // Pointer to provider fetched from DB — refreshed on each login
    Provider* currentProvider;
    bool      providerLoaded;

    QSet<QDate> blockedDates;

    // Page loaders
    void loadData();
    void loadProfilePage();
    void loadBookingsPage();
    void loadReviewsPage();
    void loadEarningsPage();
    void loadAvailabilityPage();

    // Helpers
    void    updateNavHighlight(int index);
    void    refreshCalendarHighlights();
    double  calculateTotalEarnings();
    int     countCompletedJobs();
};

#endif // PROVIDERDASHBOARD_H
