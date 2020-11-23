//
// Created by luyao on 2020/11/21.
//

#ifndef CHAPTER5_TREE_BINSEARCHTREE_H
#define CHAPTER5_TREE_BINSEARCHTREE_H

#include "BinTree.h"

template <typename T>
class BinSearchTree:public BinTree<T>{
protected:
    BinNode<T> *parent_t; //指向t的父节点
public:
    virtual BinNode<T>* & searchIn(const T& t){ return searchIn(this->rootNode, t, parent_t= nullptr);}
    virtual BinNode<T>* & searchIn(BinNode<T>* &curNode, const T& t);
    virtual BinNode<T>* & searchIn(BinNode<T>* &curNode, const T& t, BinNode<T>* &parent_t);
    virtual BinNode<T>* insert(const T& t);

};

//静态查找
template <typename T>
BinNode<T>* & BinSearchTree<T>::searchIn(BinNode<T>* &curNode, const T& t){
    //递归方式
    //基例
    if(!curNode || curNode->data == t){
        return curNode;
    }
    //链条
    if(curNode->data < t){
        curNode = curNode->RNode;
    } else{
        curNode = curNode->LNode;
    }
    searchIn(curNode, t);
}

template <typename T>
BinNode<T>* & BinSearchTree<T>::searchIn(BinNode<T>* &curNode, const T& t, BinNode<T>* &parent_t_){
    //递归方式
    //基例
    if(!curNode || curNode->data == t){
        return curNode;
    }
    //链条
    parent_t_ = curNode;
    if(curNode->data < t){
        searchIn(curNode->RNode, t, parent_t_);
    } else{
        searchIn(curNode->LNode, t, parent_t_);
    }
}

//动态插入
//递归版本一
template <typename T>
BinNode<T>* BinSearchTree<T>::insert(const T& t){
    //算法复杂度O(HEIGHT_OF_TREE)
    BinNode<T>* &wait_for_insert_ = searchIn(t);
    if(wait_for_insert_){
        return wait_for_insert_; //如果树中已经有这个元素了，就不需要进行插入了
    }
    /**
     * 方法一
     */
    /**/
    wait_for_insert_ = new BinNode<T>(t, parent_t);
    this->_size++;
    this->updateHeightAbove(wait_for_insert_);
    return wait_for_insert_;

    /*
     * 方法二
     */
    /*
    if(parent_t->data < t){
        wait_for_insert_ = parent_t->insertAsRNode(t);
    }else{
        wait_for_insert_ = parent_t->insertAsLNode(t);
    }
    this->_size++;
    this->updateHeightAbove(wait_for_insert_);
    return wait_for_insert_;
     */
}


#endif //CHAPTER5_TREE_BINSEARCHTREE_H
