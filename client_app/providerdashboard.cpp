#include "providerdashboard.h"
#include "ui_providerdashboard.h"
#include <QMessageBox>
#include <QTextCharFormat>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QJsonObject>

ProviderDashboard::ProviderDashboard(QWidget* parent)
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
    delete currentProvider;
    delete ui;
}

// ─────────────────────────────────────────────────────────────────────────────
// Public entry points called by MainWindow
// ─────────────────────────────────────────────────────────────────────────────

// Called when the server returns a getProviderByName success response.
// MainWindow builds the Provider from JSON and passes it here — no DB access.
void ProviderDashboard::loadFromProvider(const Provider& p, System* sys)
{
    system = sys;
    delete currentProvider;
    currentProvider = new Provider(p);   // owned heap copy
    providerLoaded  = true;

    loadProfilePage();
    loadReviewsPage();
    loadEarningsPage();
    loadAvailabilityPage();

    // Clear booking lists — they will be populated by loadBookingsFromJson
    // once the separate getBookings response arrives.
    ui->pendingBookingsList->clear();
    ui->bookingHistoryList->clear();
    ui->pendingCountLabel->setText("loading...");
    ui->historyCountLabel->setText("loading...");

    ui->welcomeLabel->setText(
        "Welcome back, " +
        QString::fromStdString(currentProvider->getUserName()) + " !"
        );

    showPage(0);
}

