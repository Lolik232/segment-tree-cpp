//
// Created by vladv on 14.01.2022.
//

#ifndef SEGTREE_INVERSION_SEGTREE_H
#define SEGTREE_INVERSION_SEGTREE_H

#include <functional>
#include <vector>

#include "segtree-node.h"

template<typename T>
class Segtree {
public:
    Segtree(std::vector<T> segment, std::function<T(T, T)> mergeFunction) : m_mergeFunction(mergeFunction) {
        // init tree
        init(segment.size());
        // copy segment data
        ssize_t iWrite = m_tree.size() - m_segmentSize;
        ssize_t iRead = 0;
        while (iWrite < m_tree.size()) {
            if (iRead < segment.size()) {
                m_tree.at(iWrite).setValue(segment.at(iRead));
                iRead++;
            }
            iWrite++;
        }
        // create tree
        iWrite = m_tree.size() - m_segmentSize - 1;
        while (iWrite >= 0) {
            std::size_t leftChildIndex = iWrite * 2 + 1;
            std::size_t rightChildIndex = iWrite * 2 + 2;

            SegtreeNode<T>& leftChild = m_tree.at(leftChildIndex);
            SegtreeNode<T>& rightChild = m_tree.at(rightChildIndex);

            SegtreeNode<T>& currentNode = m_tree.at(iWrite);

            currentNode.setLeftChild(&leftChild);
            currentNode.setRightChild(&rightChild);

            leftChild.setParent(&currentNode);
            rightChild.setParent(&currentNode);

            currentNode.updateValue(m_mergeFunction);

            iWrite--;
        }
    }

    virtual T query(std::size_t leftBorder, std::size_t rightBorder) {
        ssize_t segmentStartPosInTree = m_tree.size() - m_segmentSize;
        ssize_t leftBorderIndex = segmentStartPosInTree + leftBorder;
        ssize_t rightBorderIndex = segmentStartPosInTree + rightBorder;


        T leftResult;
        bool isLeftResultNeutral = true;

        T rightResult;
        bool isRightResultNeutral = true;

        while (leftBorderIndex <= rightBorderIndex) {
            SegtreeNode<T>& left = m_tree.at(leftBorderIndex);
            SegtreeNode<T>& right = m_tree.at(rightBorderIndex);

            if (!left.isLeftChild()) {
                if (left.isNeutral() == false && !isLeftResultNeutral)
                    leftResult = m_mergeFunction(leftResult, left.getValue());
                else if (left.isNeutral() == false) {
                    leftResult = left.getValue();
                    isLeftResultNeutral = false;
                }
            }

            if (right.isLeftChild()) {
                if (right.isNeutral() == false && !isRightResultNeutral)
                    rightResult = m_mergeFunction(rightResult, right.getValue());
                else if (left.isNeutral() == false) {
                    rightResult = right.getValue();
                    isRightResultNeutral = false;
                }
            }

            leftBorderIndex /= 2;
            rightBorderIndex = rightBorderIndex / 2 - 1;
        }

        if (isLeftResultNeutral)
            return rightResult;
        else if (isRightResultNeutral)
            return leftResult;
        else
            return m_mergeFunction(leftResult, rightResult);
    }

    void set(T value, std::size_t pos) {
        //TODO: throw exception
        if (pos > m_segmentSize)
            return;

        std::size_t posInTree = m_tree.size() - m_segmentSize + pos;

        SegtreeNode<T>* currentNode = &m_tree.at(posInTree);
        currentNode->setValue(value);

        while ((currentNode = currentNode->getParent()) != nullptr)
            currentNode->updateValue(m_mergeFunction);
    }

private:
    std::vector<SegtreeNode<T>> m_tree;
    std::size_t m_segmentSize;

    std::function<T(T, T)> m_mergeFunction;

private:
    void init(std::size_t segmentSize) {
        //TODO: add check for zero segment size
        m_segmentSize = 1;
        while (m_segmentSize < segmentSize)
            m_segmentSize *= 2;

        std::size_t treeSize = m_segmentSize * 2 - 1;

        m_tree.resize(treeSize);
    }
};


#endif //SEGTREE_INVERSION_SEGTREE_H
