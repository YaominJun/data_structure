//
// Created by luyao on 2020/11/21.
//

#ifndef CHAPTER5_TREE_BALANCEDBST_H
#define CHAPTER5_TREE_BALANCEDBST_H

#include "BinSearchTree.h"

template <typename T>
class AVL:public BinSearchTree<T>{
protected:
    BinNode<T>* connect3plus4(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
                                BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
    BinNode<T>* rotateAt(BinNode<T>* v);
    bool isLChild(const T& t); //判断v是不是在其父节点的左子树上
    bool isRChild(const T& t); //判断v是不是在其父节点的右子树上

    int balanceFactor(BinNode<T> *node){ return node->LNode->getHeight() - node->RNode->getHeight();}
    bool avlBalanced(BinNode<T> *node){ return ((-2 < balanceFactor(node)) && (balanceFactor(node) < 2));}
    BinNode<T>* & tallerChild(BinNode<T>* pr){ return (pr->LNode->getHeight() > pr->RNode->getHeight())? pr->LNode : pr->RNode;}
    BinNode<T>* & fromParentTo(BinNode<T> *pr){ return pr->parent;}

public:
    BinNode<T>* insert(const T& t);
    bool remove(const T& t);
};

template <typename T>
BinNode<T>* AVL<T>::insert(const T& t){
    BinNode<T>* &x = this->searchIn(t);
    if(x){ return x;} //只有当t不在树中时，才需要插入
    BinNode<T>* xx = new BinNode<T>(t, this->parent_t); this->_size++;
    //添加新节点
    for(BinNode<T>* gr = this->parent_t; gr; gr = gr->parent){
        if(!avlBalanced(gr)){
            fromParentTo(gr) = rotateAt(tallerChild(tallerChild(gr)));
            break; //插入只需要保证被破坏平衡的祖孙三代恢复平衡即可
        } else{
            updateHeight(gr);
        }
    }
    return xx;
}

template <typename T>
bool AVL<T>::remove(const T& t){
    BinNode<T>* &x = this->searchIn(t);
    if(!x){ return false;} //当t不在树中时，不能删除，则说明删除错误
    /**
     * 待做
     */

}

template <typename T>
BinNode<T>* AVL<T>::connect3plus4(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
                                  BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3){
    a->LNode = T0;
    if(T0){T0->parent = a;}
    a->RNode = T1;
    if(T1){T1->parent = a;}
    this->updateHeight(a);
    c->LNode = T2;
    if(T2){T2->parent = c;}
    c->RNode = T3;
    if(T3){T3->parent = c;}
    this->updateHeight(b);

    b->LNode = a;
    b->RNode = c;
    this->updateHeight(b);
    return b;
}

template <typename T>
BinNode<T>* AVL<T>::rotateAt(BinNode<T>* v){
    BinNode<T>* pr = v->parent;
    BinNode<T>* gr = pr->parent;
    if(isLChild(v->data)){
        if(isLChild(pr->data)){
            //LL 旋转模式，则需要顺时针转zigzig
            //也可以直接从拆开合并的直接法思路考虑，它们恢复平衡后的大小排列顺序肯定还是不能变
            //既然v是pr的左子树，那么v < pr；pr是gr的左子树，那么 pr < gr。
            //重新排列后也需要按照这样的次序。
            //不仅如此，此时pr到中间了，所以pr的parent也要和之前的这一块的parent对应上。
            pr->parent = gr->parent;
            return connect3plus4(v, pr, gr, v->LNode, v->RNode, pr->RNode, gr->RNode);
        }else{
            //RL 旋转模式，则需要顺时针再逆时针zigzag
            //也可以直接从拆开合并的直接法思路考虑，它们恢复平衡后的大小排列顺序肯定还是不能变
            //既然v是pr的左子树，那么v < pr；pr是gr的右子树，那么 gr < v < pr；
            //重新排列后也需要按照这样的次序。
            //不仅如此，此时v到中间了，所以v的parent也要和之前的这一块的parent对应上。
            v->parent = gr->parent;
            return connect3plus4(gr, v, pr, gr->LNode, v->LNode, v->RNode, pr->RNode);
        }
    }else{
        if(isLChild(pr->data)){
            //可以直接从拆开合并的直接法思路考虑，它们恢复平衡后的大小排列顺序肯定还是不能变
            //既然v是pr的右子树，那么pr < v；pr是gr的左子树，那么pr < v < gr；
            //重新排列后也需要按照这样的次序。
            //不仅如此，此时v到中间了，所以v的parent也要和之前的这一块的parent对应上。
            v->parent = gr->parent;
            return connect3plus4(pr, v, gr, pr->LNode, v->LNode, v->RNode, gr->RNode);
        } else{
            //可以直接从拆开合并的直接法思路考虑，它们恢复平衡后的大小排列顺序肯定还是不能变
            //既然v是pr的右子树，那么pr < v；pr是gr的右子树，那么gr < pr < v；
            //重新排列后也需要按照这样的次序。
            //不仅如此，此时pr到中间了，所以pr的parent也要和之前的这一块的parent对应上。
            pr->parent = gr->parent;
            return connect3plus4(gr, pr, v, gr->LNode, pr->LNode, v->LNode, v->RNode);
        }
    }
}

template <typename T>
bool AVL<T>::isLChild(const T& t){
    if(t == v->parent->LNode->data){
        return true;
    }
    return false;
}

template <typename T>
bool AVL<T>::isRChild(const T& t){
    if(t == v->parent->RNode->data){
        return true;
    }
    return false;
}

#endif //CHAPTER5_TREE_BALANCEDBST_H
