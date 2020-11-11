//
// Created by luyao on 2020/11/10.
//

#ifndef CHAPTER4_STACK_QUEUE_STACK_H
#define CHAPTER4_STACK_QUEUE_STACK_H

#include "../chapter2-vector/cpp/vector_dsa.h"

template <typename T> class Stack: public VectorDsa<T>{
public:
    void push(T const &t);
    T pop();
    T& top(); //由于是返回值是引用，可以修改栈顶元素
};

template <typename T>
void Stack<T>::push(T const &t){
    //压入栈顶元素
    this->insert(this->size(), t);
}

template <typename T>
T Stack<T>::pop(){
    //取出栈顶元素
    return this->remove(this->size() - 1);
}

template <typename T>
T& Stack<T>::top(){
    //查找栈顶元素
    return this->_elem[this->size() - 1];
}

#endif //CHAPTER4_STACK_QUEUE_STACK_H
