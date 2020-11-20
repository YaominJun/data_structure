//
// Created by luyao on 2020/11/19.
//

#ifndef CHAPTER5_TREE_BINTREE_H
#define CHAPTER5_TREE_BINTREE_H

#include "BinNode.h"
#include <stack>
/**
 * BinTree class
 */

template <typename T>
class BinTree{
protected:
    //数据成员
    BinNode<T> *rootNode;
    int _size;

    //函数成员
    //树中各节点高度更新
    virtual int updateHeight(BinNode<T> *curNode);
    //更新某个节点的高度
    //定义为虚函数的原因是：因为二叉树有很多派生类，如二叉搜索树、堆等，而这些树的高度可能定义或更新方法不完全一致，所以采用虚函数。
    //以便实现多态。
    void updateHeightAbove(BinNode<T> *curNode);
    //更新当前节点往上所有节点的高度。
    //注意这里只用更新当前节点往上above的祖先节点的高度，其下面的节点高度不会因为当前节点的改变而改变。
    //原因是：高度的定义是根节点到所有叶节点中高度最大的那个。而改变的是curNode，没有改变curNode下面的节点，所以不会对其产生影响。
    //同时，也正因为如此，curNode的改变（插入或删除）会对其上方的节点高度产生影响（也可能不影响，因为高度是取的最大值/最长路径）。
    void visitAlongLeftBranch(BinNode<T> *curNode, std::stack<BinNode<T>*> &stack_);
    //千万要注意这里必须有引用，不然stack_在函数进入和退出之间就是临时变量！！！


public:
    //构造函数和析构函数
    BinTree():rootNode(nullptr), _size(0){}
    ~BinTree() = default;

    //函数接口
    //只读接口
    bool empty()const { return !rootNode;}
    int size(){ return _size;}
    BinNode<T>* root()const { return rootNode;}
    //可写接口
    BinNode<T>* insertAsRoot(T const& t);
    BinNode<T>* insertAsLChild(BinNode<T>* curNode, T const& t);
    BinNode<T>* insertAsRChild(BinNode<T>* curNode, T const& t);

    //！！！遍历【这是树中非常关键和重要的操作】！！！
    //遍历包括访问式地和修改式的。
    //这里只提供访问式的cout打印，而修改式的可以将函数指针或函数对象作为输入参数，对每个遍历的节点进行操作即可。

    //实现方式包括递归式和迭代式。为了降低空间复杂度，最好是选择迭代式。
    // 以下XXX_R是递归式；XXX是迭代式。
    //递归式
    //先序遍历
    void traversePre_R(BinNode<T> *curNode); //对curNode节点为根节点的子树进行遍历（包括curNode）
    //中序遍历
    void traverseMid_R(BinNode<T> *curNode); //对curNode节点为根节点的子树进行遍历（包括curNode）
    //后序遍历
    void traverseLast_R(BinNode<T> *curNode); //对curNode节点为根节点的子树进行遍历（包括curNode）
    //迭代式
    //先序遍历
    void traversePre_version1(BinNode<T> *curNode); //尾递归模式下，采用辅助栈方式
    // 对curNode节点为根节点的子树进行遍历（包括curNode）
    void traversePre(BinNode<T> *curNode); //对curNode节点为根节点的子树进行遍历（包括curNode）
    //中序遍历
    void traverseMid(BinNode<T> *curNode); //对curNode节点为根节点的子树进行遍历（包括curNode）
    //后序遍历
    void traverseLast(BinNode<T> *curNode); //对curNode节点为根节点的子树进行遍历（包括curNode）

};

//只读接口
template <typename T>
int BinTree<T>::updateHeight(BinNode<T> *curNode) {
    int LHeight = -1, RHeight = -1;
    if(curNode->LNode){
        LHeight = curNode->LNode->getHeight();
    }
    if(curNode->RNode){
        RHeight = curNode->RNode->getHeight();
    }
    curNode->height = 1 + std::max(LHeight, RHeight);
    return curNode->height;
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *curNode){
    while (curNode != nullptr){
        updateHeight(curNode);
        curNode = curNode->parent;
    }
}

