//
// Created by admin on 08.05.2025.
//

#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H
#include <stdexcept>
#include <iostream>

template <typename T>
class LinkedList {
public:
    LinkedList(T* items, int count){
        size = count;
        if(count == 0){
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new Node(items[0]);
        Node* current = head;
        for(int i=1;i<count;i++){
            current->next = new Node(items[i], nullptr, current);
            current = current->next;
        }
        tail = current;
    }

    LinkedList() : LinkedList(nullptr, 0) {}

    LinkedList(const LinkedList <T> &list) {
        size = list.size;
        if(list.head == nullptr){
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new Node(list.head->data);
        Node* current = head;
        Node* cCurrent = list.head->next;
        while (cCurrent != nullptr) {
            current->next = new Node(cCurrent->data, nullptr, current);
            current = current->next;
            cCurrent = cCurrent->next;
        }
        tail = current;
    }

    T getFirst() const{
        if(head == nullptr){
            throw std::out_of_range("That LinkedList is empty; there are no first element.");
        }
        return head->data;
    }

    T getLast() const {
        if(tail == nullptr){
            throw std::out_of_range("That LinkedList is empty; there are no last element.");
        }
        return tail->data;
    }

    T get(int index) const{
        if(index<0 || index>=size){
            throw std::out_of_range("Used index cannot be interpreted as index of LinkedList.");
        }
        Node* current;
        if(index<=size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        }else{
            current = tail;
            for(int i=0; i < size-1-index; i++){
                current = current->prev;
            }
        }
        return current->data;
    }

    LinkedList<T>* getSublist(int startIndex, int endIndex){
        if(startIndex<0 || startIndex>=size || endIndex<0 || endIndex>=size || endIndex<startIndex){
            throw std::out_of_range("Used indexes or their combination are invalid.");
        }
        auto output = new LinkedList<T>();
        Node* current = head;
        for(int i=0;i<=endIndex;i++){
            if(i>=startIndex){
                output->append(current->data);
            }
            current = current->next;
        }
        return output;
    }

    int getLength() const{
        return size;
    }

    void append(T item){
        Node* nw = new Node {item, nullptr, tail};
        if(tail){
            tail->next = nw;
        }else{
            head = nw;
        }
        tail = nw;
        size++;
    }

    void prepend(T item){
        Node* nw = new Node {item, head, nullptr};
        if(head){
            head->prev = nw;
        }else{
            tail = nw;
        }
        head = nw;
        size++;
    }

    void popForward(){
        if(head == nullptr){
            throw std::out_of_range("popForward: cannot delete element from empty list.");
        }
        Node* ex = head->next;
        delete head;
        head = ex;
        if(head) {
            head->prev = nullptr;
        }else{
            tail = nullptr;
        }
        size--;
    }

    void popBackward(){
        if(tail == nullptr){
            throw std::out_of_range("popBackward: cannot delete element from empty list.");
        }
        Node* ex = tail->prev;
        delete tail;
        tail = ex;
        if(tail) {
            tail->next = nullptr;
        }else{
            head = nullptr;
        }
        size--;
    }

    void insertAt(T item, int index){
        if(index<0 || index>size){
            throw std::out_of_range("Used index cannot be interpreted as index of LinkedList.");
        }
        if(index==0){
            prepend(item);
            return;
        }
        if(index==size){
            append(item);
            return;
        }
        Node* current = head;
        for(int i=0;i<index-1;i++){
            current = current->next;
        }
        Node* nw = new Node{item, current->next, current};
        current->next->prev = nw;
        current->next = nw;
        size++;
    }

    void popAt(int index){
        if(index<0 || index>size){
            throw std::out_of_range("Used index cannot be interpreted as index of LinkedList.");
        }
        if(index==0){
            popForward();
            return;
        }
        if(index==size-1){
            popBackward();
            return;
        }
        Node* current = head;
        for(int i=0;i<index;i++){
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }

    LinkedList<T> * concat(LinkedList<T> *list){
        auto* output = new LinkedList<T>(*this);
        for(int i=0;i<list->getLength();i++){
            output->append(list->get(i));
        }
        return output;
    }

    T& operator[](int index){
        if(index<0 || index>=size){
            throw std::out_of_range("Used index cannot be interpreted as index of LinkedList.");
        }
        Node* current = head;
        for(int i=0;i<index;i++){
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const{
        if(index<0 || index>=size){
            throw std::out_of_range("Used index cannot be interpreted as index of LinkedList.");
        }
        Node* current = head;
        for(int i=0;i<index;i++){
            current = current->next;
        }
        return current->data;
    }

    LinkedList<T>* operator+(const LinkedList<T>* other){
        return concat(other);
    }

    LinkedList<T>& operator=(const LinkedList<T>& other){
        if (this != &other) {
            Node* current = head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            size = 0;

            if(other.head != nullptr){
                head = new Node(other.head->data);
                current = head;
                Node* sCurrent = other.head->next;
                while (sCurrent != nullptr) {
                    current->next = new Node(sCurrent->data, nullptr, current);
                    current = current->next;
                    sCurrent = sCurrent->next;
                }
                tail = current;
                size = other.size;
            }
            return *this;
        }
        return *this;
    }

    ~LinkedList(){
        Node* current = head;
        while(current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
        size=0;
    }

private:
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;

        Node(T data = T(), Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}
    };

    Node* head;
    Node* tail;
    int size;
};

template <typename T>
std::ostream& operator << (std::ostream &os, LinkedList<T> &list){
    os << "* <-> ";
    for(int i=0;i<list.getLength();i++){
        os << "[" << list.get(i) << "] <-> ";
    }
    os << "*";
    return os;
}

#endif //LAB2_LINKEDLIST_H
