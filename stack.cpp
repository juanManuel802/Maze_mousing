#ifndef STACK_CPP
#define STACK_CPP
#include "Stack.h"
template<typename T>
void Stack<T>::push(const T &value) {
list.insert(0, value);
}
template<typename T>
void Stack<T>::pop(){
list.erase(0);
}
