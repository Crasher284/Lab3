//
// Created by admin on 07.05.2025.
//

#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H

#include "LinkedList.h"

template <typename T>
class Stack {
public:
    Stack(){
        data = new LinkedList<T>();
    }

    Stack(const Stack& other) : data(new LinkedList<T>(*other.data)) {}

    void push(T item){
        data->prepend(item);
    }

    T get() const{
        return data->getFirst();
    }

    T pop(){
        T item = data->getFirst();
        data->popForward();
        return item;
    }

    int size() const{
        return data->getLength();
    }

    void clear(){
        delete data;
        data = new LinkedList<T>();
    }

    bool isEmpty() const { return data->getLength() == 0; }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete data;
            data = new LinkedList<T>(*other.data);
        }
        return *this;
    }

    ~Stack() {
        delete data;
    }
private:
    LinkedList<T>* data;
};

#endif //UNTITLED_STACK_H
