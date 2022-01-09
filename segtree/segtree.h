//
// Created by vladv on 09.01.2022.
//

#ifndef SEGTREE_SEGTREE_H
#define SEGTREE_SEGTREE_H

#include <functional>
#include <vector>

#include "segtree-node.h"

// T - type of value in nodes
// F - function for merge values in node
template<typename T>
class Segtree {
public:
//    Segtree(T segmentValue, std::size_t segmentSize, std::function<T(T, T)> mergeFunction);

    Segtree(std::vector<T>& segment,
            std::function<T(T, T)> mergeFunction) {
        m_mergeFunction = mergeFunction;

        init(segment.size());

        ssize_t iWrite = m_tree.size() - m_segmentSize;
        ssize_t iRead = 0;
        while (iRead < segment.size()) {
            SegtreeNode<T>* parent = &m_tree.at((iWrite - 1) / 2);
            m_tree.at(iWrite) = SegtreeNode<T>(segment.at(iRead), iRead, iRead, parent);
            iWrite++;
            iRead++;
        }

        while (iWrite < m_tree.size()) {
            SegtreeNode<T>* parent = &m_tree.at((iWrite - 1) / 2);
            m_tree.at(iWrite) = SegtreeNode<T>(iRead, iRead, parent);
            iWrite++;
            iRead++;
        }

        iWrite = m_tree.size() - m_segmentSize - 1;

        while (iWrite >= 0) {
            SegtreeNode<T>* leftChild = &m_tree.at(iWrite * 2 + 1);
            SegtreeNode<T>* rightChild = &m_tree.at(iWrite * 2 + 2);

            m_tree.at(iWrite) = SegtreeNode<T>(leftChild->GetLeftBorder(),
                                               rightChild->GetRightBorder(),
                                               leftChild, rightChild, m_mergeFunction);

            leftChild->SetParent(&m_tree.at(iWrite));
            rightChild->SetParent(&m_tree.at(iWrite));

            iWrite--;
        }
    }

    T Query(std::size_t lBorder, std::size_t rightBorder);

    T Get(std::size_t pos);

    void Set(T value, std::size_t pos);

private:
    std::function<T(T, T)> m_mergeFunction;
    std::vector<SegtreeNode<T>> m_tree;
    std::size_t m_segmentSize;

    void init(std::size_t segmentSize) {
        if (segmentSize <= 0)
            throw std::invalid_argument("Segment size must be positive");

        m_segmentSize = 1;
        while (m_segmentSize < segmentSize)
            m_segmentSize *= 2;

        std::size_t treeSize = m_segmentSize * 2 - 1;

//        m_tree.reserve(treeSize);
        m_tree.resize(treeSize);
    }
};


#endif //SEGTREE_SEGTREE_H
