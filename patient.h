#ifndef PATIENT_H
#define PATIENT_H
#include <QString>


enum class Severity {
    Critical  = 1,   
    High      = 2,
    Medium    = 3,
    Low       = 4    
};


inline QString severityToString(Severity s) {
    switch (s) {
        case Severity::Critical: return "Critical";
        case Severity::High:     return "High";
        case Severity::Medium:   return "Medium";
        case Severity::Low:      return "Low";
        default:                 return "Unknown";
    }
}

inline Severity intToSeverity(int val) {
    switch (val) {
        case 1:  return Severity::Critical;
        case 2:  return Severity::High;
        case 3:  return Severity::Medium;
        default: return Severity::Low;
    }
}


struct Patient {
    int     id;           
    QString name;         
    int     age;          
    QString gender;       
    QString disease;      
    QString doctor;       
    Severity severity;    
    QString admitDate;    
    bool    admitted;     

    
    Patient()
        : id(0), age(0), severity(Severity::Low), admitted(false) {}

    
    Patient(int id, const QString& name, int age, const QString& gender,
            const QString& disease, const QString& doctor,
            Severity severity, const QString& admitDate)
        : id(id), name(name), age(age), gender(gender),
          disease(disease), doctor(doctor),
          severity(severity), admitDate(admitDate), admitted(true) {}
};

#endif 
