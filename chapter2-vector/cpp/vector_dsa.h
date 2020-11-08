//
// Created by luyao on 2020/10/12.
//

#ifndef CPP_VECTOR_DSA_H
#define CPP_VECTOR_DSA_H

#include <iostream>
#include "append_class.h"
using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T>
class VectorDsa {
protected:
    Rank _size; int _capacity; T* _elem;
    void copyFrom(T const *A, Rank lo, Rank hi);
    void expand();
    /*
    //起泡排序版本一
    bool bubble(Rank low, Rank high);
     */
    //起泡排序版本二
    Rank bubble(Rank low, Rank high);
    //归并排序
    void merge(Rank low, Rank middle, Rank high);

public:
    //构造函数【可多个】
    explicit VectorDsa(int c = DEFAULT_CAPACITY, int num = 0, T v = 0);
    VectorDsa( T const *A, Rank n){copyFrom(A, 0, n);}
    VectorDsa( T const *A, Rank lo, Rank hi){copyFrom(A, lo, hi);}
    VectorDsa( VectorDsa<T> const &V){copyFrom(V._elem, 0, V._size);}
    VectorDsa( VectorDsa<T> const &V, Rank lo, Rank hi){copyFrom(V._elem, lo, hi);}
    //析构函数【单个】
    ~VectorDsa(){delete [] _elem;}

    //只读访问接口
    Rank size()const { return _size;}
    Rank find(Rank b, Rank e,T const &t); //返回相等元素的最大的秩，所以用的反向查找
    Rank find(T const &t){ return find(0, _size, t);} //先写区间的，再写单独元素的，原因和删除一样。
    int disordered() const;

    //可写访问接口
    T &operator[](Rank n){ return _elem[n];}
    const T&operator[](Rank n) const{ return _elem[n];}
    //=赋值运算符重载
    VectorDsa& operator=(VectorDsa<T> const &V);
    Rank insert(Rank r, T const &t);
    Rank insert(T const &t){return insert(_size, t);} //默认插入末尾
    //区间删除
    int remove(Rank b, Rank e);
    //单元素删除
    T remove(Rank r);
    //无序去重
    int deduplicate();
    void traverse(void (*op) (T&)); //函数指针 //本质上可以实现可写或只读
    template<typename VST> void traverse(VST op); //函数对象
    //排序算法
    void bubbleSort(Rank b, Rank e); //起泡排序
    void bubbleSort(){bubbleSort(0, _size);}
    void mergeSort(Rank b, Rank e); //归并排序
    void mergeSort(){mergeSort(0, _size);}

    //友元
    template <typename VST> friend  ostream & operator<<(ostream &os, VectorDsa<VST> V);
    /*
    friend ostream & operator<<(ostream &os, VectorDsa<T> V){
        for (Rank i = 0; i < V._size; i++){
            os << V._elem[i] << ",";
        }
        return os;
    }
    */
};

//构造函数
template<typename T>
VectorDsa<T>::VectorDsa(int c, int num, T v) {
    _capacity = c;
    _elem = new T[_capacity];
    for (_size = 0; _size < num ; _size++){
        _elem[_size] = v;
    }
}

//内部protected成员函数
template <typename T>
void VectorDsa<T>::copyFrom(T const *A, Rank lo, Rank hi){
    _capacity = 2*(hi - lo); //2倍拷贝区间的容量，有一定的预留空间
    _elem = new T[_capacity];
    _size = 0;
    for (; lo < hi; lo++, _size++){
        _elem[_size] = A[lo];
    }
}

