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

    void push(T item){
        data->prepend(item);
    }

    T get(){
        return data->getFirst();
    }

    T pop(){
        T item = data->getFirst;
        data->popForward();
        return item;
    }

    int size(){
        return data->getLength();
    }

    void clear(){
        delete data;
        data = new LinkedList<T>();
    }
private:
    LinkedList<T>* data;
};

#endif //UNTITLED_STACK_H
