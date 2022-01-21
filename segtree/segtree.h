//
// Created by vladv on 14.01.2022.
//
#pragma once

#include <functional>
#include <vector>
#include <stdexcept>
#include <cstddef>

#include "segtreebase.h"

namespace segtree_op_on_segment {
// дерево отрезков для получения значения ассоциативной операции на отрезке
// T - тип значения, хранящегося в узле дерева
    template<typename T>
    class Segtree : public SegtreeBase<T> {
    public:
        Segtree(std::vector<T>& segment, std::function<T(T, T)> mergeFunction) {
            SegtreeBase<T>::m_operation = mergeFunction;
            // init tree
            SegtreeBase<T>::init(segment.size());
            // copy segment data
            ssize_t iWrite = SegtreeBase<T>::m_tree.size() - SegtreeBase<T>::m_segmentSize;
            ssize_t iRead = 0;
            while (iWrite < SegtreeBase<T>::m_tree.size()) {
                if (iRead < segment.size()) {
                    SegtreeBase<T>::m_tree.at(iWrite).setValue(segment.at(iRead));
                    iRead++;
                }
                iWrite++;
            }
            // create tree
            iWrite = SegtreeBase<T>::m_tree.size() - SegtreeBase<T>::m_segmentSize - 1;
            while (iWrite >= 0) {
                std::size_t leftChildIndex = iWrite * 2 + 1;
                std::size_t rightChildIndex = iWrite * 2 + 2;

                SegtreeNode<T>& leftChild = SegtreeBase<T>::m_tree.at(leftChildIndex);
                SegtreeNode<T>& rightChild = SegtreeBase<T>::m_tree.at(rightChildIndex);

                SegtreeNode<T>& currentNode = SegtreeBase<T>::m_tree.at(iWrite);

                currentNode.setLeftChild(&leftChild);
                currentNode.setRightChild(&rightChild);

                leftChild.setParent(&currentNode);
                rightChild.setParent(&currentNode);

                currentNode.updateValue(SegtreeBase<T>::m_operation);

                iWrite--;
            }
        }

        ~Segtree() override = default;

        virtual T query(std::size_t leftBorder, std::size_t rightBorder) {
            // check leftBorder value and rightBorder value

            ssize_t segmentStartPosInTree = SegtreeBase<T>::m_tree.size() - SegtreeBase<T>::m_segmentSize;
            ssize_t leftBorderIndex = segmentStartPosInTree + leftBorder;
            ssize_t rightBorderIndex = segmentStartPosInTree + rightBorder;

            T leftResult;
            bool isLeftResultNeutral = true;

            T rightResult;
            bool isRightResultNeutral = true;

            while (leftBorderIndex <= rightBorderIndex) {
                SegtreeNode<T>& left = SegtreeBase<T>::m_tree.at(leftBorderIndex);
                SegtreeNode<T>& right = SegtreeBase<T>::m_tree.at(rightBorderIndex);

                // небольшой костыль ;)
                if (!left.isLeftChild()) {
                    if (left.isNeutral() == false && !isLeftResultNeutral)
                        leftResult = SegtreeBase<T>::m_operation(leftResult, left.getValue());
                    else if (left.isNeutral() == false) {
                        leftResult = left.getValue();
                        isLeftResultNeutral = false;
                    }
                }

                if (right.isLeftChild()) {
                    if (right.isNeutral() == false && !isRightResultNeutral)
                        rightResult = SegtreeBase<T>::m_operation(rightResult, right.getValue());
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
                return SegtreeBase<T>::m_operation(leftResult, rightResult);
        }

        virtual void set(T value, std::size_t pos) {
            if (pos >= SegtreeBase<T>::m_segmentSize)
                throw std::invalid_argument("Pos is bigger than segment size");

            std::size_t
                    posInTree = SegtreeBase<T>::m_tree.size() - SegtreeBase<T>::m_segmentSize + pos;

            SegtreeNode<T>* currentNode = &SegtreeBase<T>::m_tree.at(posInTree);
            currentNode->setValue(value);

            while ((currentNode = currentNode->getParent()) != nullptr)
                currentNode->updateValue(SegtreeBase<T>::m_operation);
        }
    };
}