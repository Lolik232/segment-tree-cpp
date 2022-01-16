#include <iostream>
#include <vector>

#include "segtree/segtree.h"

long long sum(long long a, long long b) {
    return a + b;
}

long long min2(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<long long> segment(n);
    for (long long& a: segment) {
        std::cin >> a;
    }

    Segtree<long long> segmentTree(segment, min2);

    for (int i = 0; i < m; i++) {
        int currentOperation;
        std::cin >> currentOperation;

        if (currentOperation == 1) {
            long long value, pos;
            std::cin >> pos >> value;
            segmentTree.set(value, pos);
        } else {
            int left, right;
            std::cin >> left >> right;
            right -= 1;

            std::cout << segmentTree.query(left, right) << '\n';
        }
    }

    return 0;
}