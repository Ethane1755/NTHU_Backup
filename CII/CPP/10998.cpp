#include<iostream>
#include<string.h>
#include "10998.h"
using namespace std;

List_stack L_stack;

int main(){
    
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"pop")==0){
            L_stack.pop();
        }else if(strcmp(command,"push")==0){
            cin >> n;
            L_stack.push(n);
        }else if(strcmp(command, "print") == 0){
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}

List_stack::List_stack(): head(nullptr), tail(nullptr) {}
List_stack::~List_stack() {
    ListNode *Node = head;
    while (Node != nullptr) {
        ListNode *temp = Node;
        Node = Node -> nextPtr;
        delete temp;
    }
}

void List_stack::push(const int &value) {
    ListNode* newNode = new ListNode(value);
    newNode->nextPtr = head;
    newNode->prevPtr = nullptr;
    if (head != nullptr) {
        head->prevPtr = newNode;
    }
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
}

void List_stack::pop() {
    if (head == nullptr) return;
    ListNode* temp = head;
    head = head->nextPtr;
    if (head != nullptr) {
        head->prevPtr = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}

void List_stack::print() {
    ListNode *cur = head;
    if (cur == nullptr) return;
    while (cur -> nextPtr != nullptr) {
        cout << cur -> data << " ";
        cur = cur -> nextPtr;
    }
    cout << cur -> data;
}