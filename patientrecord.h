#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H
#include "patient.h"
#include <QVector>


struct RecordNode {
    Patient     data;   
    RecordNode* next;   
    RecordNode* prev;   

    explicit RecordNode(const Patient& p)
        : data(p), next(nullptr), prev(nullptr) {}
};


class PatientRecord {
private:
    RecordNode* head;   
    RecordNode* tail;   
    int         count;  

public:
    PatientRecord();
    ~PatientRecord();

    
    void    addPatient(const Patient& p);         
    bool    removePatient(int id);                
    bool    updatePatient(int id, const Patient& updated); 
    Patient* findById(int id);                    

    
    QVector<Patient> findByName(const QString& name) const;
    QVector<Patient> findByDoctor(const QString& doctor) const;
    QVector<Patient> getAllPatients() const;       
    QVector<Patient> getAdmitted() const;         

    int  totalPatients() const { return count; }
    bool isEmpty()       const { return head == nullptr; }

    RecordNode* getHead() const { return head; }
};

#endif 
