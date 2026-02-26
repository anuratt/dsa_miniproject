#include "queue.h"
#include <stdexcept>

PatientQueue::PatientQueue()
    : front(nullptr), rear(nullptr), count(0) {}


PatientQueue::~PatientQueue() {
    clear();
}


void PatientQueue::enqueue(const Patient& p) {
    QueueNode* newNode = new QueueNode(p);

    
    if (isEmpty()) {
        front = rear = newNode;
        count++;
        return;
    }

    
    if (static_cast<int>(p.severity) < static_cast<int>(front->data.severity)) {
        newNode->next = front;
        front = newNode;
        count++;
        return;
    }

    
    
    QueueNode* current = front;
    while (current->next != nullptr &&
           static_cast<int>(current->next->data.severity) <= static_cast<int>(p.severity)) {
        current = current->next;
    }

    
    newNode->next = current->next;
    current->next = newNode;

    
    if (newNode->next == nullptr) {
        rear = newNode;
    }

    count++;
}



Patient PatientQueue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty — no patients to dequeue.");
    }

    QueueNode* temp    = front;
    Patient    patient = temp->data;  

    front = front->next;             

    
    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;   
    count--;

    return patient;
}


Patient PatientQueue::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }
    return front->data;
}


bool PatientQueue::isEmpty() const {
    return front == nullptr;
}


int PatientQueue::size() const {
    return count;
}


void PatientQueue::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}
