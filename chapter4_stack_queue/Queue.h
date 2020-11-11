//
// Created by luyao on 2020/11/11.
//

#ifndef CHAPTER4_STACK_QUEUE_QUEUE_H
#define CHAPTER4_STACK_QUEUE_QUEUE_H

#include "../chapter3_list/cpp/List.h"

template <typename T>
class Queue:public List<T>{
    //从链表进行继承更好，因为链表非常方便地在任何地方插入或删除。但是向量在前端插入和删除都需要进行挪动操作，时间复杂度需要O(N)。
public:
    void edqueue(T const &t); //入队 -> 队尾
    T dequeue(); //出队 -> 队首
    T& front();
};

template <typename T>
void Queue<T>::edqueue(T const &t){
    //入队 -> 队尾
    this->insertAtLast(t);
}

template <typename T>
T Queue<T>::dequeue(){
    //出队 -> 队首
    return this->remove(this->first());
}

template <typename T>
T& Queue<T>::front(){
    return this->first()->data;
}

#endif //CHAPTER4_STACK_QUEUE_QUEUE_H
