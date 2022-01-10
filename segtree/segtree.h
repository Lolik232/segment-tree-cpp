//
// Created by vladv on 09.01.2022.
//

#ifndef SEGTREE_SEGTREE_H
#define SEGTREE_SEGTREE_H

#include <functional>
#include <vector>

#include "segtree-node.h"

// T - type of value in nodes
template<typename T>
class Segtree {
public:
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

    virtual T
    Query(const std::size_t leftBorder, const std::size_t rightBorder, const T startValue) {
        ssize_t leftBorderInTree = m_tree.size() - m_segmentSize + leftBorder;
        ssize_t rightBorderInTree = m_tree.size() - m_segmentSize + rightBorder;

        T leftResult;
        bool isNeutralLeftResult = true;

        T rightResult;
        bool isNeutralRightResult = true;

        while (leftBorderInTree <= rightBorderInTree) {
            SegtreeNode<T>* left = &m_tree.at(leftBorderInTree);
            SegtreeNode<T>* right = &m_tree.at(rightBorderInTree);

            if (!left->IsLeftChild()) {
                if (isNeutralLeftResult) {
                    leftResult = left->GetValue();
                    isNeutralLeftResult = false;
                } else
                    leftResult = m_mergeFunction(leftResult, left->GetValue());
            }

            if (right->IsLeftChild()) {
                if (isNeutralRightResult) {
                    rightResult = right->GetValue();
                    isNeutralRightResult = false;
                } else
                    rightResult = m_mergeFunction(rightResult, right->GetValue());
            }

            leftBorderInTree /= 2;
            rightBorderInTree = rightBorderInTree / 2 - 1;
        }

        if (isNeutralLeftResult)
            return rightResult;
        else if (isNeutralRightResult)
            return leftResult;
        else
            return m_mergeFunction(leftResult, rightResult);
    }

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
