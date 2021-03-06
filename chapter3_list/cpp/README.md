# 数组【无序链表、有序链表】

里面包含了无序链表、有序链表的典型接口。【这里的链表是双向链表，即有prev和next两个成员变量。但是一般都是考察单向链表，只有next。此时可以多设一个prevhead或nexttrailer哨兵节点，以便保留节点链接信息。

## 【1】无序链表

### 文件

main.cpp —— 简单测试文件

List.h —— 无序链表类

ListNode.h —— 节点类

### 无序链表接口

（1）创建/初始化：构造、析构

（2）索引 【没有数组方便】也就是按照序号查找元素

（3）查找 【遍历】

（4）插入/增加元素  √【方便】

（5）删除元素 √【方便】

（6）长度 【没有数组方便，需遍历所有数据后】

但是如果能在list成员变量里设置一个_size成员函数，也是会很方便的。

但很多情况下不能像数组一样到下一个元素根据 for(Rank i = 0; i < _size; i++) 来对[i]进行操作，而是只能新定义一个ListNode节点，然后->next。




附加接口和操作：

（1）唯一化、去重【联想unique、去重。和remove一起。】

无序链表：思想：与无序向量的去重方法类似，但是也有区别。主要还是前缀比较方法：在元素前方的区间是否有与该元素相等的，在无序向量中有就剔除该元素，而在无序链表中有就删除该元素前方与该元素相等的元素。

（2）遍历【联想for_each，也可以有两个版本：不变序列算法或变值算法】

（3）排序

包括起泡排序、选择排序、插入排序、归并排序、堆排序、快速排序。

②选择排序

③插入排序

④归并排序【这里有个**重要的函数 merge：合并两个有序链表**。这在LeetCode第21题中也考察了】

（4）插入/增加元素  √【方便】

在前方插入和在后方插入

注意！！！调整被插入元素的指针p时，必须先处理被插入元素的指针p的prev或next，而不能先处理被插入元素的指针p。因为如果先处理了被插入元素的指针p，那么后续被插入元素的指针p的prev或next就已经变成了tmp_p，而不是之前的那个p了！！！

（5）删除元素 √【方便】

因为有前后哨兵节点，那么就算list中只剩一个node p，删掉该nodep的过程，也不会出问题。因为此时也能得到(p->prev)->next和(p->next)->prev。但是如果没有哨兵节点肯定会报错，甚至p->next 或 p->prev其中就有个指令会不成功。

### 关键注意点！

每个链表本身只存储一个data，一个prev节点指针，一个next节点指针。【对于单向链表而言只有data和next节点指针】。所以要时刻注意删除链表的节点的时候，是不是链表会断！一般有几个技巧：

①先p = p->next; 再删除 p->prev;

②对于单向链表而言，没有prev节点，就自己建一个prevhead节点！【具体案例可以看LeetCode第21题，合并两个有序链表】



## 【2】有序链表

### 文件

main.cpp —— 简单测试文件

ListOrdered.h —— 有序链表类

ListNode.h —— 节点类

### 有序数组接口

（1）创建/初始化：构造、析构

（2）索引 【没有数组方便】也就是按照序号查找元素

（3）查找 【遍历】**和无序链表差别不大**，主要就是这里用的 <=就可以break出【返回不大于元素t的最大秩】，而find那里用的是 == 【没找到就失败】。

（4）插入/增加元素  √【方便】

（5）删除元素 √【方便】

（6）长度 【没有数组方便，需遍历所有数据后】

但是如果能在list成员变量里设置一个_size成员函数，也是会很方便的。
但很多情况下不能像数组一样到下一个元素根据 for(Rank i = 0; i < _size; i++) 来对[i]进行操作，而是只能新定义一个ListNode节点，然后->next。



附加接口和操作：

（1）唯一化、去重【联想unique、去重。和remove一起。】

思想：从前往后遍历，相邻节点对比较数值大小，等于就剔除掉后面的元素，不等于则跳过，转向下一个next区段。

（2）遍历【联想for_each，也可以有两个版本：不变序列算法或变值算法】

对链表上的每个元素进行操作op，这个op可以是函数指针，也可以是函数对象！！！

