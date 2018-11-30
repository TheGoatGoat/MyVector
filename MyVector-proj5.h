
#ifndef PROJ5V2_MYVECTOR_PROJ5_H
#define PROJ5V2_MYVECTOR_PROJ5_H

#include "ContainerIfc.h"

using namespace std;

template <class T>
class MyVector : public ContainerIfc<T>{
public:
    MyVector();
    ~MyVector();
    MyVector (const MyVector&);
    MyVector<T>&operator = (const MyVector&);
    MyVector<T>& pushFront(T);
    MyVector<T>& pushBack(T);
    MyVector<T>& popFront(T&);
    MyVector<T>& popBack(T&);
    T front();
    T back();
    T&operator[](int);
    int getSize();
    bool isEmpty();
    void erase();

protected:
    T *data;
    int size;
    int capacity;
    void grow();
    void shiftRight();
    void shiftLeft();
};

//Constructor
template <class T>
MyVector<T>::MyVector() {
    this->size = 0;
    this->capacity = 10;
    this->data = new T[capacity];
}


//Destructor
template <class T>
MyVector<T>::~MyVector (){
    delete [] this->data;
}

//Copy Constructor
template <class T>
MyVector<T>::MyVector (const MyVector& obj){
    this-> size = obj.size;
    this->capacity = obj.capacity;
    this->data = new T [this->capacity];
    for(int i = 0; i < this->size; i++){
        this->data[i] = obj.data[i];
    }
}

//Overloaded "=" operator
template <class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& that){
    if(this != &that){
        delete [] this->data;
        this->capacity = that.capacity;
        this->size = that.size;
        this->data = new T [this->capacity];
        for(int i = 0; i < this->size; i++){
            this->data[i] = that.data[i];
        }
    }
    return *this;
}

//Adds an element to the front of the vector
template<class T>
MyVector<T>& MyVector<T>::pushFront(T val){
    shiftRight();
    this->data[0] = val;
    return *this;
}

//Adds an element to the end of the vector
template <class T>
MyVector<T>& MyVector<T>::pushBack(T val){
    if(this->size == this->capacity){
        grow();
    }
    this->data[this->size] = val;
    this->size++;
    return *this;
}

//Removes element from front of vector
template <class T>
MyVector<T>& MyVector<T>::popFront(T& val){
    if(isEmpty()){
        throw BADINDEX();
    }
    val = this->data[0];
    this->size--;
    shiftLeft();
    return *this;
}

//Removes element from end of the vector
template <class T>
MyVector<T>& MyVector<T>::popBack(T& val){
    if(this->size > 0) {
        val = this->data[this->size - 1];
        this->size--;
    } else{
        throw BADINDEX();
    }
    return*this;
}

//Returns the first element in the vector
template <class T>
T MyVector<T>::front(){
    if(isEmpty()){
        throw BADINDEX();
    }

    return this->data[0];
}

//Returns the last element in the vector
template <class T>
T MyVector<T>::back(){
    if(isEmpty()){
        throw BADINDEX();
    }
    return this->data[this->size - 1];
}

//Overloaded "[]" operator
template <class T>
T& MyVector<T>::operator [](int ndx){
    //Bounds Checking
    if(ndx >= this->size || isEmpty())
        throw BADINDEX();
    return this->data[ndx];
}

//Returns size of vector
template <class T>
int MyVector<T>::getSize(){
    return this->size;
}

//Checks if vector is empty returns T/F
template <class T>
bool MyVector<T>::isEmpty(){
    return getSize() == 0;
}

//Increases the size of the vector by doubling previous capacity value
template <class T>
void MyVector<T>::grow() {
    this->capacity*=2;
    T *temp = this->data;
    this->data = new T [this->capacity];
    for(int i = 0; i < this->size; i++){
        this->data[i] = temp[i];
    }
    delete [] temp;

}

//Shifts all elements to the right
template <class T>
void MyVector<T>::shiftRight() {
    if(this->size+1 == this->capacity){
        grow();
    }
    for(int i = this->size; i >= 0; i--){
        this->data[i+1] = this->data[i];
    }
}

//Shifts all elements to the left
template<class T>
void MyVector<T>::shiftLeft() {
    for(int i = 0; i < this->size; i++){
        this->data[i] = this->data[i+1];
    }
}

template<class T>
void MyVector<T>::erase() {
    this->capacity = 10;
    this->size = 0;
    delete [] this->data;
    this->data = new T [this->capacity];

}


#endif //PROJ5V2_MYVECTOR_PROJ5_H
