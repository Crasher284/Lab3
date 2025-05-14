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

    void push(T item){
        data->append(item);
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

    ~Queue(){
        delete data;
    }
private:
    LinkedList<T>* data;
};

#endif //UNTITLED_QUEUE_H
