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

    void prepend(T item){
        data->prepend(item);
    }

    void append(T item){
        data->append(item);
    }

    T first(){
        return data->getFirst();
    }

    T last(){
        return data->getLast;
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

    int getLength(){
        return data->getLength();
    }

    void clear(){
        delete data;
        data = new LinkedList<T>;
    }

    ~Deque(){
        delete data;
    }

private:
    LinkedList<T>* data;
};

#endif //LAB2_DEQUE_H