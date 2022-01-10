#include <iostream>
#include <vector>
#include <functional>

#include "segtree/segtree.h"


int sum(int a, int b) {
    return a + b;
}

int min2(int a, int b) {
    return a < b ? a : b;
}

int main() {


    std::vector<int> segment = {4, 1, 4, 2, 6, 8};

    Segtree<int> segmentTree = Segtree<int>(segment, sum);

    std::cout << segmentTree.Query(0, 5, 0);
    return 0;
}