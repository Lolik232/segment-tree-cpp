//
// Created by vladv on 09.01.2022.
//

#ifndef SEGTREE_SEGTREE_NODE_H
#define SEGTREE_SEGTREE_NODE_H

#include <functional>
#include <vector>

template<typename T>
class SegtreeNode {
public:
    SegtreeNode() = default;

    SegtreeNode(std::size_t leftBorder, std::size_t rightBorder) : m_isNeutral(true),
                                                                   m_leftBorder(leftBorder),
                                                                   m_rightBorder(rightBorder) {}

    SegtreeNode(std::size_t leftBorder, std::size_t rightBorder,
                SegtreeNode<T>* parent) : SegtreeNode(leftBorder, rightBorder) {
        m_parent = parent;
    }

    SegtreeNode(std::size_t leftBorder, std::size_t rightBorder,
                SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild,
                std::function<T(T, T)> mergeFunction) : m_leftBorder(leftBorder),
                                                        m_rightBorder(rightBorder),
                                                        m_leftChild(leftChild),
                                                        m_rightChild(rightChild) {
        if (leftChild->IsNeutral() && rightChild->IsNeutral())
            SetNeutral(true);
        else if (leftChild->IsNeutral())
            SetValue(rightChild->GetValue());
        else if (rightChild->IsNeutral())
            SetValue(leftChild->GetValue());
        else {
            T newValue = mergeFunction(leftChild->GetValue(), rightChild->GetValue());
            SetValue(newValue);
        }
    }

    SegtreeNode(std::size_t leftBorder, std::size_t rightBorder, SegtreeNode<T>* parent,
                SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild,
                std::function<T(T, T)> mergeFunction)
            : SegtreeNode(leftBorder, rightBorder, leftChild, rightChild, mergeFunction) {
        m_parent = parent;
    }

    SegtreeNode(T value, std::size_t leftBorder, std::size_t rightBorder)
            : m_value(value), m_leftBorder(leftBorder), m_rightBorder(rightBorder) {
    }


    SegtreeNode(T value, std::size_t leftBorder, std::size_t rightBorder,
                SegtreeNode<T>* parent) : m_value(value), m_leftBorder(leftBorder),
                                          m_rightBorder(rightBorder), m_parent(parent) {
    }

    SegtreeNode(T value, std::size_t leftBorder, std::size_t rightBorder,
                SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild) : m_value(value),
                                                                         m_leftBorder(leftBorder),
                                                                         m_rightBorder(rightBorder),
                                                                         m_leftChild(leftChild),
                                                                         m_rightChild(rightChild) {
    }

    SegtreeNode(T value, std::size_t leftBorder, std::size_t rightBorder, SegtreeNode<T>* parent,
                SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild) : m_value(value),
                                                                         m_leftBorder(leftBorder),
                                                                         m_rightBorder(rightBorder),
                                                                         m_parent(parent),
                                                                         m_leftChild(leftChild),
                                                                         m_rightChild(rightChild) {
    }

    bool IsLeftChild() {
        if (m_parent == nullptr || m_parent->GetLeftChild() != this)
            return false;

        return true;
    }

    bool IsNeutral() const {
        return m_isNeutral;
    }

    bool SetNeutral(bool value) {
        m_isNeutral = value;
    }

    T GetValue() const {
        return m_value;
    }

    void SetValue(T value) {
        m_value = value;
    }

    std::size_t GetLeftBorder() const {
        return m_leftBorder;
    }

    void SetLeftBorder(std::size_t leftBorder) {
        m_leftBorder = leftBorder;
    }

    std::size_t GetRightBorder() const {
        return m_rightBorder;
    }

    void SetRightBorder(std::size_t rightBorder) {
        m_rightBorder = rightBorder;
    }

    SegtreeNode<T>* GetParent() const {
        return m_parent;
    }

    void SetParent(SegtreeNode<T>* parent) {
        m_parent = parent;
    }

    SegtreeNode<T>* GetLeftChild() const {
        return m_leftChild;
    }

    SegtreeNode<T>* GetRightChild() const {
        return m_rightChild;
    }

    SegtreeNode<T>& operator=(const SegtreeNode<T>& otherNode) {
        if (this == &otherNode)
            return *this;

        m_isNeutral = otherNode.IsNeutral();

        SetValue(otherNode.GetValue());
        SetParent(otherNode.GetParent());

        m_leftChild = otherNode.m_leftChild;
        m_rightChild = otherNode.m_rightChild;

        SetLeftBorder(otherNode.GetLeftBorder());
        SetRightBorder(otherNode.GetRightBorder());

        return *this;
    }

private:
    bool m_isNeutral = false;

    T m_value;

    std::size_t m_leftBorder;
    std::size_t m_rightBorder;

    SegtreeNode<T>* m_parent = nullptr;
    SegtreeNode<T>* m_leftChild = nullptr;
    SegtreeNode<T>* m_rightChild = nullptr;
};

#endif //SEGTREE_SEGTREE_NODE_H
