//
// Created by luyao on 2021/1/14.
//

#ifndef CHAPTER2_RECURSION_HANOI_H
#define CHAPTER2_RECURSION_HANOI_H

/**
 * 中国慕课网
 * 程序设计算法(二)
 * 示例2：汉罗塔问题
 */

#include <iostream>

using namespace std;

namespace exam2{
class Solution{
public:
    void hanoi(int n, char left, char middle, char right){
        string message;
        if(n == 1){
            std::cout << left << "->" << right << std::endl;
        }else{
            hanoi(n-1, left, right, middle);
            std::cout << left << "->" << right << std::endl;
            hanoi(n-1, middle, left, right);
        }
    }
};
}

#endif //CHAPTER2_RECURSION_HANOI_H