//可写接口
template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& t){
    //插入根节点，说明原本是空树。
    //所以现在_size规模就是1
    //而根节点此时没有子节点，高度为0，这在new该BinNode的时候就已经实现了。
    _size = 1;
    rootNode = new BinNode<T>(t);
    return rootNode;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsLChild(BinNode<T>* curNode, T const& t){
    //注意：插入的时候不仅仅是插入node，还要考虑相应的size和节点height的更新。
    //这样的新添加元素作为高度或规模或最大值或最小值的度量，非常方便之后获取信息
    //而不用遍历树来得到结果
    curNode->insertAsLNode(t);
    _size++;
    updateHeightAbove(curNode); //新插入节点的height不需要更新，因为新插入节点没有子节点，height本身就是0。
    return curNode->LNode;
}
template <typename T>
BinNode<T>* BinTree<T>::insertAsRChild(BinNode<T>* curNode, T const& t){
    curNode->insertAsRNode(t);
    _size++;
    updateHeightAbove(curNode); //新插入节点的height不需要更新，因为新插入节点没有子节点，height本身就是0。
    return curNode->RNode;
}

//递归版本
template <typename T>
void BinTree<T>::traversePre_R(BinNode<T> *curNode){
    //先序遍历
    //时间复杂度：O(N)【渐进】。
    if(!curNode){
        return;
    }
    std::cout << curNode->data << ", ";
    traversePre_R(curNode->LNode);
    traversePre_R(curNode->RNode);
}

template <typename T>
void BinTree<T>::traverseMid_R(BinNode<T> *curNode){
    //中序遍历
    //时间复杂度：O(N)【渐进】。
    if(!curNode){
        return;
    }
    traverseMid_R(curNode->LNode);
    std::cout << curNode->data << ", ";
    traverseMid_R(curNode->RNode);
}

template <typename T>
void BinTree<T>::traverseLast_R(BinNode<T> *curNode){
    //后序遍历
    //时间复杂度：O(N)【渐进】。
    if(!curNode){
        return;
    }
    traverseLast_R(curNode->LNode);
    traverseLast_R(curNode->RNode);
    std::cout << curNode->data << ", ";
}

//迭代版本一
template <typename T>
void BinTree<T>::traversePre_version1(BinNode<T> *curNode){
    //先序遍历
    //尾递归，可以采用辅助栈方式化为迭代版本。但这里只有先序遍历几乎满足尾递归格式的要求。
    std::stack<BinNode<T>*> stack_;
    if(curNode){
        stack_.push(curNode);
    }
    while (!stack_.empty()){
        //注意这里压入栈中的顺序
        curNode = stack_.top();
        stack_.pop();
        std::cout << curNode->data << ", ";
        if(curNode->RNode){stack_.push(curNode->RNode);}
        if(curNode->LNode){stack_.push(curNode->LNode);}
    }
} //对curNode节点为根节点的子树进行遍历（包括curNode）

//迭代版本二
//先序遍历
template <typename T>
void BinTree<T>::traversePre(BinNode<T> *curNode){
    std::stack<BinNode<T>*> stack_;
    while (true){
        visitAlongLeftBranch(curNode, stack_);
        if(stack_.empty()){
            //这个终止while的命令只能放在这，因为最开始stack_是空的，没法作为while里的判断条件。
            break;
        }
        curNode = stack_.top();
        stack_.pop();
    }
} //对curNode节点为根节点的子树进行遍历（包括curNode）

template <typename T>
void BinTree<T>::visitAlongLeftBranch(BinNode<T> *curNode, std::stack<BinNode<T>*> &stack_){
    //千万要注意这里必须有引用，不然stack_在函数进入和退出之间就是临时变量！！！
    while (curNode){
        std::cout << curNode->data <<", ";
        if(curNode->RNode){stack_.push(curNode->RNode);}
        curNode = curNode->LNode;
    }
}

//中序遍历
template <typename T>
void BinTree<T>::traverseMid(BinNode<T> *curNode){

} //对curNode节点为根节点的子树进行遍历（包括curNode）


#endif //CHAPTER5_TREE_BINTREE_H
