//
// Created by luyao on 2020/11/24.
//

#ifndef CHAPTER10_PRIORITY_QUEUE_PRIORITYQUEUE_H
#define CHAPTER10_PRIORITY_QUEUE_PRIORITYQUEUE_H

#include "../chapter2-vector/cpp/vector_dsa.h"

template <typename T>
class PriorityQueue:public VectorDsa<T>{
protected:
    Rank percolateUp(Rank i);
    // 逐步上滤，判断当前节点与父节点的优先级大小，如果不符合堆的要求就调换
    Rank percolateDown(Rank n, Rank i);
    // 逐步下滤，判断当前节点与左右子树根节点的优先级大小，如果不符合堆的要求就调换。
    // 如果和两个子树都不符合要求，那么选择和优先级更大的子树根节点进行调换
    Rank biggerChild(Rank i, Rank j) {
        return (_elem[i] < _elem[j]) ? j : i;
    }

    void heapify(Rank n);
public:
    PriorityQueue(){};
    PriorityQueue(T* A, Rank n){VectorDsa<T>::copyFrom(A, 0, n); heapify(n);}
    //方法一：先保证满足完全二叉树的结构性，再调整为满足堆特点的结构体
    //方法二：空堆里不停insert插入堆。
    void insert(T);
    T getMax(){
        return this->_elem[0];}
    T delMax();
};

template <typename T>
void PriorityQueue<T>::insert(T t){
    VectorDsa<T>::insert(t);
    percolateUp(_size - 1); //逐步上滤，判断当前节点与父节点的优先级大小，如果不符合堆的要求就调换
}

template <typename T>
Rank PriorityQueue<T>::percolateUp(Rank i){
    while(i/2 >= 0){
        if(swap(this->_elem[i/2] >= this->_elem[i])){
            break;
        }
        swap(this->_elem[i/2],this->_elem[i]);
        i = i/2;
    }
    return i;
} //逐步上滤，判断当前节点与父节点的优先级大小，如果不符合堆的要求就调换

template <typename T>
T PriorityQueue<T>::delMax(){
    T max_elem = this->_elem[0];
    this->_elem[0] = this->_elem[--this->_size];
    percolateDown(_size, 0);
    return max_elem;
}

template <typename T>
Rank PriorityQueue<T>::percolateDown(Rank n, Rank i){
    Rank j;
    while(this->_elem[i] < this->_elem[j = biggerChild(2*i, 2*i+1)]){
        swap(this->_elem[i], this->_elem[j]);
        i = j;
    }
    return i;
}


#endif //CHAPTER10_PRIORITY_QUEUE_PRIORITYQUEUE_H
