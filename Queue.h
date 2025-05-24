//
// Created by admin on 07.05.2025.
//

#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H

#include "Deque.h"

template <typename T>
class Queue {
public:
    Queue(){
        data = new LinkedList<T>();
    }

    Queue(const Queue& other) : data(new LinkedList<T>(*other.data)) {}

    void push(T item){
        data->append(item);
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

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            delete data;
            data = new LinkedList<T>(*other.data);
        }
        return *this;
    }

    ~Queue(){
        delete data;
    }
private:
    LinkedList<T>* data;
};

#endif //UNTITLED_QUEUE_H
