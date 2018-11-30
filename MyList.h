#ifndef PROJ5V2_MYLIST_PROJ5_H
#define PROJ5V2_MYLIST_PROJ5_H

#include <iostream>
using namespace std;

template <class T>
class Node{
public:
    T data;
    Node *next;

    Node(T d){
        data = d;
        next = NULL;
    }

    ~Node(){
        delete next;
    }
};

class BADINDEX {};

template <class T>
class ContainerIfc{
public:
    virtual ContainerIfc<T>& pushFront(T) = 0;
    virtual ContainerIfc<T>& pushBack(T) = 0;
    virtual ContainerIfc<T>& popFront(T&) = 0;
    virtual ContainerIfc<T>& popBack(T&) = 0;
    virtual int getSize() = 0;
    virtual bool isEmpty() = 0;
    virtual T front() = 0;
    virtual T back() = 0;
    virtual T& operator [] (int) = 0;
    virtual void erase() = 0;
};

template <class T>
class MyList: public ContainerIfc<T>{
public:
    MyList();
    ~ MyList();
    MyList(const MyList &);
    MyList <T>& operator = (const MyList &);
    MyList <T>& pushFront(T);
    MyList <T>& pushBack(T);
    MyList <T>& popFront(T&);  // throws BADINDEX
    MyList <T>& popBack(T&);   // throws BADINDEX
    int getSize();
    bool isEmpty();
    T  front();           // throws BADINDEX
    T  back();            // throws BADINDEX
    T& operator [](int);  // throws BADINDEX
    void erase();
    void display(ostream &out){
            Node<T> *temp = this->head;
            while(temp != NULL){
                out << temp->data << " -> ";
                temp = temp->next;
            }
            out << "NULL";
    }

private:
    Node<T> *head;
    Node<T> *tail;
};

template <class T>
MyList<T>::MyList() {
    this->head = NULL;
    this->tail = NULL;
}

template <class T>
MyList<T>::~MyList(){
    delete this->head;
}

template <class T>
MyList<T>::MyList(const MyList & that) {
    this->head = NULL;
    this->tail = NULL;
    if(that.head != NULL) {
        this->head = new Node<T>(that.head->data);
        Node<T> *thisTemp = this->head;
        Node<T> *thatTemp = that.head->next;

        while (thatTemp != NULL) {
            thisTemp->next = new Node<T>(thatTemp->data);
            thisTemp = thisTemp->next;
            thatTemp = thatTemp->next;
        }
        this->tail = thisTemp;
    }
}

template <class T>
MyList<T>& MyList<T>::operator=(const MyList & that) {
    if(this != &that){
        if(!isEmpty()){
            delete this->head;
        }
        this->head = NULL;
        this->tail = NULL;
        if(that.head != NULL) {
            this->head = new Node<T>(that.head->data);
            Node<T> *thisTemp = this->head;
            Node<T> *thatTemp = that.head->next;

            while (thatTemp != NULL) {
                thisTemp->next = new Node<T>(thatTemp->data);
                thisTemp = thisTemp->next;
                thatTemp = thatTemp->next;
            }
            this->tail = thisTemp;
        }
    }
    return *this;
}

template <class T>
MyList<T>& MyList<T>::pushFront(T n) {
    if(!isEmpty()){
        Node<T> *temp;
        temp = new Node<T>(n);
        temp->next = head;
        head = temp;
    }else{
        this->head = new Node<T>(n);
        this->tail = this->head;
    }
    return *this;
}

template <class T>
MyList<T>& MyList<T>::pushBack(T n){
    if(isEmpty()){
        this->head = new Node<T>(n);
        this->tail = this->head;
    }else{
        Node<T> *temp = this->tail;
        temp->next = new Node<T>(n);
        this->tail = temp->next;
    }
    return *this;
}

template <class T>
MyList<T>& MyList<T>::popFront(T& n){
    if(isEmpty()){
        throw BADINDEX();
    }
    n = this->head->data;
    Node<T> *temp = this->head->next;
    this->head->next = NULL;
    delete this->head;
    this->head = temp;
    return *this;
}

template <class T>
MyList<T>& MyList<T>::popBack(T& n){
    if(isEmpty()){
        throw BADINDEX();
    }else if(head->next == NULL){
        n = this->head->data;
        delete this->head;
        this->head = NULL;
    }else {
        Node<T> *temp = this->head->next;
        Node<T> *trail = this->head;
        while (temp->next != NULL) {
            trail = temp;
            temp = temp->next;
        }
        n = temp->data;
        trail->next = temp->next;
        this->tail = trail;
        delete temp;
    }
    return *this;
}

template <class T>
int MyList<T>::getSize() {
    int size = 0;
    if(this->head == NULL){
        size = 0;
    }else{
        Node<T> *temp = this->head;
        while(temp != NULL){
            temp = temp->next;
            size++;
        }
    }
    return size;
}

template <class T>
bool MyList<T>::isEmpty() {
    return this->head == NULL;
}

template <class T>
T MyList<T>::front(){
    if(isEmpty()){
        throw BADINDEX();
    }
    return this->head->data;
}

template <class T>
T MyList<T>::back() {
    if(isEmpty()){
        throw BADINDEX();
    }
    return this->tail->data;
}

template <class T>
T& MyList<T>::operator[](int n) {
    if(isEmpty() || n < 0 || n > getSize() - 1){
        throw BADINDEX();
    }
    int index = 0;
    Node<T> *temp = this->head;
    while(index != n){
        temp = temp->next;
        index++;
    }
    return temp->data;
}

template <class T>
void MyList<T>::erase(){
    delete this->head;
    this->head = this->tail = NULL;
}

#endif //PROJ5V2_MYLIST_PROJ5_H
