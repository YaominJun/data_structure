//
// Created by luyao on 2020/11/19.
//

#ifndef CHAPTER5_TREE_BINNODE_H
#define CHAPTER5_TREE_BINNODE_H

template <typename T> struct BinNode{
public:
    //数据成员：主要是自身数据，左子树节点，右子树节点
    T data;
    BinNode<T> *LNode, *RNode;
    BinNode<T> *parent;
    int height;

    //构造函数
    BinNode(); //默认初始化
    BinNode(BinNode const& binNode); //拷贝初始化
    BinNode(T t,  BinNode<T> *pNode = nullptr, BinNode<T> *lNode = nullptr, BinNode<T> *rNode = nullptr, int h = 0);

    //函数接口
    //只读接口
    BinNode<T>* insertAsLNode(T const& t);
    BinNode<T>* insertAsRNode(T const& t);

};

template <typename T>
BinNode<T>::BinNode():
        LNode(nullptr), RNode(nullptr), parent(nullptr){
}

template <typename T>
BinNode<T>::BinNode(BinNode const& binNode){
    data = binNode.data;
    LNode = binNode.LNode;
    RNode = binNode.RNode;
    parent = binNode.parent;
    height = binNode.height;
}

template <typename T>
BinNode<T>::BinNode(T t, BinNode<T> *pNode, BinNode<T> *lNode, BinNode<T> *rNode, int h):
        data(t), LNode(lNode), RNode(rNode), parent(pNode), height(h){
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsLNode(T const& t){
    LNode = new BinNode<T>(t, this); //数据是t，而父节点parent是this指针
    return LNode;
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRNode(T const& t){
    RNode = new BinNode<T>(t, this);
    return RNode;
}



#endif //CHAPTER5_TREE_BINNODE_H
