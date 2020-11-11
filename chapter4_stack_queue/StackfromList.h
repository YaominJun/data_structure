//
// Created by luyao on 2020/11/10.
//

#ifndef CHAPTER4_STACK_QUEUE_STACKFROMLIST_H
#define CHAPTER4_STACK_QUEUE_STACKFROMLIST_H

#include "../chapter3_list/cpp/List.h"

template <typename T>
class StackfromList: public List<T>{
public:
    void push(T const& t);
    T pop();
    T& top(); //由于是返回值是引用，可以修改栈顶元素
};

template <typename T>
void StackfromList<T>::push(T const& t){
    this->insertAtFirst(t);
}

template <typename T>
T StackfromList<T>::pop(){
    return this->remove(this->first());
}

template <typename T>
T& StackfromList<T>::top(){
    return this->first()->data;
}

#endif //CHAPTER4_STACK_QUEUE_STACKFROMLIST_H
