//
// Created by luyao on 2020/11/6.
//

#ifndef CPP_LISTNODE_H
#define CPP_LISTNODE_H
using namespace std;

template <typename T>
struct ListNode{
public:
    //变量成员
    T data;
    ListNode<T> *prev;
    ListNode<T> *next;

    //构造函数
    ListNode(){} //首节点和末尾节点
    ListNode(ListNode<T> *prev_, ListNode<T> *next_, T t_)
        :prev(prev_), next(next_), data(t_){} //中间节点
    //只读接口
    //可写接口
    ListNode<T>& operator=(ListNode<T> const& listnode_){
        data = listnode_.data;
        prev = listnode_.prev;
        next = listnode_.prev;
    }
};

#endif //CPP_LISTNODE_H
