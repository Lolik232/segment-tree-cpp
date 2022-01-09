#include <iostream>
#include <vector>
#include <functional>

#include "segtree/segtree.h"

int sum(int a, int b) {
    return a + b;
}

int product(int a, int b) {
    return a * b;
}

int main() {

    std::vector<int> segment = {2, 3, 4, 5, 6};

    Segtree<int> segmentTree = Segtree<int>(segment, sum);


    return 0;
}