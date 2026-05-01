#include "providerdashboard.h"
#include "ui_providerdashboard.h"
#include <QMessageBox>
#include <QTextCharFormat>
#include <QListWidgetItem>
#include <QCheckBox>

ProviderDashboard::ProviderDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProviderDashboard)
    , system(nullptr)
    , currentProvider(nullptr)
    , providerLoaded(false)
{
    ui->setupUi(this);

    // ── Navigation ─────────────────────────────────────────────────────────
    connect(ui->navProfileBtn,      &QPushButton::clicked, [=]() { showPage(0); });
    connect(ui->navBookingsBtn,     &QPushButton::clicked, [=]() { showPage(1); });
    connect(ui->navReviewsBtn,      &QPushButton::clicked, [=]() { showPage(2); });
    connect(ui->navAvailabilityBtn, &QPushButton::clicked, [=]() { showPage(3); });
    connect(ui->navEarningsBtn,     &QPushButton::clicked, [=]() { showPage(4); });

    // ── Profile ────────────────────────────────────────────────────────────
    connect(ui->saveProfileBtn, &QPushButton::clicked,
            this, &ProviderDashboard::onSaveProfile);

    // ── Availability ───────────────────────────────────────────────────────
    connect(ui->toggleAvailabilityBtn, &QPushButton::clicked,
            this, &ProviderDashboard::onToggleAvailability);
    connect(ui->availabilityCalendar, &QCalendarWidget::clicked,
            this, &ProviderDashboard::onDateSelected);
    connect(ui->clearBlockedDatesBtn, &QPushButton::clicked,
            this, &ProviderDashboard::onClearBlockedDates);
    connect(ui->saveScheduleBtn, &QPushButton::clicked,
            this, &ProviderDashboard::onSaveSchedule);

    // ── Bookings ───────────────────────────────────────────────────────────
    connect(ui->acceptBookingBtn, &QPushButton::clicked,
            this, &ProviderDashboard::onAcceptBooking);
    connect(ui->rejectBookingBtn, &QPushButton::clicked,
            this, &ProviderDashboard::onRejectBooking);
    connect(ui->pendingBookingsList, &QListWidget::itemSelectionChanged,
            this, &ProviderDashboard::onBookingSelectionChanged);

    showPage(0);
}

ProviderDashboard::~ProviderDashboard()
{
    delete ui;
}

// ─────────────────────────────────────────────────────────────────────────────
// Entry point called by MainWindow after successful provider login
// ─────────────────────────────────────────────────────────────────────────────
void ProviderDashboard::loadForProvider(System* sys, const QString& providerName)
{
    system = sys;
    providerLoaded = false;

    // Fetch a fresh copy of this provider from the DB via System
    Provider* ptr = system->findProviderByName(providerName);
    if (!ptr) {
        QMessageBox::warning(this, "Dashboard Error",
                             "Could not load provider profile for: " + providerName);
        return;
    }

    currentProvider = ptr;   // pointer into System's cached providers vector
    providerLoaded  = true;

    loadData();
    showPage(0);
}

// ─────────────────────────────────────────────────────────────────────────────
// Navigation
// ─────────────────────────────────────────────────────────────────────────────
void ProviderDashboard::showPage(int index)
{
    ui->mainStack->setCurrentIndex(index);
    updateNavHighlight(index);
}

void ProviderDashboard::updateNavHighlight(int index)
{
    QList<QPushButton*> btns = {
        ui->navProfileBtn, ui->navBookingsBtn, ui->navReviewsBtn,
        ui->navAvailabilityBtn, ui->navEarningsBtn
    };

    const QString activeStyle =
        "QPushButton { background:#6366f1; color:white; border-radius:8px; "
        "padding:10px 16px; text-align:left; font-weight:bold; border:none; }";
    const QString inactiveStyle =
        "QPushButton { background:transparent; color:#9ca3af; border-radius:8px; "
        "padding:10px 16px; text-align:left; font-size:13px; border:none; }"
        "QPushButton:hover { background:#2d2d4e; color:#ffffff; }";

    for (int i = 0; i < btns.size(); ++i)
        btns[i]->setStyleSheet(i == index ? activeStyle : inactiveStyle);
}

