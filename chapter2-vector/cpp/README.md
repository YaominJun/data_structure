# 数组【无序数组、有序数组】

里面包含了无序数组、有序数组的典型接口。

## 【1】无序数组

### 文件

main.cpp —— 简单测试文件

vector_dsa.h —— 无序数组类

append_class.h —— 非数组类的其他类

### 无序数组接口

（1）创建/初始化：构造、析构；赋值=运算符重载
（2）索引 √【很方便，下标即可】：访问[]，重载[]
（3）查找 【遍历】
（4）插入/增加元素 【没有链表方便，需要挪位置】
（5）删除元素 【没有链表方便，需要挪位置】
（6）长度 √【方便】

附加接口和操作
（1）唯一化、去重【联想unique、去重。和remove一起。】
前缀比较方法
（2）遍历【联想for_each，也可以有两个版本：不变序列算法或变值算法】
对向量上的每个元素进行操作op，这个op可以是函数指针，也可以是函数对象！！！

（3）判断向量是否有序
（4）对无序向量排序

### 具体实现

（1）创建/初始化：构造、析构；赋值=运算符重载

``//构造函数【多个】``

``explicit VectorDsa(int c = DEFAULT_CAPACITY, int num = 0, T v = 0);``

``VectorDsa( T const *A, Rank n){copyFrom(A, 0, n);}``

``VectorDsa( T const *A, Rank lo, Rank hi){copyFrom(A, lo, hi);}``

``VectorDsa( VectorDsa<T> const &V){copyFrom(V._elem, 0, V._size);}``

``VectorDsa( VectorDsa<T> const &V, Rank lo, Rank hi){copyFrom(V._elem, lo, hi);}``

``//析构函数【单个】``

``~VectorDsa(){delete [] _elem;}
``

``VectorDsa& operator=(VectorDsa<T> const &V);``

（2）索引：访问[]，重载[]

``T &operator[](Rank n){ return _elem[n];}``

``const T&operator[](Rank n) const{ return _elem[n];}``

（3）查找 【遍历】

无序容器有关的算法，一般相等判别是用 == 比较器或操作op返回true；【无序容器中的元素为可判等的基本类型，或已经重载操作符==或!=】

有序容器有关的算法，一般相等判别用的是 x不小于y，x也不大于y的判断方式。【有序容器中的元素为可比较的基本类型，或已经重载操作符<或>】

``Rank find(Rank b, Rank e,T const &t);``

``Rank find(T const &t){ return find(0, _size, t);}``

（4）插入/增加元素 【没有链表方便，需要挪位置】

``Rank insert(Rank r, T const &t);``

``Rank insert(T const &t){return insert(_size, t);} //默认插入末尾``

![1](..\images\1.png)

（5）删除元素 【没有链表方便，需要挪位置】

remove接口

**注意：**先定义区间删除，再基于此定义单个元素删除。则只用O(N)的复杂度，也就是挪位置的复杂度。

![2](..\images\2.png)

（6）长度 √【方便】

```Rank size()const { return _size;}```



附加接口和操作:

（1）唯一化、去重【和remove一起。】

deduplicate接口

思想：前缀比较方法：在元素前方的区间是否有与该元素相等的，有就剔除该元素。所以是从1开始计算。

算法复杂度分析：算法复杂度为O（N^2）

（2）遍历

对向量上的每个元素进行操作op，这个op可以是函数指针，也可以是函数对象！！！

方式一：函数指针【只读或局部修改】

```void traverse(void (*op) (T&));```

方式二：函数对象【只读或全局修改】

```template<typename VST> void traverse(VST &op);```

（3）判断向量是否有序

disordered接口

相邻元素对之间进行顺序判断，顺序就继续，逆序就累加，最后只有为0时才说明没有逆序对。

（4）对无序向量排序

排序算法在basic_algorithms仓库里具体说明。

包括起泡排序、选择排序、归并排序、堆排序、快速排序。

①起泡排序

版本一：如果起泡排序在扫描一遍的过程中，都没有进行逆序对交换，说明整体都已经达到了正序，不需要再进行排序了。所以用soreted作为标志位，及时终止排序。

```template <typename T>```

```void VectorDsa<T>::bubbleSort(Rank b, Rank e){```

```  //起泡排序  while(!bubble(b, e--));}```

版本二：如果起泡排序在扫描一遍的过程中，后方都没有进行逆序对交换，说明后方都已经达到了正序，不需要再进行排序了，可以直接将范围缩小到计算到最后一次逆序对交换的位置。所以用返回的Rank作为排序扫描的末尾，及时终止排序。

```template <typename T>```

```void VectorDsa<T>::bubbleSort(Rank b, Rank e){  ```

```//起泡排序  Rank high = e;  ```

```while(bubble(b, high--) < e);}```

②归并排序

mergeSort接口



## 【2】有序数组

### 文件

main.cpp —— 简单测试文件

vector_dsa_ordered.h —— 无序数组类

fibonacci\fib.h —— 斐波那契数列类【具体说明在basic_algorithms里】

### 有序数组接口

（1）创建/初始化：构造、析构；赋值=运算符重载
（2）索引 √【很方便，下标即可】：访问[]，重载[]
（3）查找 【遍历】能有高效的方法：二分查找及其改进版本；斐波那契查找；插值查找。【具体说明在basic_algorithms里】
（4）插入/增加元素 【没有链表方便，需要挪位置】
（5）删除元素 【没有链表方便，需要挪位置】
（6）长度 √【方便】

附加接口和操作：
（1）唯一化、去重【联想unique、去重。和remove一起。】能有高效的方法：不采用remove版本，而是想更巧妙的办法。直接一步到位。找到不重复的元素，直接移到正在判别是否重复的元素的右边。

### 具体实现

构造函数等部分和无序数组一样，其实不应该一样。但是为了简便起见，直接写了。

（1）创建/初始化：构造、析构；赋值=运算符重载
（2）索引 √【很方便，下标即可】：访问[]，重载[]
（3）查找 【遍历】能有高效的方法
**二分搜索及其改进**

binsearch接口、binsearch_improve接口、binsearch_return_rule接口（满足语义规定的二分法搜索）

**Fibonacci查找**

fibsearch接口

**插值查找**

（4）插入/增加元素 【没有链表方便，需要挪位置】
（5）删除元素 【没有链表方便，需要挪位置】
（6）长度 √【方便】

附加接口和操作：
（1）唯一化、去重

高效版本

uniquify接口

不采用remove版本【remove会将后方的元素全部往前挪，所以最坏情况是O(N)的复杂度】，而是想更巧妙的办法。直接一步到位。

复杂度是O(N)。