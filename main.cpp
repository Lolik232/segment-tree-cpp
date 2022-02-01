#include <iostream>
#include <vector>

#include "segtree/segtree.h"
#include "segtree/segtree-seg-operation.h"

//struct MinCnt {
//	std::size_t count;
//	int value;
//};
//
//MinCnt combineNodes(const MinCnt& left, const MinCnt& right) {
//	if (left.value < right.value)
//		return left;
//	else if (right.value < left.value)
//		return right;
//
//	return MinCnt {
//		left.count + right.count,
//		left.value
//	};
//}

int main() {
//    std::vector<int> segment = {1, 2, 3};
//    SegtreeSegOperation<int> segtree(segment, segtree_op::SUM, segtree_op::
//    SUM_NEUTRAL_VAL);
//
//    int a = segtree.get(0);
//	int n, m;
//	std::cin >> n >> m;
//
//
//	std::vector<MinCnt> segment(n);
//	for (MinCnt& a : segment) {
//		std::cin >> a.value;
//		a.count = 1;
//	}
//
//	Segtree<MinCnt> segmentTree(segment, combineNodes);
//
//	for (int i = 0; i < m; i++) {
//		int currentOperation;
//		std::cin >> currentOperation;
//
//		if (currentOperation == 1) {
//			int value, pos;
//			std::cin >> pos >> value;
//			segmentTree.set(MinCnt { 1, value }, pos);
//		} else {
//			int left, right;
//			std::cin >> left >> right;
//			right -= 1;
//
//			MinCnt res = segmentTree.query(left, right);
//			std::cout << res.value << ' ' << res.count << '\n';
//		}
//	}

    return 0;
}