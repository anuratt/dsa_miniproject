
#include "doctor.h"
#include <stdexcept>


ActionStack::ActionStack()
    : top(nullptr), count(0) {}


ActionStack::~ActionStack() {
    while (!isEmpty()) pop();
}


void ActionStack::push(const DoctorAction& action) {
    StackNode* newNode = new StackNode(action);
    newNode->next = top;   
    top = newNode;         
    count++;
}


DoctorAction ActionStack::pop() {
    if (isEmpty())
        throw std::underflow_error("Action stack is empty.");
    StackNode*   temp   = top;
    DoctorAction action = temp->data;
    top = top->next;   
    delete temp;
    count--;
    return action;
}


DoctorAction ActionStack::peek() const {
    if (isEmpty())
        throw std::underflow_error("Action stack is empty.");
    return top->data;
}

bool ActionStack::isEmpty() const { return top == nullptr; }
int  ActionStack::size()    const { return count; }


QVector<DoctorAction> ActionStack::getHistory() const {
    QVector<DoctorAction> history;
    StackNode* current = top;
    while (current != nullptr) {
        history.append(current->data);
        current = current->next;
    }
    return history;
}
