//
// Created by luyao on 2020/11/6.
//

#ifndef CPP_ListOrderedORDERED_H
#define CPP_ListOrderedORDERED_H
//
// Created by luyao on 2020/11/6.
//

#include <iostream>
#include "ListNode.h"
typedef int Rank;

template <typename T>
class ListOrdered{
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
    ListOrdered();
    ListOrdered(ListOrdered<T> const& ListOrdered_);
    ListOrdered(ListNode<T> *p, int n);
    //析构函数
    ~ListOrdered();

    //只读接口
    int size(){ return _size;}
    T& operator[](Rank r) const;
    ListNode<T>* first()const{ return header->next;}
    ListNode<T>* last()const{ return trailer->prev;}
    ListNode<T>* find(ListNode<T>* p, int n, T const& t) const; //[p, p+n)区间查找 //返回最小秩
    ListNode<T>* find(int n, ListNode<T>* p, T const& t) const; //[p-n, p)区间查找 //返回最大秩
    ListNode<T> *search(int n, ListNode<T>* p, T const& t)const; //有序链表查找
    ListNode<T> *search(T const& t)const{ return search(_size, trailer, t);}//[p - n, p)区间查找 //返回最大秩
    ListNode<T> *find(T const& t){ return find(_size, trailer, t);} //保证秩最大

    //可写接口
    ListNode<T>* insertBefore(ListNode<T> *p,  T const& t); //将t插入到p前面
    ListNode<T>* insertAfter(ListNode<T> *p,  T const& t); //将t插入到p后面
    ListNode<T>* insertAtLast(T const& t){ return insertBefore(trailer, t);} //将t插入到最后面
    ListNode<T>* insertAtFirst(T const& t){ return insertAfter(header, t);} //将t插入到最前面
    ListNode<T>* insert(T const& t){ return insertAtLast(t);} //默认插入到后方
    T remove(ListNode<T> *p);
    int deduplicate(); //前缀比较法去重
    int uniquify(); //有序向量去重
    void traverse( void (*op) (T&)); //遍历 —— 函数指针
    template <typename VST>
    void traverse(VST op); //遍历 —— 函数对象


    //友元
    template <typename VST>
    friend ostream& operator<<(ostream &os, ListOrdered<VST> const &ListOrdered_);

};

//内部成员函数
template <typename T>
void ListOrdered<T>::init(){
    //默认初始化的情况下，链表是空的！！！
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->prev = nullptr; header->next = trailer;
    trailer->prev = header; trailer->next = nullptr;
    _size = 0;
}

template <typename T>
void ListOrdered<T>::copyNodes(ListNode<T> *p, int n){
    init();
    //复制[p, p+n)里的所有节点
    while (n-- > 0){
        insertAtLast(p->data);
        p = p->next;
    }
}

template <typename T>
int ListOrdered<T>::clear(){
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
ListOrdered<T>::ListOrdered() {init();}

template<typename T>
ListOrdered<T>::ListOrdered(ListOrdered<T> const& ListOrdered_){
    copyNodes(ListOrdered_.first(), ListOrdered_.size());
}

template<typename T>
ListOrdered<T>::ListOrdered(ListNode<T> *p, int n){
    copyNodes(p, n);
}

//析构函数
template<typename T>
ListOrdered<T>::~ListOrdered(){
    clear();
    delete header;
    delete trailer;
}

//只读接口
template <typename T>
T& ListOrdered<T>::operator[](Rank r) const{
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
ListNode<T>* ListOrdered<T>::find(ListNode<T>* p, int n, T const& t) const{
    //从前往后查找，能找到最小的秩
    //所以这里的是[p, p + n)区间查找
    while (n-- >= 0){
        if(p->data == t){
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

template <typename T>
ListNode<T>* ListOrdered<T>::find(int n, ListNode<T>* p, T const& t) const{
    //从后往前查找，能找到最大的秩
    //所以这里的是[p - n, p)区间查找
    while(n-- >= 0){
        if((p->prev)->data == t){
            return p->prev;
        }
        p = p->prev;
    }
    return nullptr;
}

template <typename T>
ListNode<T> * ListOrdered<T>::search(int n, ListNode<T>* p, T const& t)const{
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
ListNode<T>* ListOrdered<T>::insertBefore(ListNode<T> *p,  T const& t) {
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
ListNode<T>* ListOrdered<T>::insertAfter(ListNode<T> *p,  T const& t) {
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
T ListOrdered<T>::remove(ListNode<T> *p){
    T t = p->data;
    (p->prev)->next = p->next;
    (p->next)->prev = p->prev;
    delete p;
    _size--;
    return t;
}

template <typename T>
int ListOrdered<T>::deduplicate(){
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
int ListOrdered<T>::uniquify(){
    //有序向量去重
    if(_size < 2){
        return 0;
    }
    int old_size = _size;
    ListNode<T> *tmp = first();
    while(tmp != last()){
        if((tmp->next)->data == tmp->data){
            remove(tmp->next);
        } else{
            tmp = tmp->next;
        }
    }
    return old_size - _size;
}

template <typename T>
void ListOrdered<T>::traverse( void (*op) (T& t)){
    //遍历 —— 函数指针
    ListNode<T> *tmp = first();
    while (tmp != trailer){
        op(tmp->data);
        tmp = tmp->next;
    }
}

template <typename T>
template <typename VST>
void ListOrdered<T>::traverse(VST op){
    //遍历 —— 函数对象
    ListNode<T> *tmp = first();
    while (tmp != trailer){
        op(tmp->data);
        tmp = tmp->next;
    }
}

//友元
template <typename VST>
ostream& operator<<(ostream &os, ListOrdered<VST> const &ListOrdered_){
    ListNode<VST> *tmp = ListOrdered_.first();
    while (tmp != ListOrdered_.trailer){
        os << tmp->data << ", ";
        tmp = tmp->next;
    }
    return os;
}


#endif //CPP_ListOrderedORDERED_H
