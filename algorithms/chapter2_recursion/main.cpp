#include <iostream>
#include "hanoi.h"

int main() {
    exam2::Solution solution2;
    int n = 4;
    solution2.hanoi(n, 'A', 'B', 'C');

    return 0;
}