// ─────────────────────────────────────────────────────────────────────────────
// Data loading
// ─────────────────────────────────────────────────────────────────────────────
void ProviderDashboard::loadData()
{
    if (!providerLoaded || !currentProvider) return;

    ui->welcomeLabel->setText(
        "Welcome back, " +
        QString::fromStdString(currentProvider->getUserName()) + " !"
        );

    loadProfilePage();
    loadBookingsPage();
    loadReviewsPage();
    loadEarningsPage();
    loadAvailabilityPage();
}

void ProviderDashboard::loadProfilePage()
{
    QString name     = QString::fromStdString(currentProvider->getUserName());
    QString category = QString::fromStdString(currentProvider->getCategory());
    double  price    = currentProvider->getPrice();
    bool    avail    = currentProvider->isAvailable();

    // Sidebar mini-card
    ui->sidebarNameLabel->setText(name);
    ui->sidebarCategoryLabel->setText(category);
    ui->profileStatusBadge->setText(avail ? "Available" : "Unavailable");
    ui->profileStatusBadge->setStyleSheet(
        avail ? "color:#4ade80;font-size:11px;font-weight:bold;"
              : "color:#f87171;font-size:11px;font-weight:bold;"
        );

    // Info card
    ui->profileNameLabel->setText(name);
    ui->profileCategoryLabel->setText(category);
    ui->profilePriceDisplay->setText(
        "$" + QString::number(price, 'f', 2) + " / hr"
        );
    ui->profileStatusBadge2->setText(avail ? "● Available" : "● Unavailable");
    ui->profileStatusBadge2->setStyleSheet(
        avail ? "color:#16a34a;font-weight:bold;font-size:13px;"
              : "color:#dc2626;font-weight:bold;font-size:13px;"
        );

    // Edit card pre-fill
    ui->priceInput->setText(QString::number(price, 'f', 2));
}

void ProviderDashboard::loadBookingsPage()
{
    if (!system) return;

    ui->pendingBookingsList->clear();
    ui->bookingHistoryList->clear();

    int pending = 0, completed = 0;
    std::string providerName = currentProvider->getUserName();

    for (const auto& b : system->getBookings()) {
        // Booking::getProvider() — assumed to return std::string matching provider name
        if (b.getProvider() != providerName) continue;

        QString user = QString::fromStdString(b.getUser());
        QString date = QString::fromStdString(b.getDate());
        QString entry = QString("%1  —  %2").arg(user, date);

        QDate bookingDate = QDate::fromString(date, "yyyy-MM-dd");
        if (bookingDate.isValid() && bookingDate < QDate::currentDate()) {
            auto* item = new QListWidgetItem(entry);
            item->setForeground(QColor("#6b7280"));
            ui->bookingHistoryList->addItem(item);
            completed++;
        } else {
            auto* item = new QListWidgetItem(entry);
            item->setBackground(QColor("#f0fdf4"));
            ui->pendingBookingsList->addItem(item);
            pending++;
        }
    }

    ui->pendingCountLabel->setText(QString::number(pending) + " pending");
    ui->historyCountLabel->setText(QString::number(completed) + " completed");
    ui->acceptBookingBtn->setEnabled(false);
    ui->rejectBookingBtn->setEnabled(false);
}

void ProviderDashboard::loadReviewsPage()
{
    ui->reviewsList->clear();

    int jobs = countCompletedJobs();
    if (jobs == 0) {
        auto* item = new QListWidgetItem(
            "No reviews yet. Complete jobs to receive reviews."
            );
        item->setForeground(QColor("#9ca3af"));
        ui->reviewsList->addItem(item);
        ui->avgRatingLabel->setText("—");
        ui->ratingBar->setValue(0);
    } else {
        // Demo reviews — replace with a Review class from DB when available
        QStringList samples = {
            "     Ahmed K. — Excellent work, very professional!",
            "     Sara M. — Good service, arrived on time.",
            "     Omar T. — Highly recommended, will hire again.",
        };
        for (const auto& r : samples)
            ui->reviewsList->addItem(r);

        ui->avgRatingLabel->setText("4.7 *");
        ui->ratingBar->setValue(94);
    }
}

