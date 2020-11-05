//
// Created by luyao on 2020/11/3.
//

#ifndef CPP_VECTOR_DSA_ORDERED_H
#define CPP_VECTOR_DSA_ORDERED_H

#include <iostream>
#include "append_class.h"
#include "fibonacci/fib.h"
using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>
class VectorDsaOrdered{
protected:
    Rank _size; int _capacity; T* _elem;
    void copyFrom(T const *A, Rank lo, Rank hi);
    void expand();
public:
    //构造函数【可多个】
    explicit VectorDsaOrdered(int c = DEFAULT_CAPACITY, int num = 0, T v = 0);
    VectorDsaOrdered( T const *A, Rank n){copyFrom(A, 0, n);}
    VectorDsaOrdered( T const *A, Rank lo, Rank hi){copyFrom(A, lo, hi);}
    VectorDsaOrdered( VectorDsaOrdered<T> const &V){copyFrom(V._elem, 0, V._size);}
    VectorDsaOrdered( VectorDsaOrdered<T> const &V, Rank lo, Rank hi){copyFrom(V._elem, lo, hi);}
    //析构函数【单个】
    ~VectorDsaOrdered(){delete [] _elem;}

    //只读访问接口
    Rank size()const { return _size;}
    Rank find(Rank b, Rank e, T const &t); //返回相等元素的最大的秩，所以用的反向查找
    Rank find(T const &t){ return find(0, _size, t);} //先写区间的，再写单独元素的，原因和删除一样。
    Rank search(Rank b, Rank e, T const &t);
    Rank search(T const &t){ return (0 >= _size)? -1 : search(0, _size, t);}
    Rank binsearch(Rank b, Rank e, T const &t);
    Rank binsearch_improve(Rank b, Rank e, T const &t);
    Rank binsearch_return_rule(Rank b, Rank e, T const &t);
    Rank fibsearch(Rank b, Rank e, T const &t);
    int disordered() const;

    //可写访问接口
    T &operator[](Rank n){ return _elem[n];}
    const T&operator[](Rank n) const{ return _elem[n];}
    //=赋值运算符重载
    VectorDsaOrdered& operator=(VectorDsaOrdered<T> const &V);
    Rank insert(Rank r, T const &t);
    Rank insert(T const &t){return insert(_size, t);} //默认插入末尾
    //区间删除
    int remove(Rank b, Rank e);
    //单元素删除
    T remove(Rank r);
    //无序去重
    int deduplicate();
    int uniquify();
    void traverse(void (*op) (T&)); //函数指针 //本质上可以实现可写或只读
    template<typename VST> void traverse(VST op); //函数对象

    //友元
    template <typename VST> friend  ostream & operator<<(ostream &os, VectorDsaOrdered<VST> V);

};

//构造函数
template<typename T>
VectorDsaOrdered<T>::VectorDsaOrdered(int c, int num, T v) {
    _capacity = c;
    _elem = new T[_capacity];
    for (_size = 0; _size < num ; _size++){
        _elem[_size] = v;
    }
}

//内部protected成员函数
template <typename T>
void VectorDsaOrdered<T>::copyFrom(T const *A, Rank lo, Rank hi){
    _capacity = 2*(hi - lo); //2倍拷贝区间的容量，有一定的预留空间
    _elem = new T[_capacity];
    _size = 0;
    for (; lo < hi; lo++, _size++){
        _elem[_size] = A[lo];
    }
}

template <typename T>
void VectorDsaOrdered<T>::expand() {
    //扩容算法
    if (_size < _capacity){ return;}
    _capacity = max(_capacity, DEFAULT_CAPACITY);
    T *old_elem = _elem;
    _elem = new T[_capacity <<= 1]; //扩大2倍
    for (Rank i = 0; i < _size; i++){
        _elem[i] = old_elem[i];
    }
    delete [] old_elem;
}


//只读访问接口
template <typename T>
Rank VectorDsaOrdered<T>::find(Rank b, Rank e,T const &t){
    if(e <= b){ //不能用 e-- < b，因为在这个操作过程中就已经把e减一操作了！！！
        return -1;
    }
    while((e-- > b) && _elem[e] != t);
    return e;
}

