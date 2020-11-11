#include <iostream>
#include "Stack.h"
#include "StackfromList.h"

int main() {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    cout << stack1.top() << endl;
    stack1.pop();
    cout << stack1.top() << endl;
    stack1.top() = 3;
    cout << stack1.top() << endl;

    StackfromList<int> stackfromList1;
    stackfromList1.push(1);
    stackfromList1.push(2);
    cout << stackfromList1.top() << endl;
    stackfromList1.pop();
    cout << stackfromList1.top() << endl;
    stackfromList1.top() = 3;
    cout << stackfromList1.top() << endl;

    return 0;
}