void ProviderDashboard::loadEarningsPage()
{
    double total = calculateTotalEarnings();
    int    jobs  = countCompletedJobs();

    ui->totalEarningsLabel->setText("$" + QString::number(total, 'f', 2));
    ui->completedJobsLabel->setText(QString::number(jobs));
    ui->avgPerJobLabel->setText(
        jobs > 0 ? "$" + QString::number(total / jobs, 'f', 2) : "$0.00"
        );

    int progress = qMin(static_cast<int>(total / 1000.0 * 100), 100);
    ui->earningsProgressBar->setValue(progress);
    ui->earningsGoalLabel->setText(
        QString("$%1 / $1,000 monthly goal").arg(total, 0, 'f', 2)
        );
}

void ProviderDashboard::loadAvailabilityPage()
{
    bool avail = currentProvider->isAvailable();

    ui->availabilityStatusLabel->setText(
        avail ? "Status: Available" : "Status: Unavailable"
        );
    ui->availabilityStatusLabel->setStyleSheet(
        avail ? "font-size:15px;font-weight:bold;color:#16a34a;"
              : "font-size:15px;font-weight:bold;color:#dc2626;"
        );
    ui->toggleAvailabilityBtn->setText(
        avail ? "Set as Unavailable" : "Set as Available"
        );

    refreshCalendarHighlights();
}

// ─────────────────────────────────────────────────────────────────────────────
// Slots
// ─────────────────────────────────────────────────────────────────────────────

void ProviderDashboard::onSaveProfile()
{
    double newPrice = ui->priceInput->text().toDouble();
    if (newPrice <= 0) {
        QMessageBox::warning(this, "Invalid Price",
                             "Please enter a valid price greater than 0.");
        return;
    }

    // Rebuild via pointer dereference (Provider has no setPrice setter)
    *currentProvider = Provider(
        currentProvider->getUserName(),
        "pass",
        currentProvider->getCategory(),
        newPrice
        );

    // TODO: persist via system->updateProvider(*currentProvider) when DB supports it

    loadProfilePage();
    QMessageBox::information(this, "Profile Updated",
                             "Your profile has been saved successfully.");
}

void ProviderDashboard::onToggleAvailability()
{
    // Provider has no setAvailable() yet, so we track UI state via the label.
    // When DB supports it, call system->setProviderAvailability(...) here.
    bool currentlyAvailable =
        (ui->availabilityStatusLabel->text() == "Status: Available");

    // Temporarily reflect the toggle in our local copy via a workaround.
    // Since Provider constructor always sets available=true, we use the UI
    // state as the source of truth until a proper setter is added.
    if (currentlyAvailable) {
        ui->availabilityStatusLabel->setText("Status: Unavailable");
        ui->availabilityStatusLabel->setStyleSheet(
            "font-size:15px;font-weight:bold;color:#dc2626;");
        ui->toggleAvailabilityBtn->setText("Set as Available");
        ui->profileStatusBadge->setText("Unavailable");
        ui->profileStatusBadge->setStyleSheet(
            "color:#f87171;font-size:11px;font-weight:bold;");
        ui->profileStatusBadge2->setText("● Unavailable");
        ui->profileStatusBadge2->setStyleSheet(
            "color:#dc2626;font-weight:bold;font-size:13px;");
    } else {
        ui->availabilityStatusLabel->setText("Status: Available");
        ui->availabilityStatusLabel->setStyleSheet(
            "font-size:15px;font-weight:bold;color:#16a34a;");
        ui->toggleAvailabilityBtn->setText("Set as Unavailable");
        ui->profileStatusBadge->setText("Available");
        ui->profileStatusBadge->setStyleSheet(
            "color:#4ade80;font-size:11px;font-weight:bold;");
        ui->profileStatusBadge2->setText("● Available");
        ui->profileStatusBadge2->setStyleSheet(
            "color:#16a34a;font-weight:bold;font-size:13px;");
    }
}

