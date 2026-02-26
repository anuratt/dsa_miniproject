
#include "hospital.h"
#include <QDate>

Hospital::Hospital(const QString& name)
    : hospitalName(name), nextPatientId(1001), nextDoctorId(1) {}


int Hospital::addToTriage(const QString& name, int age, const QString& gender,
                          const QString& disease, const QString& doctorName,
                          Severity severity)
{
    int id = nextPatientId++;

    Patient p(id, name, age, gender, disease, doctorName, severity,
              QDate::currentDate().toString("yyyy-MM-dd"));
    p.admitted = false;   

    triageQueue.enqueue(p);   
    return id;
}

bool Hospital::admitNextPatient() {
    if (triageQueue.isEmpty()) return false;

    Patient p = triageQueue.dequeue();   
    p.admitted = true;

    records.addPatient(p);   

    
    Doctor* doc = findDoctorByName(p.doctor);
    if (doc) {
        doc->patientsAssigned++;
        doc->logAction("Admitted", p.id, p.name);
    }
    return true;
}

bool Hospital::dischargePatient(int id) {
    Patient* p = records.findById(id);
    if (!p || !p->admitted) return false;

    p->admitted = false;   

    
    Doctor* doc = findDoctorByName(p->doctor);
    if (doc) {
        if (doc->patientsAssigned > 0) doc->patientsAssigned--;
        doc->logAction("Discharged", p->id, p->name);
    }
    return true;
}


bool Hospital::updatePatient(int id, const Patient& updated) {
    bool ok = records.updatePatient(id, updated);
    if (ok) {
        Doctor* doc = findDoctorByName(updated.doctor);
        if (doc) doc->logAction("Updated", updated.id, updated.name);
    }
    return ok;
}

Patient* Hospital::findPatient(int id) {
    return records.findById(id);
}

QVector<Patient> Hospital::searchByName(const QString& name) const {
    return records.findByName(name);
}

QVector<Patient> Hospital::searchByDoctor(const QString& doctor) const {
    return records.findByDoctor(doctor);
}

QVector<Patient> Hospital::getAllPatients() const {
    return records.getAllPatients();
}

QVector<Patient> Hospital::getAdmittedPatients() const {
    return records.getAdmitted();
}


QVector<Patient> Hospital::getQueueSnapshot() const {
    QVector<Patient> snap;
    QueueNode* node = triageQueue.getFront();
    while (node != nullptr) {
        snap.append(node->data);
        node = node->next;
    }
    return snap;
}


int Hospital::addDoctor(const QString& name, const QString& spec, const QString& contact) {
    int id = nextDoctorId++;
    doctors.append(Doctor(id, name, spec, contact));
    return id;
}


bool Hospital::removeDoctor(int id) {
    for (int i = 0; i < doctors.size(); ++i) {
        if (doctors[i].id == id) {
            doctors.remove(i);
            return true;
        }
    }
    return false;
}


Doctor* Hospital::findDoctor(int id) {
    for (Doctor& d : doctors)
        if (d.id == id) return &d;
    return nullptr;
}


Doctor* Hospital::findDoctorByName(const QString& name) {
    for (Doctor& d : doctors)
        if (d.name.contains(name, Qt::CaseInsensitive)) return &d;
    return nullptr;
}





HospitalStats Hospital::getStats() const {
    HospitalStats stats;
    stats.totalDoctors    = doctors.size();
    stats.patientsInQueue = triageQueue.size();

    QVector<Patient> all = records.getAllPatients();
    stats.totalPatients     = all.size();
    stats.admittedPatients  = 0;
    stats.dischargedPatients= 0;
    stats.criticalCases     = 0;

    for (const Patient& p : all) {
        if (p.admitted)  stats.admittedPatients++;
        else             stats.dischargedPatients++;
        if (p.severity == Severity::Critical) stats.criticalCases++;
    }
    
    QueueNode* node = triageQueue.getFront();
    while (node) {
        if (node->data.severity == Severity::Critical) stats.criticalCases++;
        node = node->next;
    }
    return stats;
}


void Hospital::loadSampleData() {
    
    addDoctor("Dr. Sarah Ahmed",   "Cardiology",    "0300-1234567");
    addDoctor("Dr. Rahul Khan",    "Neurology",     "0301-2345678");
    addDoctor("Dr. Aisha Malik",   "Orthopedics",   "0302-3456789");
    addDoctor("Dr. James Cooper",  "General Surgery","0303-4567890");

    
    auto admitDirect = [&](const QString& name, int age, const QString& gender,
                           const QString& disease, const QString& doctor,
                           Severity sev, const QString& date) {
        int id = nextPatientId++;
        Patient p(id, name, age, gender, disease, doctor, sev, date);
        p.admitted = true;
        records.addPatient(p);
        Doctor* d = findDoctorByName(doctor);
        if (d) { d->patientsAssigned++; d->logAction("Admitted", id, name); }
    };

    admitDirect("Ali Hassan",     32, "Male",   "Heart Arrhythmia",   "Dr. Sarah Ahmed",  Severity::Critical, "2025-02-18");
    admitDirect("Fatima Noor",    28, "Female", "Migraine",           "Dr. Rahul Khan",   Severity::High,     "2025-02-19");
    admitDirect("Ahmed Raza",     45, "Male",   "Fractured Femur",    "Dr. Aisha Malik",  Severity::High,     "2025-02-20");
    admitDirect("Zara Sheikh",    60, "Female", "Appendicitis",       "Dr. James Cooper", Severity::Critical, "2025-02-20");
    admitDirect("Omar Farooq",    22, "Male",   "Flu",                "Dr. Rahul Khan",   Severity::Low,      "2025-02-21");

    
    addToTriage("Bilal Akhtar",  38, "Male",   "Chest Pain",       "Dr. Sarah Ahmed",  Severity::Critical);
    addToTriage("Sana Javed",    50, "Female", "Knee Pain",        "Dr. Aisha Malik",  Severity::Medium);
    addToTriage("Tariq Mehmood", 29, "Male",   "Food Poisoning",   "Dr. James Cooper", Severity::High);
    addToTriage("Nadia Hussain", 41, "Female", "Back Pain",        "Dr. Aisha Malik",  Severity::Low);
}
