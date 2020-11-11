#include <iostream>
#include "Stack.h"
#include "StackfromList.h"
#include "stackTestExample.h"
#include "Queue.h"

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

    Stack<char> stack_char;
    convert(stack_char, 12345, 8);
    cout << stack_char << endl;
    Stack<char> stack_char_recur;
    convert(stack_char_recur, 12345, 8, "recursion");
    cout << stack_char_recur << endl;

    string exp = "(-)((1+1) - (2+2))";
    if(match_paren(exp)){
        cout << "parentheses match! " << endl;
    } else{
        cout << "parentheses don't match! " << endl;
    }

    Queue<int> queue1;
    queue1.edqueue(1);
    cout << queue1.front() << endl;
    queue1.dequeue();
    cout << "size: " << queue1.size() << endl;

    return 0;
}