void ProviderDashboard::onDateSelected(const QDate& date)
{
    if (date < QDate::currentDate()) return;

    if (blockedDates.contains(date))
        blockedDates.remove(date);
    else
        blockedDates.insert(date);

    refreshCalendarHighlights();
    ui->blockedDatesCountLabel->setText(
        QString("%1 date(s) blocked").arg(blockedDates.size())
        );
}

void ProviderDashboard::onClearBlockedDates()
{
    blockedDates.clear();
    refreshCalendarHighlights();
    ui->blockedDatesCountLabel->setText("0 date(s) blocked");
}

void ProviderDashboard::refreshCalendarHighlights()
{
    QCalendarWidget* cal = ui->availabilityCalendar;
    QTextCharFormat  defaultFmt = cal->dateTextFormat(QDate());

    for (int i = 0; i < 90; i++)
        cal->setDateTextFormat(QDate::currentDate().addDays(i), defaultFmt);

    QTextCharFormat blockedFmt;
    blockedFmt.setBackground(QColor("#fee2e2"));
    blockedFmt.setForeground(QColor("#dc2626"));
    for (const QDate& d : blockedDates)
        cal->setDateTextFormat(d, blockedFmt);
}

void ProviderDashboard::onAcceptBooking()
{
    auto selected = ui->pendingBookingsList->selectedItems();
    if (selected.isEmpty()) return;

    QListWidgetItem* item = selected.first();
    item->setText(item->text() + "  [Accepted]");
    item->setBackground(QColor("#dcfce7"));
    item->setForeground(QColor("#166534"));
    ui->acceptBookingBtn->setEnabled(false);
    ui->rejectBookingBtn->setEnabled(false);

    // TODO: notify server via socket when booking accept/reject command is added
}

void ProviderDashboard::onRejectBooking()
{
    auto selected = ui->pendingBookingsList->selectedItems();
    if (selected.isEmpty()) return;

    int ret = QMessageBox::question(this, "Reject Booking",
                                    "Are you sure you want to reject this booking?",
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes)
        delete selected.first();
}

void ProviderDashboard::onBookingSelectionChanged()
{
    bool has = !ui->pendingBookingsList->selectedItems().isEmpty();
    ui->acceptBookingBtn->setEnabled(has);
    ui->rejectBookingBtn->setEnabled(has);
}

void ProviderDashboard::onSaveSchedule()
{
    QList<QCheckBox*> boxes = {
        ui->monCheck, ui->tueCheck, ui->wedCheck, ui->thuCheck,
        ui->friCheck, ui->satCheck, ui->sunCheck
    };
    QStringList names = {
        "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"
    };

    QStringList active;
    for (int i = 0; i < boxes.size(); i++)
        if (boxes[i]->isChecked()) active << names[i];

    if (active.isEmpty()) {
        QMessageBox::warning(this, "Schedule",
                             "Please select at least one working day.");
        return;
    }

    QMessageBox::information(this, "Schedule Saved",
                             "Working days saved: " + active.join(", "));

    // TODO: persist schedule via server command when supported
}

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────

double ProviderDashboard::calculateTotalEarnings()
{
    if (!system || !providerLoaded || !currentProvider) return 0.0;
    return countCompletedJobs() * currentProvider->getPrice();
}

int ProviderDashboard::countCompletedJobs()
{
    if (!system || !providerLoaded || !currentProvider) return 0;

    int count = 0;
    std::string name = currentProvider->getUserName();
    for (const auto& b : system->getBookings()) {
        if (b.getProvider() != name) continue;
        QDate d = QDate::fromString(
            QString::fromStdString(b.getDate()), "yyyy-MM-dd"
            );
        if (d.isValid() && d < QDate::currentDate()) count++;
    }
    return count;
}
