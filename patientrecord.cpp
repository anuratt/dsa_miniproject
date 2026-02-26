#include "patientrecord.h"


PatientRecord::PatientRecord()
    : head(nullptr), tail(nullptr), count(0) {}


PatientRecord::~PatientRecord() {
    RecordNode* current = head;
    while (current != nullptr) {
        RecordNode* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}


void PatientRecord::addPatient(const Patient& p) {
    RecordNode* newNode = new RecordNode(p);

    if (head == nullptr) {
        
        head = tail = newNode;
    } else {
        
        newNode->next = head;
        head->prev    = newNode;
        head          = newNode;
    }
    count++;
}


bool PatientRecord::removePatient(int id) {
    RecordNode* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            
            if (current->prev != nullptr)
                current->prev->next = current->next;
            else
                head = current->next;   

            
            if (current->next != nullptr)
                current->next->prev = current->prev;
            else
                tail = current->prev;   

            delete current;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;   
}


bool PatientRecord::updatePatient(int id, const Patient& updated) {
    RecordNode* current = head;
    while (current != nullptr) {
        if (current->data.id == id) {
            current->data = updated;
            return true;
        }
        current = current->next;
    }
    return false;
}


Patient* PatientRecord::findById(int id) {
    RecordNode* current = head;
    while (current != nullptr) {
        if (current->data.id == id)
            return &current->data;
        current = current->next;
    }
    return nullptr;   
}


QVector<Patient> PatientRecord::findByName(const QString& name) const {
    QVector<Patient> results;
    RecordNode* current = head;
    while (current != nullptr) {
        if (current->data.name.contains(name, Qt::CaseInsensitive))
            results.append(current->data);
        current = current->next;
    }
    return results;
}


QVector<Patient> PatientRecord::findByDoctor(const QString& doctor) const {
    QVector<Patient> results;
    RecordNode* current = head;
    while (current != nullptr) {
        if (current->data.doctor.contains(doctor, Qt::CaseInsensitive))
            results.append(current->data);
        current = current->next;
    }
    return results;
}


QVector<Patient> PatientRecord::getAllPatients() const {
    QVector<Patient> all;
    RecordNode* current = head;
    while (current != nullptr) {
        all.append(current->data);
        current = current->next;
    }
    return all;
}


QVector<Patient> PatientRecord::getAdmitted() const {
    QVector<Patient> admitted;
    RecordNode* current = head;
    while (current != nullptr) {
        if (current->data.admitted)
            admitted.append(current->data);
        current = current->next;
    }
    return admitted;
}
