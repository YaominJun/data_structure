//
// Created by luyao on 2020/11/6.
//

#ifndef CPP_LIST_H
#define CPP_LIST_H

#include <iostream>
#include "ListNode.h"
typedef int Rank;

template <typename T>
class List{
private:
    int _size;
    ListNode<T> *header;
    ListNode<T> *trailer;
protected:
    //内部成员函数
    void init();
    void copyNodes(ListNode<T> *p, int n); //复制[p, p+n)里的所有节点
    int clear(); //清除所有可见节点

public:
    //构造函数
    List();
    List(List<T> const& list_);
    List(ListNode<T> *p, int n);
    //析构函数
    ~List();

    //只读接口
    int size(){ return _size;}
    bool empty(){ return !_size;}
    T& operator[](Rank r) const;
    ListNode<T>* first()const{ return header->next;}
    ListNode<T>* last()const{ return trailer->prev;}
    ListNode<T>* find(ListNode<T>* p, int n, T const& t) const; //[p, p+n)区间查找
    ListNode<T>* find(int n, ListNode<T>* p, T const& t) const; //[p-n, p)区间查找
    ListNode<T> *find(T const& t){ return find(_size, trailer, t);} //保证秩最大
    ListNode<T> *search(int n, ListNode<T>* p, T const& t)const; //有序链表查找 //虽然在无序链表里不能直接用，但是
    //在插入排序中，可以先对前缀进行排序，然后逐步扩充有序区间的范围。而在此时可以用到search
    ListNode<T> *search(T const& t)const{ return search(_size, trailer, t);}//[p - n, p)区间查找 //返回最大秩
    //在归并排序中的merge操作
    void merge(ListNode<T> *p_node, int p_index, List<T> &L, ListNode<T> *q_node, int q_index);

        //可写接口
    ListNode<T>* insertBefore(ListNode<T> *p,  T const& t); //将t插入到p前面
    ListNode<T>* insertAfter(ListNode<T> *p,  T const& t); //将t插入到p后面
    ListNode<T>* insertAtLast(T const& t){ return insertBefore(trailer, t);} //将t插入到最后面
    ListNode<T>* insertAtFirst(T const& t){ return insertAfter(header, t);} //将t插入到最前面
    ListNode<T>* insert(T const& t){ return insertAtLast(t);} //默认插入到后方
    T remove(ListNode<T> *p);
    int deduplicate(); //前缀比较法去重
    void traverse( void (*op) (T&)); //遍历 —— 函数指针
    template <typename VST>
    void traverse(VST op); //遍历 —— 函数对象
    void selectionSort(ListNode<T> *p, int n); //选择排序
    void selectionSort(){ selectionSort(first(), _size);} //默认情况下的整体选择排序
    ListNode<T>* selectMax(ListNode<T> *p, int n); //从[p, p+n)中找到最大值位置
    ListNode<T>* selectMax(){ return selectMax(first(), _size);}; //默认情况系的整体最大值
    ListNode<T>* selectMin(ListNode<T> *p, int n); //从[p, p+n)中找到最小值位置
    ListNode<T>* selectMin(){ return selectMax(first(), _size);}; //默认情况系的整体最小值
    void insertSort(ListNode<T> *p, int n); //插入排序
    void insertSort(){ return insertSort(first(), _size);} //默认情况下的整体插入排序
    void mergeSort(ListNode<T> *p, int n); //归并排序
    void mergeSort(){return mergeSort(first(), _size);} //归并排序

    //友元
    template <typename VST>
    friend ostream& operator<<(ostream &os, List<VST> const &list_);

};

//内部成员函数
template <typename T>
void List<T>::init(){
    //默认初始化的情况下，链表是空的！！！
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->prev = nullptr; header->next = trailer;
    trailer->prev = header; trailer->next = nullptr;
    _size = 0;
}

template <typename T>
void List<T>::copyNodes(ListNode<T> *p, int n){
    init();
    //复制[p, p+n)里的所有节点
    for (int i = 0; i < n; ++i) {
        insertAtLast(p->data);
        p = p->next;
        n--;
    }
}

template <typename T>
int List<T>::clear(){
    int old_size = _size;
    //清除所有可见节点
    while (_size > 0){
        //或者是while(_size > 0)，因为remove操作会一直_size--;
        //或者是for(Rank i = 0; i < old_size; i++)
        remove(first());
    }
    return old_size;
}