template <typename T>
Rank VectorDsaOrdered<T>::search(Rank b, Rank e, T const &t){
    //随机选取一种排序方法
    Rank i = 0;
    switch(rand() % 4){
        case 0: i = binsearch(b, e, t);
            cout << "choose binsearch: ";
            break;
        case 1: i = binsearch_improve(b, e, t);
            cout << "choose binsearch_improve: ";
            break;
        case 2: i = binsearch_return_rule(b, e, t);
            cout << "choose binsearch_return_rule: ";
            break;
        case 3: i = fibsearch(b, e, t);
            cout << "choose fibsearch: ";
            break;
    }
    return i;
}


template <typename T>
Rank VectorDsaOrdered<T>::binsearch(Rank b, Rank e, T const &t){
    //二分搜索
    Rank low = b, high = e;
    while (low < high){
        Rank middle = (low + high) >> 1;
        //(low + high) >> 1，右移一位表示减少为1/2。位操作一般会比乘除法 (low + high) /2 运算效率高
        if(t < _elem[middle]){
            //用 < 比大于号>更合适的原因是：小于号<是顺着看的实现过去的，相当于能直接说t在_elem[middle]的左侧
            high = middle;
            //查找区间[high, middle)。
        }else if(_elem[middle] < t){
            low = middle+ 1; //前面high = middle;不需要+1的原因是查找区间是左闭右开[high, middle)。
            //查找区间是[middle+1, high)
        }else{
            return middle;
        }
    }
    return -1;
}

template <typename T>
Rank VectorDsaOrdered<T>::binsearch_improve(Rank b, Rank e, T const &t){
    //二分支的二分搜索
    //最坏情况的复杂度变好
    //最好情况的复杂度变坏
    Rank low = b, high = e;
    while (high - low > 1){
        //否则low = high = middle = 0的时候算法无法退出
        Rank middle = (low + high) >> 1;
        //也可以用(low + high) >> 1，右移一位表示减少为1/2。位操作一般会比乘除法运算效率高
        if(t < _elem[middle]){
            //用 < 比大于号>更合适的原因是：小于号<是顺着看的实现过去的，相当于能直接说t在_elem[middle]的左侧
            high = middle;
            //high = middle;不需要+1的原因是查找区间是左闭右开[high, middle)。
            //查找区间[high, middle)。
        }else {
            low = middle;
            //improve的地方：low = middle;不进行+1，从而只有两分支。该分支包含了轴点，即 t == _elem[middle]的情况。
            //查找区间是[middle, high)
        }
    }
    if (_elem[low] == t){
        //轴点的比对放到最后。之前是三分支，现在是二分支版本。
        return low;
    } else{
        return -1;
    }
}

template <typename T>
Rank VectorDsaOrdered<T>::binsearch_return_rule(Rank b, Rank e, T const &t) {
    //满足相应语义规定的二分搜索
    //如果能找到，就返回最高优先级（最大秩）的元素的秩
    //如果找不到，就返回边界low-1，以便插入【除非low = b不要随意插入外，其他情况插入都不会有问题】
    Rank low = b, high = e;
    while (low < high) {
        Rank middle = (low + high) >> 1;
        //(low + high) >> 1，右移一位表示减少为1/2。位操作一般会比乘除法 (low + high) /2 运算效率高
        if (t < _elem[middle]) {
            //用 < 比大于号>更合适的原因是：小于号<是顺着看的实现过去的，相当于能直接说t在_elem[middle]的左侧
            high = middle;
            //查找区间[high, middle)。
        } else {
            low = middle + 1; //前面high = middle;不需要+1的原因是查找区间是左闭右开[high, middle)。
            //查找区间是[middle+1, high)
        }
    }
    //看似少比较了或漏掉了middle，但其实通过return --low;能够保证不会漏掉，且满足语义规定要求。
    return --low;
}

