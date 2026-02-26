#ifndef DOCTOR_H
#define DOCTOR_H
#include <QString>
#include <QVector>
#include <QDateTime>


struct DoctorAction {
    QString   actionType;     
    int       patientId;      
    QString   patientName;    
    QString   timestamp;      

    DoctorAction() : patientId(0) {}
    DoctorAction(const QString& type, int pid, const QString& pname)
        : actionType(type), patientId(pid), patientName(pname),
          timestamp(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")) {}
};


struct StackNode {
    DoctorAction data;
    StackNode*   next;
    explicit StackNode(const DoctorAction& a) : data(a), next(nullptr) {}
};


class ActionStack {
private:
    StackNode* top;
    int        count;

public:
    ActionStack();
    ~ActionStack();

    void         push(const DoctorAction& action);  
    DoctorAction pop();                              
    DoctorAction peek() const;                       
    bool         isEmpty() const;
    int          size()    const;
    QVector<DoctorAction> getHistory() const;        
};


struct Doctor {
    int         id;
    QString     name;
    QString     specialization;
    QString     contact;
    int         patientsAssigned;   
    ActionStack actionHistory;      

    Doctor() : id(0), patientsAssigned(0) {}
    Doctor(int id, const QString& name, const QString& spec, const QString& contact)
        : id(id), name(name), specialization(spec),
          contact(contact), patientsAssigned(0) {}

    void logAction(const QString& type, int patientId, const QString& patientName) {
        actionHistory.push(DoctorAction(type, patientId, patientName));
    }
};

#endif 
