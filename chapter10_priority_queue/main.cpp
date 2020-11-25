#include <iostream>
#include "PriorityQueue.h"

int main() {
    int array_[5] = {1, 2, 4, 5, 3};
    PriorityQueue<int> heap_(array_, 5);
    cout << heap_ << endl;
    cout << heap_.getMax() << endl;
    heap_.delMax();
    cout << heap_ << endl;

    VectorDsa<int> ivec(array_, 5);
    cout << ivec << endl;
    heapSort(ivec);
    cout << ivec << endl;

    return 0;
}