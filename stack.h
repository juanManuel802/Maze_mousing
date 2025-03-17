#ifndef STACK_H
#define STACK_H
#include "List.h"
template<typename T>
class Stack {
private:
List<T> list;
public:
void push(const T& value);
void pop();
T& top() const;
int size() const;
};
#endif