//构造函数
template<typename T>
List<T>::List() {init();}

template<typename T>
List<T>::List(List<T> const& list_){
    copyNodes(list_.first(), list_.size());
}

template<typename T>
List<T>::List(ListNode<T> *p, int n){
    copyNodes(p, n);
}

//析构函数
template<typename T>
List<T>::~List(){
    clear();
    delete header;
    delete trailer;
}

//只读接口
template <typename T>
T& List<T>::operator[](Rank r) const{
    //效率低，不能像vector数组一样快速返回。
    ListNode<T> *p = first();
    Rank i = 0;
    while (i < r){
        p = p->next;
        i++;
    }
    return p->data;
}

template <typename T>
ListNode<T>* List<T>::find(ListNode<T>* p, int n, T const& t) const{
    //从前往后查找，能找到最小的秩
    //所以这里的是[p, p + n)区间查找
    while (n-- > 0){
        if(p->data == t){
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

template <typename T>
ListNode<T>* List<T>::find(int n, ListNode<T>* p, T const& t) const{
    //从后往前查找，能找到最大的秩
    //所以这里的是[p - n, p)区间查找
    while(n-- > 0){
        if((p->prev)->data == t){
            return p->prev;
        }
        p = p->prev;
    }
    return nullptr;
}

template <typename T>
ListNode<T> * List<T>::search(int n, ListNode<T>* p, T const& t)const{
    //有序链表查找
    //从后往前查找，能找到最大的秩
    //所以这里的是[p - n, p)区间查找
    while (n-- >= 0){
        if((p->prev)->data <= t){
            //注意和无需链表不同的是这里用的是<=，并且是break，返回
            p = p->prev;
            break;
        }
        p = p->prev;
    }
    return p;
}

//可写接口
template <typename T>
ListNode<T>* List<T>::insertBefore(ListNode<T> *p,  T const& t) {
    //将t插入到p前面
    if(p == header){
        return nullptr;
    }
    ListNode<T> *tmp_p = new ListNode<T>(p->prev, p, t); //不new的话，退出函数就没了
    (p->prev)->next = tmp_p;
    p->prev = tmp_p;
    _size++;
    return tmp_p;
}

template <typename T>
ListNode<T>* List<T>::insertAfter(ListNode<T> *p,  T const& t) {
    //将t插入到p后面
    if(p == trailer){
        return nullptr;
    }
    ListNode<T> *tmp_p = new ListNode<T>(p, p->next, t); //不new的话，退出函数就没了
    (p->next)->prev = tmp_p;
    p->next = tmp_p;
    _size++;
    return tmp_p;
}

template <typename T>
T List<T>::remove(ListNode<T> *p){
    T t = p->data;
    (p->prev)->next = p->next;
    (p->next)->prev = p->prev;
    delete p;
    _size--;
    return t;
}

template <typename T>
int List<T>::deduplicate(){
    Rank old_size = _size;
    //前缀比较法去重
    ListNode<T> *tmp = first();
    Rank r = 0; ListNode<T> *tmp_p_find;
    while (r <_size && tmp != trailer){
        tmp_p_find = find(first(), r, tmp->data);
        if(tmp_p_find){
            remove(tmp_p_find); //不可以这样写，因为tmp之后还要用到，不能直接remove掉！！！
        }else{
            r++;
        }
        tmp = tmp->next;
    }

    return old_size - _size;
}

template <typename T>
void List<T>::traverse( void (*op) (T& t)){
    //遍历 —— 函数指针
    ListNode<T> *tmp = first();
    while (tmp != trailer){
        op(tmp->data);
        tmp = tmp->next;
    }
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST op){
    //遍历 —— 函数对象
    ListNode<T> *tmp = first();
    while (tmp != trailer){
        op(tmp->data);
        tmp = tmp->next;
    }
}

//排序算法
/*
//版本一：变节点——remove和insert操作
template <typename T>
void List<T>::selectionSort(ListNode<T> *p, int n){
    //选择排序
    ListNode<T> *tmp_head = p->prev;
    ListNode<T> *tmp_tail = p;
    for(Rank i = 0; i < n; i++){
        tmp_tail = tmp_tail->next;
    }
    while(n > 1){
        //至少有两个元素才需要排序，否则不用
        ListNode<T> *tmp_max = selectMax(tmp_head->next, n);
        insertBefore(tmp_tail, tmp_max->data);
        remove(tmp_max);
        tmp_tail = tmp_tail->prev;
        n--;
    }
}
*/

//版本二：变数据域
template <typename T>
void List<T>::selectionSort(ListNode<T> *p, int n){
    ListNode<T> *tmp_head = p->prev;
    ListNode<T> *tmp_tail = p;
    for(Rank i = 0; i < n; i++){
        tmp_tail = tmp_tail->next;
    }
    while(n > 1){
        //至少有两个元素才需要排序，否则不用
        ListNode<T> *tmp_max = selectMax(tmp_head->next, n);
        if(tmp_max != tmp_tail->prev){
            T tmp_t = tmp_tail->prev->data;
            tmp_tail->prev->data = tmp_max->data;
            tmp_max->data = tmp_t;
        }
        tmp_tail = tmp_tail->prev;
        n--;
    }
}


template <typename T>
void List<T>::insertSort(ListNode<T> *p, int n) {
    //插入排序
    //版本一：插入
    for(Rank i = 0; i < n; i++){
        //至少有两个元素才需要排序，否则不用
        ListNode<T> *tmp_max = search(i, p, p->data);
        insertAfter(tmp_max, p->data);
        p = p->next;
        remove(p->prev);
    }
}

/*
template <typename T>
void List<T>::insertSort(ListNode<T> *p, int n){
    //插入排序
    //版本二：变数据域
    ListNode<T> *tmp_head = p->prev;
    ListNode<T> *tmp_tail = p;
    for(Rank i = 0; i < n; i++){
        tmp_tail = tmp_tail->next;
    }
    while(n > 1){
        ListNode<T> *tmp_min = selectMin(tmp_head->next, n);
        if(tmp_min != tmp_head->next){
            T tmp_t = tmp_head->next->data;
            tmp_head->next->data = tmp_min->data;
            tmp_min->data = tmp_t;
        }
        tmp_head = tmp_head->next;
        n--;
    }
}
*/

template <typename T>
void List<T>::mergeSort(ListNode<T> *p, int n){
    //归并排序
    if(n < 2){
        return;
    }
    //找到划分的中点位置
    int m_index = n / 2;
    ListNode<T> *middle = p;
    for(Rank i = 0; i < m_index; i++){
        middle = middle->next;
    }
    mergeSort(p, m_index);
    mergeSort(middle, n - m_index);
    merge(p, m_index, *this, middle, n-m_index);
}

template <typename T>
void List<T>::merge(ListNode<T> *p_node, int p_index, List<T> &L, ListNode<T> *q_node, int q_index){
    while ((p_index > 0) && (q_index > 0)){
        if(p_node->data <= q_node->data){
            p_node = p_node->next;
            if(q_node == p_node){
                break;
            }
            p_index--;
        } else{
            insertBefore(p_node, q_node->data);
            q_node = q_node->next;
            if(q_node == nullptr){
                break;
            }
            L.remove(q_node->prev);
            q_index--;
        }
    }
}

template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T> *p, int n){
    //从[p, p+n)中找到最大值位置
    ListNode<T> *tmp_max = p;
    while(n > 1){
        if(((p->next)->data) >= (tmp_max->data)){
            tmp_max = p->next;
        }
        p = p->next;
        n--;
    }
    return tmp_max;
}

template <typename T>
ListNode<T>* List<T>::selectMin(ListNode<T> *p, int n){
    //从[p, p+n)中找到最大值位置
    ListNode<T> *tmp_min = p;
    while(n > 1){
        if(((p->next)->data) < (tmp_min->data)){
            tmp_min = p->next;
        }
        p = p->next;
        n--;
    }
    return tmp_min;
}



//友元
template <typename VST>
ostream& operator<<(ostream &os, List<VST> const &list_){
    ListNode<VST> *tmp = list_.first();
    while (tmp != list_.trailer){
        os << tmp->data << ", ";
        tmp = tmp->next;
    }
    return os;
}

#endif //CPP_LIST_H
