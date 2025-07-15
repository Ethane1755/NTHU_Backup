#include<iostream>
#include<string.h>
#include"10998.h"
using namespace std;

List_stack::List_stack(): head(nullptr), tail(nullptr){}
List_stack::~List_stack() {
    if (head != nullptr) {
        ListNode *temp = head;
        head = head -> nextPtr;
        delete temp;
    }
}
void List_stack::push(const int & value) {
    ListNode *newNode = new ListNode(value);
    newNode -> nextPtr = head;
    newNode -> prevPtr = nullptr;
    if (head != nullptr) {
        head -> prevPtr = newNode;
    }
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
}
void List_stack::pop() {
    if (head == nullptr) return; 
    ListNode *temp = head;
    head = head -> nextPtr;
    if (head != nullptr) {
        head -> prevPtr = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}
void List_stack::print() {
    if (head == nullptr) return;
    ListNode *cur = head;
    while (cur -> nextPtr != nullptr) {
        cout << cur -> data << " ";
        cur = cur -> nextPtr;
    }
    cout << cur -> data;
}
