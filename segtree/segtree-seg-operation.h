#pragma once

#include <vector>
#include <stdexcept>

#include "segtreebase.h"

namespace segtree_op {
    const auto SUM_NEUTRAL_VAL = 0;
    const auto PRODUCT_NEUTRAL_VAL = 1;
}


namespace segtree_op_with_seg {
// дерево отрезков для операции на отрезке
// например, прибавление какого-то числа к отрезку
// T - тип значения, хранящегося в узле дерева
    template<typename T>
    class SegtreeSegOperation : public SegtreeBase<T> {
    public:
        SegtreeSegOperation(std::vector<T>& segment, std::function<T(T, T)> operationOnSegment,
                            T neutralValue) : m_opNeutralVal(neutralValue) {
            SegtreeBase<T>::m_operation = operationOnSegment;
            SegtreeBase<T>::init(segment.size());
            build(segment);
        }

        T get(std::size_t pos) {
            if (pos > SegtreeBase<T>::m_segmentSize)
                throw std::invalid_argument("Pos is bigger than segment size");

            ssize_t posInTree = SegtreeBase<T>::m_tree.size() - SegtreeBase<T>::m_segmentSize;

            T result = m_opNeutralVal;

            SegtreeNode<T>* currentNode = &SegtreeBase<T>::m_tree.at(posInTree);
            while (currentNode != nullptr) {
                result += currentNode->getValue();
                currentNode = currentNode->getParent();
            }

            return result;
        }

        void operation(T value, std::size_t leftBorder, std::size_t rightBorder) {

        }

    private:
        T m_opNeutralVal;

    private:
        void build(std::vector<T>& segment) {
            ssize_t iWrite = SegtreeBase<T>::m_tree.size() - SegtreeBase<T>::m_segmentSize;
            ssize_t iRead = 0;
            while (iWrite < SegtreeBase<T>::m_tree.size()) {
                if (iRead < segment.size()) {
                    SegtreeBase<T>::m_tree.at(iWrite).setValue(segment.at(iRead));
                    iRead++;
                } else
                    SegtreeBase<T>::m_tree.at(iWrite).setValue(m_opNeutralVal);

                iWrite++;
            }

            // create tree
            iWrite = SegtreeBase<T>::m_tree.size() - SegtreeBase<T>::m_segmentSize - 1;
            while (iWrite >= 0) {
                std::size_t leftChildIndex = iWrite * 2 + 1;
                std::size_t rightChildIndex = iWrite * 2 + 2;

                SegtreeNode<T>* leftChild = &SegtreeBase<T>::m_tree.at(leftChildIndex);
                SegtreeNode<T>* rightChild = &SegtreeBase<T>::m_tree.at(rightChildIndex);

                SegtreeNode<T>* currentNode = SegtreeBase<T>::m_tree.at(iWrite);

                currentNode->setLeftChild(leftChild);
                currentNode->setRightChild(rightChild);

                leftChild->setParent(&currentNode);
                rightChild->setParent(&currentNode);

                currentNode->setValue(m_opNeutralVal);

                iWrite--;
            }
        }
    };
}