template <typename T>
Rank VectorDsaOrdered<T>::fibsearch(Rank b, Rank e, T const &t){
    //斐波那契数列查找
    Rank low = b, high = e;
    Fib fib(high - low);
    while (low < high){
        //找到对应当前high - low的最靠近的fib[k]，但是不一定能保证fib[k]-1 == high - low
        while(high - low < fib.get_golden_ratio()){
            fib.prev();
        }
        Rank middle = low + fib.get_golden_ratio() - 1;
        if(t < _elem[middle]){
            //用 < 比大于号>更合适的原因是：小于号<是顺着看的实现过去的，相当于能直接说t在_elem[middle]的左侧
            high = middle;
        }else if(_elem[middle] < t){
            low = middle+ 1; //前面high = middle;不需要+1的原因是查找区间是左闭右开[high, middle)。
        }else{
            return middle;
        }
    }
    return -1;
}


template <typename T>
int VectorDsaOrdered<T>::disordered() const{
    int sum = 0;
    for(Rank i = 1; i < _size; i++){
        if(_elem[i] > _elem[i-1]){
            sum++;
        }
    }
    return sum;
}


//可写访问接口
template <typename T>
VectorDsaOrdered<T>& VectorDsaOrdered<T>:: operator=(VectorDsaOrdered<T> const &V){
    if(_elem){
        delete [] _elem;
    }
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
Rank VectorDsaOrdered<T>::insert(Rank r, T const &t){
    expand();
    //是否扩容在expand函数里面已经有判断了，所以直接调用expand()即可，不需要再做额外的判断。
    //expand()里面的判断是_size < _capacity，即如果_size已经等于_capacity了，也会扩容
    //所以能保证还能再插入一个元素。
    for (Rank i = _size; i > r; i--){
        _elem[i] = _elem[i-1];
        //注意不是_elem[i+1] = _elem[i];
        // 因为是从0开始计数的，所以移动的是 [r, size)区间的数。
    }
    _elem[r] = t;
    return r;
}

template <typename T>
int VectorDsaOrdered<T>::remove(Rank b, Rank e){

    if(b == e) {return 0;}
    for(; e < _size; b++, e++){
        _elem[b] = _elem[e];
    }
    _size = b; //因为b也在增加
    return e-b;
}

template <typename T>
T VectorDsaOrdered<T>::remove(Rank r){
    //相当于是删除区间[r,r+1)之间的值
    T e = _elem[r];
    remove(r, r+1);
//    _size -= 1; //不用进行这个操作了，因为在remove(b,e)中已经实现了。
    return e;
    //返回被删除的元素值
}

template <typename T>
int VectorDsaOrdered<T>::deduplicate(){
    //无序容器的去重版本
    Rank old_size = _size;
    Rank i = 1;
    while (i < _size){
        if(find(0, i, _elem[i]) > 0){
            remove(i);
            //remove了之后就不用i++了，因为会该后方的所有元素会相应地往前挪一个位置
        }else{
            i++;
        }
    }
    return _size - old_size;
}

/*
//低效版本的去重
 //时间复杂度O(N^2)
template <typename T>
int VectorDsaOrdered<T>::uniquify(){
    //有序容器的去重版本
    Rank old_size = _size;
    Rank i = 1;
    while (i < _size){
        if(_elem[i] == _elem[i-1]){
            remove(i);
        }else{
            i++;
        }
    }
    return old_size - _size;
}
*/

//高效版
//时间复杂度O(N)
template <typename T>
int VectorDsaOrdered<T>::uniquify() {
    Rank old_size = _size;
    Rank i = 0, j = 1;
    while (j < _size) {
        if(_elem[j] != _elem[i]){
            _elem[i++] = _elem[j];
        }
        j++;
    }
    _size = i++; //因为是从0开始计数
    return old_size - _size;
}

template <typename T>
void VectorDsaOrdered<T>::traverse(void (*op) (T&)){
    for(Rank i = 0; i < _size; i++){
        op(_elem[i]);
    }
}

template <typename T>
template<typename VST> void VectorDsaOrdered<T>::traverse(VST op){
    for(Rank i = 0; i < _size; i++){
        op(_elem[i]);
    }
}


//友元
template <typename VST>  ostream & operator<<(ostream &os, VectorDsaOrdered<VST> V){
    for (Rank i = 0; i < V._size; i++){
        os << V._elem[i] << ",";
    }
    return os;
}

//非类成员函数
template <typename T> void increase(VectorDsaOrdered<T> &V){
    V.traverse(Increase<T>());
}


#endif //CPP_VECTOR_DSA_ORDERED_H
