#include <iostream>
#include "BinTree.h"
#include "BinSearchTree.h"

int main() {
    BinTree<int> binTree1;
    binTree1.insertAsRoot(3);
    binTree1.insertAsLChild(binTree1.root(), 4);
    binTree1.insertAsRChild(binTree1.root(), 5);
    //递归版
    //先序遍历
    binTree1.traversePre_R(binTree1.root());
    std::cout << std::endl;
    //中序遍历
    binTree1.traverseMid_R(binTree1.root());
    std::cout << std::endl;
    //后序遍历
    binTree1.traverseLast_R(binTree1.root());
    std::cout << std::endl;

    //迭代版版本一
    //尾递归 -> 迭代方式
    //先序遍历
    binTree1.traversePre_version1(binTree1.root());
    std::cout << std::endl;

    //迭代版版本二
    //观察特征 -> 迭代方式
    binTree1.traversePre(binTree1.root());
    std::cout << std::endl;

    /**
     * binary search tree test
     */
    BinSearchTree<int>* binTree_ptr = new BinSearchTree<int>;
    binTree_ptr->insertAsRoot(4);
    binTree_ptr->insertAsLChild(binTree_ptr->root(), 3);
    binTree_ptr->insertAsRChild(binTree_ptr->root(),5);

    BinNode<int> *root_ = binTree_ptr->root();
    int num_find = 1;
    if(binTree_ptr->searchIn(root_,num_find) != nullptr){
        std::cout << "find the number: " << binTree_ptr->searchIn(root_,num_find)->data << std::endl;
    }else{
        std::cout << "not found! " << std::endl;
    }

    std::cout << "binTree_ptr->size(): " << binTree_ptr->size() << std::endl;
    binTree_ptr->insert(6);
    //先序遍历
    binTree_ptr->traversePre_R(binTree_ptr->root());
    std::cout << std::endl;
    //中序遍历【正好是顺序】
    binTree_ptr->traverseMid_R(binTree_ptr->root());
    std::cout << std::endl;
    std::cout << "binTree_ptr->size(): " << binTree_ptr->size() << std::endl;

    return 0;
}