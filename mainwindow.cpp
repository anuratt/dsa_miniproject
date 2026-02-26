#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QHeaderView>
#include <QColor>
#include <QDate>
#include <QComboBox>
#include <QSpinBox>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      hospital("City General Hospital")
{
    ui->setupUi(this);

    
    hospital.loadSampleData();

    setupUI();
    setupTableHeaders();
    applyStyleSheet();

    
    clockTimer = new QTimer(this);
    connect(clockTimer, &QTimer::timeout, this, &MainWindow::updateClock);
    clockTimer->start(1000);

    
    refreshDashboard();
    refreshQueueTable();
    refreshPatientTable();
    refreshDoctorTable();

    setWindowTitle("Hospital Management System — " + hospital.getName());
}

MainWindow::~MainWindow() {
    delete ui;
}





void MainWindow::setupUI() {
    
    setMinimumSize(1100, 700);
    resize(1200, 780);

    
    ui->tabWidget->setTabText(0, "📊  Dashboard");
    ui->tabWidget->setTabText(1, "🚑  Triage Queue");
    ui->tabWidget->setTabText(2, "🏥  Patients");
    ui->tabWidget->setTabText(3, "👨‍⚕️  Doctors");
}

void MainWindow::setupTableHeaders() {
    
    ui->queueTable->setColumnCount(6);
    ui->queueTable->setHorizontalHeaderLabels(
        {"Priority", "ID", "Name", "Age", "Disease", "Assigned Doctor"});
    ui->queueTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->queueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->queueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->queueTable->setAlternatingRowColors(true);

    
    ui->patientTable->setColumnCount(8);
    ui->patientTable->setHorizontalHeaderLabels(
        {"ID", "Name", "Age", "Gender", "Disease", "Doctor", "Severity", "Status"});
    ui->patientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->patientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->patientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->patientTable->setAlternatingRowColors(true);

    
    ui->doctorTable->setColumnCount(5);
    ui->doctorTable->setHorizontalHeaderLabels(
        {"ID", "Name", "Specialization", "Contact", "Patients Assigned"});
    ui->doctorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->doctorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->doctorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->doctorTable->setAlternatingRowColors(true);

    
    ui->historyTable->setColumnCount(4);
    ui->historyTable->setHorizontalHeaderLabels(
        {"Action", "Patient ID", "Patient Name", "Timestamp"});
    ui->historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->historyTable->setAlternatingRowColors(true);
}


