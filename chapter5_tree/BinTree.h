//
// Created by luyao on 2020/11/19.
//

#ifndef CHAPTER5_TREE_BINTREE_H
#define CHAPTER5_TREE_BINTREE_H

#include "BinNode.h"

template <typename T>
class BinTree{
protected:
    //数据成员
    BinNode<T> *rootNode;
    virtual int updateHeight(BinNode<T> *curNode);
    //定义为虚函数的原因是：因为二叉树有很多派生类，如二叉搜索树、堆等，而这些树的高度可能定义或更新方法不完全一致，所以采用虚函数。
    //以便实现多态。

public:
    //函数接口
    //只读接口
    bool empty(){ return !rootNode;}
    //可写接口

};


#endif //CHAPTER5_TREE_BINTREE_H
