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
#include <QSet>
#include <QDate>
#include <QJsonArray>
#include "System.h"
#include "Provider.h"

namespace Ui { class ProviderDashboard; }

class ProviderDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit ProviderDashboard(QWidget* parent = nullptr);
    ~ProviderDashboard();

    // Called by MainWindow after getProviderByName response arrives.
    // p is built from the server JSON — no direct DB access needed.
    void loadFromProvider(const Provider& p, System* sys);

    // Called by MainWindow after getBookings response arrives.
    void loadBookingsFromJson(const QJsonArray& bookings);

signals:
    // Emitted when the provider saves a new price — MainWindow should
    // send an updateProvider command to the server (future work).
    void profileUpdated(const Provider& updatedProvider);

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
    Provider* currentProvider;   // pointer — no default constructor needed
    bool      providerLoaded;

    QSet<QDate> blockedDates;

    void loadProfilePage();
    void loadReviewsPage();
    void loadEarningsPage();
    void loadAvailabilityPage();

    void   updateNavHighlight(int index);
    void   refreshCalendarHighlights();
    double calculateTotalEarnings();
    int    countCompletedJobs();
};

#endif // PROVIDERDASHBOARD_H
