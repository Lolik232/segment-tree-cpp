#pragma once

#include <vector>

#include "segtree-node.h"

namespace segtree_op {
    auto SUM = [](auto a, auto b) {
        return a + b;
    };
    auto PRODUCT = [](auto a, auto b) {
        return a * b;
    };
}

template<typename T>
class SegtreeBase {
public:
    virtual ~SegtreeBase() = default;

protected:
    std::vector<SegtreeNode<T>> m_tree;
    std::size_t m_segmentSize = 0;
    std::function<T(T, T)> m_operation;

    void init(std::size_t segmentSize) {
        if (segmentSize == 0) {
            m_tree.resize(0);
            m_segmentSize = 0;
        }

        m_segmentSize = 1;
        while (m_segmentSize < segmentSize)
            m_segmentSize *= 2;

        std::size_t treeSize = m_segmentSize * 2 - 1;

        m_tree.resize(treeSize);
    }
};