void MainWindow::applyStyleSheet() {
    setStyleSheet(R"(
        QMainWindow { background-color: #F0F4F8; }
        QTabWidget::pane { border: none; background: #F0F4F8; }
        QTabBar::tab {
            background: #CBD5E0; color: #2D3748;
            padding: 10px 22px; border-radius: 6px 6px 0 0;
            font-size: 13px; font-weight: bold;
            margin-right: 2px;
        }
        QTabBar::tab:selected { background: #2B6CB0; color: white; }
        QTabBar::tab:hover:!selected { background: #90CDF4; }

        QGroupBox {
            font-weight: bold; font-size: 13px;
            color: #2D3748; border: 1.5px solid #BEE3F8;
            border-radius: 8px; margin-top: 12px;
            background: white; padding: 12px;
        }
        QGroupBox::title {
            subcontrol-origin: margin; left: 12px;
            padding: 0 6px; color: #2B6CB0;
        }

        QTableWidget {
            border: 1px solid #BEE3F8; border-radius: 6px;
            gridline-color: #EBF8FF; font-size: 12px;
            alternate-background-color: #EBF8FF;
            selection-background-color: #2B6CB0;
            selection-color: white;
        }
        QTableWidget::item { padding: 6px; }
        QHeaderView::section {
            background-color: #2B6CB0; color: white;
            font-weight: bold; font-size: 12px;
            padding: 8px; border: none;
        }

        QPushButton {
            background-color: #2B6CB0; color: white;
            border: none; border-radius: 6px;
            padding: 8px 18px; font-size: 12px; font-weight: bold;
        }
        QPushButton:hover   { background-color: #2C5282; }
        QPushButton:pressed { background-color: #1A365D; }
        QPushButton#btnDischarge, QPushButton#btnRemoveDoctor {
            background-color: #C53030;
        }
        QPushButton#btnDischarge:hover, QPushButton#btnRemoveDoctor:hover {
            background-color: #9B2C2C;
        }
        QPushButton#btnAdmitNext {
            background-color: #276749;
        }
        QPushButton#btnAdmitNext:hover { background-color: #22543D; }

        QLineEdit, QComboBox, QSpinBox, QDateEdit {
            border: 1.5px solid #90CDF4; border-radius: 5px;
            padding: 6px 10px; font-size: 12px;
            background: white; color: #2D3748;
        }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus {
            border-color: #2B6CB0;
        }
        QLabel { color: #2D3748; }
        QLabel#lblHospitalName { font-size: 20px; font-weight: bold; color: #2B6CB0; }
        QLabel#lblClock { font-size: 14px; color: #4A5568; }
        QStatusBar { background: #EBF8FF; color: #2D3748; font-size: 11px; }
    )");
}





void MainWindow::refreshDashboard() {
    HospitalStats s = hospital.getStats();

    
    ui->lblTotalPatients->setText(QString::number(s.totalPatients));
    ui->lblAdmitted->setText(QString::number(s.admittedPatients));
    ui->lblDischarged->setText(QString::number(s.dischargedPatients));
    ui->lblInQueue->setText(QString::number(s.patientsInQueue));
    ui->lblDoctors->setText(QString::number(s.totalDoctors));
    ui->lblCritical->setText(QString::number(s.criticalCases));
    ui->lblHospitalName->setText("🏥  " + hospital.getName());
}

void MainWindow::updateClock() {
    ui->lblClock->setText(QDateTime::currentDateTime().toString("ddd dd MMM yyyy   hh:mm:ss"));
    
    static int tick = 0;
    if (++tick % 60 == 0) refreshDashboard();
}





void MainWindow::on_btnAddToQueue_clicked() {
    
    QString name    = ui->queueName->text().trimmed();
    int     age     = ui->queueAge->value();
    QString gender  = ui->queueGender->currentText();
    QString disease = ui->queueDisease->text().trimmed();
    QString doctor  = ui->queueDoctor->currentText();
    int     sevInt  = ui->queueSeverity->currentIndex() + 1;  
    Severity sev    = intToSeverity(sevInt);

    if (name.isEmpty() || disease.isEmpty()) {
        showStatusMessage("Please fill in patient name and disease.", true);
        return;
    }

    int id = hospital.addToTriage(name, age, gender, disease, doctor, sev);
    showStatusMessage(QString("Patient '%1' (ID: %2) added to triage queue.").arg(name).arg(id));

    
    ui->queueName->clear();
    ui->queueDisease->clear();
    ui->queueAge->setValue(1);

    refreshQueueTable();
    refreshDashboard();
}

void MainWindow::on_btnAdmitNext_clicked() {
    if (hospital.queueSize() == 0) {
        showStatusMessage("Triage queue is empty — no patients to admit.", true);
        return;
    }

    
    Patient next = hospital.getQueue().peek();
    bool ok = hospital.admitNextPatient();

    if (ok) {
        showStatusMessage(QString("Patient '%1' (ID: %2) admitted successfully.")
                          .arg(next.name).arg(next.id));
        refreshQueueTable();
        refreshPatientTable();
        refreshDoctorTable();
        refreshDashboard();
    }
}

void MainWindow::on_btnClearQueue_clicked() {
    if (hospital.queueSize() == 0) { showStatusMessage("Queue is already empty."); return; }

    auto reply = QMessageBox::question(this, "Clear Queue",
        "Are you sure you want to clear all patients from the triage queue?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        hospital.getQueue().clear();
        refreshQueueTable();
        refreshDashboard();
        showStatusMessage("Triage queue cleared.");
    }
}

void MainWindow::refreshQueueTable() {
    QVector<Patient> snap = hospital.getQueueSnapshot();
    ui->queueTable->setRowCount(0);

    for (int i = 0; i < snap.size(); ++i) {
        const Patient& p = snap[i];
        ui->queueTable->insertRow(i);

        
        auto* priItem = new QTableWidgetItem(
            QString("#%1  %2").arg(i + 1).arg(severityBadge(p.severity)));
        priItem->setBackground(severityColor(p.severity));
        priItem->setForeground(Qt::white);
        priItem->setFont(QFont("Arial", 10, QFont::Bold));
        ui->queueTable->setItem(i, 0, priItem);

        ui->queueTable->setItem(i, 1, new QTableWidgetItem(QString::number(p.id)));
        ui->queueTable->setItem(i, 2, new QTableWidgetItem(p.name));
        ui->queueTable->setItem(i, 3, new QTableWidgetItem(QString::number(p.age)));
        ui->queueTable->setItem(i, 4, new QTableWidgetItem(p.disease));
        ui->queueTable->setItem(i, 5, new QTableWidgetItem(p.doctor));
    }

    ui->lblQueueCount->setText(
        QString("Patients in queue: <b>%1</b>").arg(snap.size()));
}





void MainWindow::on_btnDischarge_clicked() {
    int row = ui->patientTable->currentRow();
    if (row < 0) { showStatusMessage("Select a patient row first.", true); return; }

    int id = ui->patientTable->item(row, 0)->text().toInt();
    Patient* p = hospital.findPatient(id);
    if (!p) { showStatusMessage("Patient not found.", true); return; }
    if (!p->admitted) { showStatusMessage("Patient is already discharged.", true); return; }

    bool ok = hospital.dischargePatient(id);
    if (ok) {
        showStatusMessage(QString("Patient '%1' (ID: %2) discharged.").arg(p->name).arg(id));
        refreshPatientTable();
        refreshDoctorTable();
        refreshDashboard();
    }
}

void MainWindow::on_btnSearchPatient_clicked() {
    QString query = ui->searchBar->text().trimmed();
    if (query.isEmpty()) { refreshPatientTable(); return; }

    QVector<Patient> results = hospital.searchByName(query);
    populateTable(ui->patientTable, results);
    showStatusMessage(QString("Found %1 patient(s) matching '%2'.").arg(results.size()).arg(query));
}

void MainWindow::on_btnClearSearch_clicked() {
    ui->searchBar->clear();
    refreshPatientTable();
}

void MainWindow::on_patientTable_itemSelectionChanged() {
    int row = ui->patientTable->currentRow();
    if (row < 0) return;

    
    auto get = [&](int col) { return ui->patientTable->item(row, col)->text(); };
    ui->lblSelectedPatient->setText(
        QString("<b>%1</b> | ID: %2 | %3 | %4 | Doctor: %5")
        .arg(get(1)).arg(get(0)).arg(get(3)).arg(get(4)).arg(get(5)));
}

void MainWindow::refreshPatientTable() {
    QVector<Patient> all = hospital.getAllPatients();
    populateTable(ui->patientTable, all);
    ui->lblPatientCount->setText(
        QString("Total records: <b>%1</b>").arg(all.size()));
}

void MainWindow::populateTable(QTableWidget* table, const QVector<Patient>& patients) {
    table->setRowCount(0);

    for (int i = 0; i < patients.size(); ++i) {
        const Patient& p = patients[i];
        table->insertRow(i);

        table->setItem(i, 0, new QTableWidgetItem(QString::number(p.id)));
        table->setItem(i, 1, new QTableWidgetItem(p.name));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(p.age)));
        table->setItem(i, 3, new QTableWidgetItem(p.gender));
        table->setItem(i, 4, new QTableWidgetItem(p.disease));
        table->setItem(i, 5, new QTableWidgetItem(p.doctor));

        
        auto* sevItem = new QTableWidgetItem(severityBadge(p.severity));
        sevItem->setBackground(severityColor(p.severity));
        sevItem->setForeground(Qt::white);
        sevItem->setFont(QFont("Arial", 10, QFont::Bold));
        table->setItem(i, 6, sevItem);

        
        QString statusText = p.admitted ? "Admitted" : "Discharged";
        auto* statusItem   = new QTableWidgetItem(statusText);
        statusItem->setForeground(p.admitted ? QColor("#276749") : QColor("#C53030"));
        statusItem->setFont(QFont("Arial", 10, QFont::Bold));
        table->setItem(i, 7, statusItem);
    }
}





void MainWindow::on_btnAddDoctor_clicked() {
    QString name  = ui->doctorName->text().trimmed();
    QString spec  = ui->doctorSpec->text().trimmed();
    QString phone = ui->doctorPhone->text().trimmed();

    if (name.isEmpty() || spec.isEmpty()) {
        showStatusMessage("Doctor name and specialization are required.", true); return;
    }

    int id = hospital.addDoctor(name, spec, phone);
    showStatusMessage(QString("Doctor '%1' (ID: %2) added.").arg(name).arg(id));

    ui->doctorName->clear();
    ui->doctorSpec->clear();
    ui->doctorPhone->clear();

    refreshDoctorTable();
    refreshDashboard();

    
    ui->queueDoctor->clear();
    for (const Doctor& d : hospital.getDoctors())
        ui->queueDoctor->addItem(d.name);
}

void MainWindow::on_btnRemoveDoctor_clicked() {
    int row = ui->doctorTable->currentRow();
    if (row < 0) { showStatusMessage("Select a doctor row first.", true); return; }

    int id = ui->doctorTable->item(row, 0)->text().toInt();
    Doctor* d = hospital.findDoctor(id);
    if (!d) return;

    auto reply = QMessageBox::question(this, "Remove Doctor",
        QString("Remove Dr. %1 from the system?").arg(d->name),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        hospital.removeDoctor(id);
        refreshDoctorTable();
        refreshDashboard();
        showStatusMessage("Doctor removed.");
    }
}

void MainWindow::on_doctorTable_itemSelectionChanged() {
    refreshDoctorHistory();
}

void MainWindow::refreshDoctorTable() {
    const QVector<Doctor>& docs = hospital.getDoctors();
    ui->doctorTable->setRowCount(0);

    for (int i = 0; i < docs.size(); ++i) {
        const Doctor& d = docs[i];
        ui->doctorTable->insertRow(i);
        ui->doctorTable->setItem(i, 0, new QTableWidgetItem(QString::number(d.id)));
        ui->doctorTable->setItem(i, 1, new QTableWidgetItem(d.name));
        ui->doctorTable->setItem(i, 2, new QTableWidgetItem(d.specialization));
        ui->doctorTable->setItem(i, 3, new QTableWidgetItem(d.contact));
        ui->doctorTable->setItem(i, 4, new QTableWidgetItem(QString::number(d.patientsAssigned)));
    }
}


void MainWindow::refreshDoctorHistory() {
    int row = ui->doctorTable->currentRow();
    ui->historyTable->setRowCount(0);
    if (row < 0) return;

    int id = ui->doctorTable->item(row, 0)->text().toInt();
    Doctor* d = hospital.findDoctor(id);
    if (!d) return;

    QVector<DoctorAction> history = d->actionHistory.getHistory();
    for (int i = 0; i < history.size(); ++i) {
        const DoctorAction& a = history[i];
        ui->historyTable->insertRow(i);
        ui->historyTable->setItem(i, 0, new QTableWidgetItem(a.actionType));
        ui->historyTable->setItem(i, 1, new QTableWidgetItem(QString::number(a.patientId)));
        ui->historyTable->setItem(i, 2, new QTableWidgetItem(a.patientName));
        ui->historyTable->setItem(i, 3, new QTableWidgetItem(a.timestamp));
    }

    ui->lblDoctorHistory->setText(
        QString("Action history for <b>%1</b> (most recent first — Stack LIFO):")
        .arg(d->name));
}





void MainWindow::showStatusMessage(const QString& msg, bool isError) {
    statusBar()->setStyleSheet(
        isError ? "color: #C53030; font-weight: bold;"
                : "color: #276749; font-weight: bold;");
    statusBar()->showMessage((isError ? "⚠  " : "✓  ") + msg, 4000);
}

QString MainWindow::severityBadge(Severity s) {
    switch (s) {
        case Severity::Critical: return "🔴 CRITICAL";
        case Severity::High:     return "🟠 HIGH";
        case Severity::Medium:   return "🟡 MEDIUM";
        case Severity::Low:      return "🟢 LOW";
        default:                 return "UNKNOWN";
    }
}

QColor MainWindow::severityColor(Severity s) {
    switch (s) {
        case Severity::Critical: return QColor("#C53030");
        case Severity::High:     return QColor("#C05621");
        case Severity::Medium:   return QColor("#B7791F");
        case Severity::Low:      return QColor("#276749");
        default:                 return QColor("#4A5568");
    }
}

void MainWindow::on_btnAdmitPatient_clicked() {
    
    on_btnAdmitNext_clicked();
}
