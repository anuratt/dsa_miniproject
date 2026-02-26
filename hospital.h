#ifndef HOSPITAL_H
#define HOSPITAL_H
#include "patient.h"
#include "queue.h"
#include "patientrecord.h"
#include "doctor.h"
#include <QVector>
#include <QString>


struct HospitalStats {
    int totalPatients;
    int admittedPatients;
    int dischargedPatients;
    int patientsInQueue;
    int totalDoctors;
    int criticalCases;
};


class Hospital {
private:
    QString        hospitalName;
    PatientQueue   triageQueue;    
    PatientRecord  records;        
    QVector<Doctor> doctors;       

    int nextPatientId;             
    int nextDoctorId;

public:
    explicit Hospital(const QString& name = "City General Hospital");

    
    int  addToTriage(const QString& name, int age, const QString& gender,
                     const QString& disease, const QString& doctorName,
                     Severity severity);          
    bool admitNextPatient();                      
    bool admitPatient(int patientId);             
    bool dischargePatient(int id);                
    bool updatePatient(int id, const Patient& updated);

    Patient*         findPatient(int id);
    QVector<Patient> searchByName(const QString& name)     const;
    QVector<Patient> searchByDoctor(const QString& doctor) const;
    QVector<Patient> getAllPatients()                       const;
    QVector<Patient> getAdmittedPatients()                  const;
    QVector<Patient> getQueueSnapshot()                     const;

    
    int  addDoctor(const QString& name, const QString& spec, const QString& contact);
    bool removeDoctor(int id);
    Doctor* findDoctor(int id);
    Doctor* findDoctorByName(const QString& name);
    QVector<Doctor>& getDoctors() { return doctors; }
    const QVector<Doctor>& getDoctors() const { return doctors; }

    
    HospitalStats getStats() const;

    
    QString       getName()      const { return hospitalName; }
    PatientQueue& getQueue()           { return triageQueue; }
    PatientRecord& getRecords()        { return records; }
    int           queueSize()   const { return triageQueue.size(); }
    int           totalRecords()const { return records.totalPatients(); }

    
    void loadSampleData();
};

#endif 
