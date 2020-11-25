//
// Created by luyao on 2020/11/24.
//

#ifndef CHAPTER10_PRIORITY_QUEUE_PRIORITYQUEUE_H
#define CHAPTER10_PRIORITY_QUEUE_PRIORITYQUEUE_H

#include <iostream>
#include "../chapter2-vector/cpp/vector_dsa.h"
using namespace std;

template <typename T>
class PriorityQueue:public VectorDsa<T>{
protected:
    Rank percolateUp(Rank i);
    // 逐步上滤，判断当前节点与父节点的优先级大小，如果不符合堆的要求就调换
    Rank percolateDown(Rank n, Rank i);
    // 逐步下滤，判断当前节点与左右子树根节点的优先级大小，如果不符合堆的要求就调换。
    // 如果和两个子树都不符合要求，那么选择和优先级更大的子树根节点进行调换
    Rank biggerChild(Rank i, Rank j) {
        return (this->_elem[i] < this->_elem[j]) ? j : i;
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

//    void heapSort(VectorDsa<T> vectorDsa); //堆排序

    template <typename VST>
    friend ostream&operator<<(ostream &os, PriorityQueue<VST> const& heap_);

};

template <typename T>
void PriorityQueue<T>::heapify(Rank n){
    /**
     * 方法一：不停插入
     */
     /*
     for(int i = 1; i < n; i++){
         percolateUp(i); //不停在后面进行插入，所以是从i=1开始的。
     }
      */
     /*
      * floyd 算法，自下而上的下滤
      */
    for(int i = n/2 - 1; i >= 0; i --){
        percolateDown(n, i);
    }
}

template <typename T>
void PriorityQueue<T>::insert(T t){
    VectorDsa<T>::insert(t);
    percolateUp(this->_size - 1); //逐步上滤，判断当前节点与父节点的优先级大小，如果不符合堆的要求就调换
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
    percolateDown(this->_size, 0);
    return max_elem;
}

template <typename T>
Rank PriorityQueue<T>::percolateDown(Rank n, Rank i){
    Rank j;
    while(2*i+1 < n && this->_elem[i] < this->_elem[j = biggerChild(2*i, 2*i+1)]){
        swap(this->_elem[i], this->_elem[j]);
        i = j;
    }
    return i;
}

template <typename T>
//PriorityQueue<T>::
void heapSort(VectorDsa<T> &vectorDsa){
//堆排序
//先建堆，然后利用堆排序进行排序
    PriorityQueue<T> heap_(vectorDsa._elem, vectorDsa.size());
    Rank e = vectorDsa.size();
    while (!heap_.empty()){
        e--;
        vectorDsa._elem[e] = heap_.delMax(); //这一步已经将堆的首末元素调换完成，并且进行了下滤过程以满足堆的特性。
    }
} //堆排序

//友元
template <typename VST>
ostream& operator<<(ostream &os, PriorityQueue<VST> const& heap_){
    for(int i = 0; i < heap_.size(); i++){
        os << heap_._elem[i] << ",";
    }
    return os;
}



#endif //CHAPTER10_PRIORITY_QUEUE_PRIORITYQUEUE_H
