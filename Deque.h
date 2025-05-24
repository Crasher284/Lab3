//
// Created by admin on 25.03.2025.
//

#ifndef LAB2_DEQUE_H
#define LAB2_DEQUE_H

#include "LinkedList.h"

template <typename T>
class Deque {
public:
    Deque(){
        data = new LinkedList<T>();
    }

    Deque(const Deque& other) : data(new LinkedList<T>(*other.data)) {}

    void prepend(T item){
        data->prepend(item);
    }

    void append(T item){
        data->append(item);
    }

    T first() const{
        return data->getFirst();
    }

    T last() const{
        return data->getLast();
    }

    T popFirst(){
        T item = data->getFirst();
        data->popForward();
        return item;
    }

    T popLast(){
        T item = data->getLast();
        data->popBackward();
        return item;
    }

    int size() const{
        return data->getLength();
    }

    void clear(){
        delete data;
        data = new LinkedList<T>;
    }

    bool isEmpty() const { return data->getLength() == 0; }

    Deque& operator=(const Deque& other) {
        if (this != &other) {
            delete data;
            data = new LinkedList<T>(*other.data);
        }
        return *this;
    }

    ~Deque(){
        delete data;
    }

private:
    LinkedList<T>* data;
};

#endif //LAB2_DEQUE_H