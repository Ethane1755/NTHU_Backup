#include<bits/stdc++.h>
#include "13862.h"
using namespace std;

void ParentA(Person* p) {
    if (!p -> parentA) {
        p -> parentA = new Person();
        p -> parentA -> child = p;
        if (p -> parentB) {
            p -> parentA -> mate = p -> parentB;
            p -> parentB -> mate = p -> parentA;
        }
    }
}

void ParentB(Person* p) {
    if (!p -> parentB) {
        p -> parentB = new Person();
        p -> parentB -> child = p;
        if (p -> parentA) {
            p -> parentA -> mate = p -> parentB;
            p -> parentB -> mate = p -> parentA;
        }
    }
}

void Mate(Person* p) {
    if (!p -> mate) {
        p -> mate = new Person();
        p -> mate -> mate = p;
        if (p -> child) {
            if (p -> child -> parentA == p) {
                p -> child -> parentB = p -> mate;
                p -> mate -> child = p -> child;
            } else if (p -> child -> parentB == p) {
                p -> child -> parentA = p -> mate;
                p -> mate -> child = p -> child;
            }
        }
    }
}

void Child(Person* p) {
    if (!p -> child) {
        p -> child = new Person();
        p -> child -> parentA = p;
        if (p -> mate) {
            p -> child -> parentB = p -> mate;
            p -> mate -> child = p -> child;
        }
    }
}

Person* Person::getRelative (string* arr, int now, int len){
    if (now == len) return this;
    if (arr[now] == "ParentA") {
        ParentA(this);
        return this -> parentA -> getRelative(arr, now + 1, len);
    } else if (arr[now] == "ParentB") {
        ParentB(this);
        return this -> parentB -> getRelative(arr, now + 1, len);
    } else if (arr[now] == "Mate") {
        Mate(this);
        return this -> mate -> getRelative(arr, now + 1, len);
    } else if (arr[now] == "Child") {
        Child(this);
        return this -> child-> getRelative(arr, now + 1, len);
    } else return this;
}

void Person::describe(string* arr, int now, int len) {
    if (now >= len) return;
    if (arr[now] == "ParentA") {
        ParentA(this);
        //printf("%s", this -> parentA -> info());
        this -> parentA -> describe(arr, now + 1, len);
    } else if (arr[now] == "ParentB") {
        ParentB(this);
        //printf("%s", this -> parentB -> info());
        this -> parentB -> describe(arr, now + 1, len);
    } else if (arr[now] == "Mate") {
        Mate(this);
        //printf("%s", this -> mate -> info());
        this -> mate -> describe(arr, now + 1, len);
    } else if (arr[now] == "Child") {
        Child(this);
        //printf("%s", this -> child -> info());
        this -> child -> describe(arr, now + 1, len);
    } else if (arr[now] == "Gender") {
        if (arr[now + 1] == "MALE") this->gender = MALE;
        else this->gender = FEMALE;
        this->describe(arr, now + 2, len);
    } else if (arr[now] == "Age") {
        this->age = stoi(arr[now + 1]);
        this->describe(arr, now + 2, len);
    } else if (arr[now] == "Name") {
        this->name = arr[now + 1];
        this->describe(arr, now + 2, len);
    } else if (arr[now] == "Personality") {
        if (this->personality == "") this->personality = arr[now + 1];
        else this->personality += " " + arr[now + 1];
        this->describe(arr, now + 2, len);
    }
}