template <typename T>
void VectorDsa<T>::expand() {
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
Rank VectorDsa<T>::find(Rank b, Rank e,T const &t){
    if(e <= b){ //不能用 e-- < b，因为在这个操作过程中就已经把e减一操作了！！！
        return -1;
    }
    while((e-- > b) && _elem[e] != t);
    return e;
}

template <typename T>
int VectorDsa<T>::disordered() const{
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
VectorDsa<T>& VectorDsa<T>:: operator=(VectorDsa<T> const &V){
    if(_elem){
        delete [] _elem;
    }
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
Rank VectorDsa<T>::insert(Rank r, T const &t){
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
int VectorDsa<T>::remove(Rank b, Rank e){
    /*
     * //方法一
    if(b == e) {return 0;}
    int len_delete = e-b;
    for (Rank i = e; i < _size; i++, b++){
        _elem[b] = _elem[i];
    }
    _size -= len_delete;
    return len_delete;
     */

    //方法二
    if(b == e) {return 0;}
    for(; e < _size; b++, e++){
        _elem[b] = _elem[e];
    }
    _size = b; //因为b也在增加
    return e-b;
}

template <typename T>
T VectorDsa<T>::remove(Rank r){
    //相当于是删除区间[r,r+1)之间的值
    T e = _elem[r];
    remove(r, r+1);
//    _size -= 1; //不用进行这个操作了，因为在remove(b,e)中已经实现了。
    return e;
    //返回被删除的元素值
}

template <typename T>
int VectorDsa<T>::deduplicate(){
    Rank old_size = _size;
    Rank i = 1;
    while (i < _size){
        if(find(0, i, _elem[i]) >= 0){
            remove(i);
            //remove了之后就不用i++了，因为会该后方的所有元素会相应地往前挪一个位置
        }else{
            i++;
        }
    }
    return old_size -_size;
}

template <typename T>
void VectorDsa<T>::traverse(void (*op) (T&)){
    for(Rank i = 0; i < _size; i++){
        op(_elem[i]);
    }
}

template <typename T>
template<typename VST> void VectorDsa<T>::traverse(VST op){
    for(Rank i = 0; i < _size; i++){
        op(_elem[i]);
    }
}

/*
//起泡排序的版本一
//时间复杂度:O(n^1.5) n次循环，每次主要是swap交换操作耗时，但交换只是前缀中没有排好序的元素，个数为r<n。总的为n*平均sqrt(n)。
template <typename T>
void VectorDsa<T>::bubbleSort(Rank b, Rank e){
    //起泡排序
    while(!bubble(b, e--));
}


 template <typename T>
bool VectorDsa<T>::bubble(Rank low, Rank high){
    bool sorted = true;
    for(Rank i = low; i < high - 1; i++){
        if(_elem[i] > _elem[i+1]){
            swap(_elem[i], _elem[i+1]);
            sorted = false;
        }
    }
    return sorted;
}
*/

//起泡排序的版本二
//时间复杂度:O(n) 平均sqrt(n)次循环，直接将high挪到最后一次交换的rank处，得到sqrt(n)*sqrt(n)。
template <typename T>
void VectorDsa<T>::bubbleSort(Rank b, Rank e){
    //起泡排序
    Rank high = e;
    while(bubble(b, high--) < e);
}

template <typename T>
Rank VectorDsa<T>::bubble(Rank low, Rank high){
    Rank last = low;
    for(Rank i = low; i < high - 1; i++){
        if(_elem[i] > _elem[i+1]){
            swap(_elem[i], _elem[i+1]);
            last = i+1;
        }
    }
    return last;
}

template <typename T>
void VectorDsa<T>::mergeSort(Rank b, Rank e) {
    //归并排序
    Rank low = b, high = e;
    //基例
    if (high - low < 2){
        return;
    }
    //链条
    Rank middle = (low + high) >> 1;
    mergeSort(low, middle);
    mergeSort(middle, high);
    merge(low, middle, high);
}

template <typename T>
void VectorDsa<T>::merge(Rank low, Rank middle, Rank high){
    //合并两个有序区间
    int len_low = middle - low, len_high = high - middle;
    T *tmp_all = _elem + low;
    T *tmp_high = _elem + middle;
    T *tmp_low = new T[len_low];
    for(Rank i = 0; i < len_low; i++){
        tmp_low[i] = tmp_all[i];
    }
    Rank all_index = 0, low_to_mi = 0, mi_to_hi = 0;
    while (low_to_mi < len_low && mi_to_hi < len_high){
        if(tmp_low[low_to_mi] <= tmp_high[mi_to_hi]){
            tmp_all[all_index] = tmp_low[low_to_mi];
            low_to_mi++;
        } else{
            tmp_all[all_index] = tmp_high[mi_to_hi];
            mi_to_hi++;
        }
        all_index++;
    }
    while(low_to_mi < len_low){
        //!!!注意：依然能low_to_mi < len_low 说明后者已经耗尽了，所以需要将前者填补上来。
        //! 而同理，前者如果耗尽了，后者可以填补上来。
        //但是前者如果耗尽了，其实不用额外操作，这是因为mi_to_hi到len_high部分自然而言就已经在tmp_all里面了。
        tmp_all[all_index] = tmp_low[low_to_mi];
        low_to_mi++;
        all_index++;
    }
    delete [] tmp_low;
}



//友元
//方式一
//template <typename T>
//ostream & operator<<(ostream &os, VectorDsa<T> V);

//方式二
template <typename VST>  ostream & operator<<(ostream &os, VectorDsa<VST> V){
    for (Rank i = 0; i < V._size; i++){
        os << V._elem[i] << ",";
    }
    return os;
}

template <typename T> void increase(VectorDsa<T> &V){
    V.traverse(Increase<T>());
}

#endif //CPP_VECTOR_DSA_H