// Called when the server returns a getBookings success response.
// Populates pending and history lists from the JSON array.
void ProviderDashboard::loadBookingsFromJson(const QJsonArray& bookings)
{
    ui->pendingBookingsList->clear();
    ui->bookingHistoryList->clear();

    int pending = 0, completed = 0;

    for (const auto& val : bookings)
    {
        QJsonObject obj  = val.toObject();
        QString user     = obj["user"].toString();
        QString date     = obj["date"].toString();
        QString entry    = QString("%1  —  %2").arg(user, date);

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

    // Refresh earnings now that we know how many completed jobs there are
    loadEarningsPage();
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
    const QString active =
        "QPushButton { background:#6366f1; color:white; border-radius:8px; "
        "padding:10px 16px; text-align:left; font-weight:bold; border:none; }";
    const QString inactive =
        "QPushButton { background:transparent; color:#9ca3af; border-radius:8px; "
        "padding:10px 16px; text-align:left; font-size:13px; border:none; }"
        "QPushButton:hover { background:#2d2d4e; color:#ffffff; }";
    for (int i = 0; i < btns.size(); ++i)
        btns[i]->setStyleSheet(i == index ? active : inactive);
}

// ─────────────────────────────────────────────────────────────────────────────
// Page loaders
// ─────────────────────────────────────────────────────────────────────────────

void ProviderDashboard::loadProfilePage()
{
    if (!providerLoaded || !currentProvider) return;

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
    ui->profilePriceDisplay->setText("$" + QString::number(price, 'f', 2) + " / hr");
    ui->profileStatusBadge2->setText(avail ? "Available" : "Unavailable");
    ui->profileStatusBadge2->setStyleSheet(
        avail ? "color:#16a34a;font-weight:bold;font-size:13px;"
              : "color:#dc2626;font-weight:bold;font-size:13px;"
        );

    // Pre-fill editable fields
    ui->priceInput->setText(QString::number(price, 'f', 2));
}

void ProviderDashboard::loadReviewsPage()
{
    ui->reviewsList->clear();
    // Placeholder until a Reviews table + server command is added.
    auto* item = new QListWidgetItem("No reviews yet. Complete jobs to receive reviews.");
    item->setForeground(QColor("#9ca3af"));
    ui->reviewsList->addItem(item);
    ui->avgRatingLabel->setText("—");
    ui->ratingBar->setValue(0);
}

void ProviderDashboard::loadEarningsPage()
{
    if (!providerLoaded || !currentProvider) return;

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
    if (!providerLoaded || !currentProvider) return;

    bool avail = currentProvider->isAvailable();
    ui->availabilityStatusLabel->setText(avail ? "Status: Available" : "Status: Unavailable");
    ui->availabilityStatusLabel->setStyleSheet(
        avail ? "font-size:15px;font-weight:bold;color:#16a34a;"
              : "font-size:15px;font-weight:bold;color:#dc2626;"
        );
    ui->toggleAvailabilityBtn->setText(avail ? "Set as Unavailable" : "Set as Available");
    refreshCalendarHighlights();
}

// ─────────────────────────────────────────────────────────────────────────────
// Slots
// ─────────────────────────────────────────────────────────────────────────────

void ProviderDashboard::onSaveProfile()
{
    if (!providerLoaded || !currentProvider) return;

    double newPrice = ui->priceInput->text().toDouble();
    if (newPrice <= 0) {
        QMessageBox::warning(this, "Invalid Price",
                             "Please enter a valid price greater than 0.");
        return;
    }

    *currentProvider = Provider(
        currentProvider->getUserName(),
        currentProvider->getPassword(),
        currentProvider->getCategory(),
        newPrice
        );

    // Notify MainWindow so it can send updateProvider to the server
    emit profileUpdated(*currentProvider);

    loadProfilePage();
    QMessageBox::information(this, "Profile Updated",
                             "Your profile has been saved successfully.");
}

void ProviderDashboard::onToggleAvailability()
{
    // Toggle via UI state until Provider gains a setAvailable() setter
    bool currentlyAvailable =
        ui->availabilityStatusLabel->text().contains("Available") &&
        !ui->availabilityStatusLabel->text().contains("Unavailable");

    if (currentlyAvailable) {
        ui->availabilityStatusLabel->setText("Status: Unavailable");
        ui->availabilityStatusLabel->setStyleSheet("font-size:15px;font-weight:bold;color:#dc2626;");
        ui->toggleAvailabilityBtn->setText("Set as Available");
        ui->profileStatusBadge->setText("Unavailable");
        ui->profileStatusBadge->setStyleSheet("color:#f87171;font-size:11px;font-weight:bold;");
        ui->profileStatusBadge2->setText("Unavailable");
        ui->profileStatusBadge2->setStyleSheet("color:#dc2626;font-weight:bold;font-size:13px;");
    } else {
        ui->availabilityStatusLabel->setText("Status: Available");
        ui->availabilityStatusLabel->setStyleSheet("font-size:15px;font-weight:bold;color:#16a34a;");
        ui->toggleAvailabilityBtn->setText("Set as Unavailable");
        ui->profileStatusBadge->setText("Available");
        ui->profileStatusBadge->setStyleSheet("color:#4ade80;font-size:11px;font-weight:bold;");
        ui->profileStatusBadge2->setText("Available");
        ui->profileStatusBadge2->setStyleSheet("color:#16a34a;font-weight:bold;font-size:13px;");
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
    QTextCharFormat  def = cal->dateTextFormat(QDate());
    for (int i = 0; i < 90; i++)
        cal->setDateTextFormat(QDate::currentDate().addDays(i), def);

    QTextCharFormat blocked;
    blocked.setBackground(QColor("#fee2e2"));
    blocked.setForeground(QColor("#dc2626"));
    for (const QDate& d : blockedDates)
        cal->setDateTextFormat(d, blocked);
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
}

void ProviderDashboard::onRejectBooking()
{
    auto selected = ui->pendingBookingsList->selectedItems();
    if (selected.isEmpty()) return;
    if (QMessageBox::question(this, "Reject Booking",
                              "Are you sure you want to reject this booking?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
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
        QMessageBox::warning(this, "Schedule", "Please select at least one working day.");
        return;
    }
    QMessageBox::information(this, "Schedule Saved",
                             "Working days saved: " + active.join(", "));
}

// ─────────────────────────────────────────────────────────────────────────────
// Helpers — use the booking list widget as source of truth (populated from JSON)
// ─────────────────────────────────────────────────────────────────────────────

int ProviderDashboard::countCompletedJobs()
{
    return ui->bookingHistoryList->count();
}

double ProviderDashboard::calculateTotalEarnings()
{
    if (!providerLoaded || !currentProvider) return 0.0;
    return countCompletedJobs() * currentProvider->getPrice();
}
