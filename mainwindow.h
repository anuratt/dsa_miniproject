#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QTimer>
#include "hospital.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    
    void refreshDashboard();

    
    void on_btnAddToQueue_clicked();
    void on_btnAdmitNext_clicked();
    void on_btnClearQueue_clicked();
    void refreshQueueTable();

    
    void on_btnAdmitPatient_clicked();
    void on_btnDischarge_clicked();
    void on_btnSearchPatient_clicked();
    void on_btnClearSearch_clicked();
    void on_patientTable_itemSelectionChanged();
    void refreshPatientTable();

    
    void on_btnAddDoctor_clicked();
    void on_btnRemoveDoctor_clicked();
    void on_doctorTable_itemSelectionChanged();
    void refreshDoctorTable();
    void refreshDoctorHistory();

    
    void updateClock();

private:
    Ui::MainWindow* ui;
    Hospital        hospital;   
    QTimer*         clockTimer;

    
    void setupUI();
    void setupTableHeaders();
    void applyStyleSheet();
    void populateTable(QTableWidget* table, const QVector<Patient>& patients);
    void showStatusMessage(const QString& msg, bool isError = false);
    QString severityBadge(Severity s);

    
    QColor severityColor(Severity s);
};

#endif 
