//
// Created by luyao on 2020/11/5.
//

#ifndef CPP_FIB_H
#define CPP_FIB_H

#include <vector>
#include <iostream>
using namespace std;

class Fib{
protected:
    vector<int> fib;
    int _size;
    static int fib_term(int n);
public:
    //构造函数
    explicit Fib(int length = 0);
    //只读
    int get() const ; //获取当前fib[k]
    int get_golden_ratio() const; //获取当前fib数列的黄金分割点，其实就是fib[k-1]项
    //可写
    int prev() ; //获取fib的前一项fib[k-1]，并修改fib数列
    //友元
    friend ostream& operator<<(ostream& os, const Fib& fib);
};

//构造函数
//这个构造复杂度很大，递归n次，时间复杂度O(2^n)
Fib::Fib(int length):_size(length){
    //还可以改进为不小于n的最小fib数列项，减少迭代次数
    //只需要加个if条件，判断满足break即可。
    int fib_value = 0;
    for (int i = 0; i < _size; i++){
        fib_value = fib_term(i);
        fib.push_back(fib_value);
    }
}


//未开放的接口
int Fib::fib_term(int n){
    if (n == 0){
        return 0;
    }else if (n == 1){
        return 1;
    }else{
        return fib_term(n-1) + fib_term( n-2);
    }
}


//只读接口
int Fib::get() const {
    return fib[_size-1];
}
int Fib::get_golden_ratio() const{
    if(_size == 1){
        return 0;
    } else{
        return fib[_size - 2];
    }
}

//可写接口
int Fib::prev(){
    fib.erase(fib.end()-1);
    _size -= 1;
    return _size;
};


//友元
ostream& operator<<(ostream& os, const Fib& fib){
    for(int begin : fib.fib){
        os << begin << ", ";
    }
    return os;
}

#endif //CPP_FIB_H
