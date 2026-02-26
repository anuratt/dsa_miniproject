#ifndef QUEUE_H
#define QUEUE_H
#include "patient.h"
struct QueueNode {
    Patient    data;   
    QueueNode* next;   

    explicit QueueNode(const Patient& p) : data(p), next(nullptr) {}
};


class PatientQueue {
private:
    QueueNode* front;   
    QueueNode* rear;    
    int        count;   

public:
    PatientQueue();
    ~PatientQueue();

    
    void    enqueue(const Patient& p);   
    Patient dequeue();                   
    Patient peek() const;               

    
    bool isEmpty() const;
    int  size()    const;
    void clear();

    
    QueueNode* getFront() const { return front; }
};

#endif 
