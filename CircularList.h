#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <stdexcept>

template <typename T>
class CircularList {
    private:
        struct Node {
                T data;
                Node* next;
                Node* prev;
                Node(const T& value) : data(value), next(this), prev(this) {}
        };

        Node* head;
        size_t count;

    public:
        CircularList();
        ~CircularList();

        class iterator;

        iterator begin();
        iterator end();

        size_t size() const;
        bool empty() const;

        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        void push_back(const T& value);
        void push_front(const T& value);
        void pop_back();
        void pop_front();

        void clear();

        iterator insert(iterator pos, const T& value);
        iterator erase(iterator pos);

        void assign(size_t n, const T& value);

        void swap(CircularList& other);

        class iterator
            : public std::iterator<std::bidirectional_iterator_tag, T> {
                Node* node;
                Node* head;

            public:
                iterator(Node* n = nullptr, Node* h = nullptr);
                T& operator*();
                iterator& operator++();
                iterator& operator--();
                bool operator==(const iterator& other) const;
                bool operator!=(const iterator& other) const;
                friend class CircularList;
        };
};

template <typename T>
CircularList<T>::CircularList() : head(nullptr), count(0) {
}

template <typename T>
CircularList<T>::~CircularList() {
    clear();
}

template <typename T>
void CircularList<T>::push_back(const T& value) {
    Node* node = new Node(value);
    if (!head) {
        head = node;
    } else {
        Node* tail = head->prev;
        tail->next = node;
        node->prev = tail;
        node->next = head;
        head->prev = node;
    }
    ++count;
}

template <typename T>
void CircularList<T>::push_front(const T& value) {
    push_back(value);
    head = head->prev;
}

template <typename T>
void CircularList<T>::pop_back() {
    if (!head) return;
    Node* tail = head->prev;
    if (tail == head) {
        delete head;
        head = nullptr;
    } else {
        tail->prev->next = head;
        head->prev = tail->prev;
        delete tail;
    }
    --count;
}

template <typename T>
void CircularList<T>::pop_front() {
    if (!head) return;
    if (head->next == head) {
        delete head;
        head = nullptr;
    } else {
        Node* old_head = head;
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
        delete old_head;
    }
    --count;
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::insert(iterator pos,
                                                           const T& value) {
    if (pos.node == nullptr || head == nullptr) {
        push_back(value);
        return iterator(head->prev, head);
    }
    Node* cur = pos.node;
    Node* prev = cur->prev;
    Node* node = new Node(value);
    node->next = cur;
    node->prev = prev;
    prev->next = node;
    cur->prev = node;
    if (cur == head) head = node;
    ++count;
    return iterator(node, head);
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::erase(iterator pos) {
    if (empty() || pos.node == nullptr) return end();
    Node* node = pos.node;
    iterator iter(node->next == head ? nullptr : node->next, head);
    if (node->next == node) {
        delete node;
        head = nullptr;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if (node == head) head = node->next;
        delete node;
    }
    --count;
    return iter;
}

template <typename T>
void CircularList<T>::assign(size_t n, const T& value) {
    clear();
    for (size_t i = 0; i < n; ++i) {
        push_back(value);
    }
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::begin() {
    return iterator(head, head);
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::end() {
    return iterator(nullptr, head);
}

template <typename T>
size_t CircularList<T>::size() const {
    return count;
}

template <typename T>
bool CircularList<T>::empty() const {
    return count == 0;
}

template <typename T>
T& CircularList<T>::front() {
    if (empty()) throw std::out_of_range("CircularList::front: empty list");
    return head->data;
}

template <typename T>
const T& CircularList<T>::front() const {
    if (empty()) throw std::out_of_range("CircularList::front: empty list");
    return head->data;
}

template <typename T>
T& CircularList<T>::back() {
    if (empty()) throw std::out_of_range("CircularList::back: empty list");
    return head->prev->data;
}

template <typename T>
const T& CircularList<T>::back() const {
    if (empty()) throw std::out_of_range("CircularList::back: empty list");
    return head->prev->data;
}

template <typename T>
void CircularList<T>::clear() {
    while (!empty()) pop_front();
}

template <typename T>
void CircularList<T>::swap(CircularList& other) {
    std::swap(head, other.head);
    std::swap(count, other.count);
}

template <typename T>
CircularList<T>::iterator::iterator(Node* n, Node* h) : node(n), head(h) {
}

template <typename T>
T& CircularList<T>::iterator::operator*() {
    return node->data;
}

template <typename T>
typename CircularList<T>::iterator& CircularList<T>::iterator::operator++() {
    if (node) node = node->next;
    return *this;
}

template <typename T>
typename CircularList<T>::iterator& CircularList<T>::iterator::operator--() {
    if (node) node = node->prev;
    return *this;
}

template <typename T>
bool CircularList<T>::iterator::operator==(const iterator& other) const {
    return node == other.node;
}

template <typename T>
bool CircularList<T>::iterator::operator!=(const iterator& other) const {
    return node != other.node;
}

#endif
