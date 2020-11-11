//
// Created by luyao on 2020/11/11.
//

#include "stackTestExample.h"

//示例1：十进制转换
void convert(Stack<char> &S, unsigned int n, int other, string const &s){
    if(s == "iteration"){
        cout << "choose iteration version to convert: ";
        convert_iteration(S, n, other);
    } else{
        cout << "choose recursion version to convert: ";
        convert_recursion(S, n, other);
    }
}

//迭代法版本
void convert_iteration(Stack<char> &S, unsigned int n, int other){
    //S：利用栈进行进制转换
    //n：被转换的十进制数
    //other：转换到其他进制
    char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    //不同进制的符号不完全一样，所以设置了digit char数组方便之后进行处理。
    int tmp = 0;
    while (n != 0){
        tmp = n % other;
        S.push(digit[tmp]);
        n = n / other;
    }
}

//递归法版本
void convert_recursion(Stack<char> &S, unsigned int n, int other){
    //S：利用栈进行进制转换
    //n：被转换的十进制数
    //other：转换到其他进制
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    //为了防止每次递归进来都需要重新定义digit，将该char数组设置为静态static。
    if(n == 0){
        return;
    }
    int tmp = n % other;
    S.push(digit[tmp]);
    n = n / other;
    convert_recursion(S, n, other);
}


bool match_paren(const string&  exp, int lo, int hi){
    Stack<char> stack;
    for(int i = lo; i < hi; i++){
        if(exp[i] == '('){
            stack.push('(');
        }
        if(exp[i] == ')'){
            if(stack.empty() || stack.top() !='('){
                return false;
            } else{
                stack.pop();
            }
        }
    }
    return stack.empty();
}

bool match_paren(const string& exp){
    return match_paren(exp, 0, exp.size());
}
