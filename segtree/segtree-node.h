//
// Created by vladv on 13.01.2022.
//

#ifndef SEGTREE_INVERSION_SEGTREE_NODE_H
#define SEGTREE_INVERSION_SEGTREE_NODE_H

#include <functional>

// T - type of data in node
template<typename T>
class SegtreeNode {
public:
    SegtreeNode() = default;

    explicit SegtreeNode(SegtreeNode<T>* parent) : m_parent(parent) {}

    SegtreeNode(SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild, std::function<T(T, T)> compareValuesFunc)
            : m_leftChild(leftChild),
              m_rightChild(rightChild) {
        if (leftChild->isNeutral() && rightChild->isNeutral()) {
            return;
        }

        if (leftChild->isNeutral())
            m_value = rightChild->getValue();
        else if (rightChild->isNeutral())
            m_value = leftChild->getValue();
        else
            m_value = compareValuesFunc(leftChild->getValue(), rightChild->getValue());

        m_isNeutral = false;
    }

    SegtreeNode(SegtreeNode<T>* parent, SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild,
                std::function<T(T, T)> compareValuesFunc)
            : SegtreeNode(leftChild, rightChild, compareValuesFunc) {
        m_parent = parent;
    }

    explicit SegtreeNode(T value) : m_value(value), m_isNeutral(false) {}

    SegtreeNode(T value, SegtreeNode<T>* parent) : m_value(value),
                                                   m_parent(parent),
                                                   m_isNeutral(false) {}

    SegtreeNode(T value, SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild) : m_value(value),
                                                                                  m_leftChild(leftChild),
                                                                                  m_rightChild(rightChild),
                                                                                  m_isNeutral(false) {}

    SegtreeNode(T value, SegtreeNode<T>* parent, SegtreeNode<T>* leftChild, SegtreeNode<T>* rightChild) : m_value(
            value), m_parent(parent), m_leftChild(leftChild), m_rightChild(rightChild), m_isNeutral(false) {}

    bool isNeutral() {
        return m_isNeutral;
    };

    T getValue() const {
        return m_value;
    }

    void setValue(T value) {
        m_value = value;
        m_isNeutral = false;
    }

    void updateValue(std::function<T(T, T)> mergeFunction) {
        if ((m_leftChild == nullptr || m_leftChild->isNeutral()) &&
            (m_rightChild == nullptr || m_rightChild->isNeutral()))
            return;
        else if (m_leftChild == nullptr || m_leftChild->isNeutral())
            setValue(m_rightChild->getValue());
        else if (m_rightChild == nullptr || m_rightChild->isNeutral())
            setValue(m_leftChild->getValue());
        else
            setValue(mergeFunction(m_leftChild->getValue(), m_rightChild->getValue()));
    }

    SegtreeNode<T>* getParent() const {
        return m_parent;
    }

    void setParent(SegtreeNode<T>* parent) {
        m_parent = parent;
    }

    SegtreeNode<T>* getLeftChild() const {
        return m_leftChild;
    }

    void setLeftChild(SegtreeNode<T>* leftChild) {
        m_leftChild = leftChild;
    }

    SegtreeNode<T>* getRightChild() const {
        return m_rightChild;
    }

    void setRightChild(SegtreeNode<T>* rightChild) {
        m_rightChild = rightChild;
    }

    bool isLeftChild() {
        if (m_parent == nullptr || m_parent->getLeftChild() != this)
            return false;

        return true;
    }

    bool isRightChild() {
        if (m_parent == nullptr || m_parent->getRightChild() != this)
            return false;

        return true;
    }

private:
    // TODO: update default value!
    bool m_isNeutral = true;
    T m_value;

    SegtreeNode<T>* m_parent = nullptr;
    SegtreeNode<T>* m_leftChild = nullptr;
    SegtreeNode<T>* m_rightChild = nullptr;
};

#endif //SEGTREE_INVERSION_SEGTREE_NODE_H
