#include <iostream>
#include "BinTree.h"

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

    return 0;
}