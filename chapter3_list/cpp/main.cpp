#include <iostream>
#include "List.h"
#include "ListOrdered.h"

int main() {
    List<int> ilist;
    for (int i = 0; i < 5; i++){
        ilist.insert(i);
    }
    cout << ilist << endl;

    ilist.insert(3);
    cout << ilist << endl;
    ilist.insertAtFirst(5);
    cout << ilist << endl;
    ilist.insertAtLast(7);

    ilist.deduplicate();
    cout << ilist << endl;
    ilist.mergeSort();
    cout << ilist << endl;

    ListOrdered<int> ilist_ordered;
    for (int i = 5; i < 10; i++){
        ilist_ordered.insert(i);
        ilist_ordered.insert(i);
    }
    cout << ilist_ordered << endl;
    ilist_ordered.uniquify();
    cout << ilist_ordered << endl;

    return 0;
}