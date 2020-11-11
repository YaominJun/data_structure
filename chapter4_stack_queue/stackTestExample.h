//
// Created by luyao on 2020/11/11.
//

#ifndef CHAPTER4_STACK_QUEUE_STACKTESTEXAMPLE_H
#define CHAPTER4_STACK_QUEUE_STACKTESTEXAMPLE_H

#include "Stack.h"
//示例1：十进制转换
void convert(Stack<char> &S, unsigned int n, int other, string const &s = "iteration");
//选择迭代法iteration或递归法recursion不同版本的进制转换算法
void convert_iteration(Stack<char> &S, unsigned int n, int other); //迭代法iteration版本
void convert_recursion(Stack<char> &S, unsigned int n, int other); //递归法recursion版本

//示例2：括号匹配
bool match_paren(const string&  exp, int lo, int hi);
bool match_paren(const string&  exp);
//单const 参数的必&须写在多参数的下面，不然找不到多参数的函数。

#endif //CHAPTER4_STACK_QUEUE_STACKTESTEXAMPLE_H
