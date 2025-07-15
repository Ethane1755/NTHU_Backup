#ifndef FUNCTION_H
#define FUNCTION_H
class Darray {
    public:
        Darray() {
            capacity = 100;
            size = 0;
            data = new int[capacity];
        };
        ~Darray();
        int& operator[](int);
        void pushback(int x);
        void clear(void);
        int length(void);
    private:
        void resize(void); // double the capacity
        int *data;
        int capacity;
        int size;
};

Darray::~Darray() {
    delete[] data;
}

int& Darray::operator[](int i) {
    return data[i];
}

void Darray::pushback(int x) {
    if (length() == capacity) {
        resize();
    }
    data[size++] = x;
}

int Darray::length() {
    return size;
}

void Darray::resize() {
    int new_capacity = capacity * 2;
    int* new_data = new int [new_capacity];
    for (int i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void Darray::clear() {
    size = 0;
}



#endif
