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
        // Конструкторы
        CircularList();
        CircularList(const CircularList& other);
        CircularList(CircularList&& other) noexcept;
        ~CircularList();

        // Операторы присваивания
        CircularList& operator=(const CircularList& other);
        CircularList& operator=(CircularList&& other) noexcept;

        // Итераторы
        class iterator;
        class const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;

        // Размер и проверка на пустоту
        size_t size() const;
        bool empty() const;

        // Доступ к элементам
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // Модификаторы
        void push_back(const T& value);
        void push_front(const T& value);
        void pop_back();
        void pop_front();
        void clear();
        iterator insert(iterator pos, const T& value);
        iterator erase(iterator pos);
        void assign(size_t n, const T& value);
        void swap(CircularList& other) noexcept;

        // Операторы сравнения
        bool operator==(const CircularList& other) const;
        bool operator!=(const CircularList& other) const;
        bool operator<(const CircularList& other) const;
        bool operator>(const CircularList& other) const;
        bool operator<=(const CircularList& other) const;
        bool operator>=(const CircularList& other) const;

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

        class const_iterator
            : public std::iterator<std::bidirectional_iterator_tag, const T> {
                Node* node;
                Node* head;

            public:
                const_iterator(Node* n = nullptr, Node* h = nullptr);
                const T& operator*() const;
                const_iterator& operator++();
                const_iterator& operator--();
                bool operator==(const const_iterator& other) const;
                bool operator!=(const const_iterator& other) const;
                friend class CircularList;
        };
};

// Конструкторы
template <typename T>
CircularList<T>::CircularList() : head(nullptr), count(0) {
}

template <typename T>
CircularList<T>::CircularList(const CircularList& other)
    : head(nullptr), count(0) {
    if (other.empty()) return;

    try {
        Node* current = other.head;
        if (!current) throw std::runtime_error("Invalid source list head");

        size_t elements_copied = 0;
        do {
            if (!current->next || !current->prev) {
                throw std::runtime_error("Invalid node links in source list");
            }
            push_back(current->data);
            current = current->next;
            elements_copied++;

            if (elements_copied > other.count) {
                throw std::runtime_error("Circular list structure corrupted");
            }
        } while (current != other.head);

        if (elements_copied != other.count) {
            throw std::runtime_error("Element count mismatch during copy");
        }
    } catch (...) {
        clear();
        throw;
    }
}

template <typename T>
CircularList<T>::CircularList(CircularList&& other) noexcept
    : head(other.head), count(other.count) {
    other.head = nullptr;
    other.count = 0;
}

template <typename T>
CircularList<T>::~CircularList() {
    clear();
}

// Операторы присваивания
template <typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList& other) {
    if (this != &other) {
        CircularList temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(CircularList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        count = other.count;
        other.head = nullptr;
        other.count = 0;
    }
    return *this;
}

// Итераторы
template <typename T>
typename CircularList<T>::iterator CircularList<T>::begin() {
    return iterator(head, head);
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::end() {
    return iterator(nullptr, head);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::begin() const {
    return const_iterator(head, head);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::end() const {
    return const_iterator(nullptr, head);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::cbegin() const {
    return begin();
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::cend() const {
    return end();
}

template <typename T>
typename CircularList<T>::reverse_iterator CircularList<T>::rbegin() {
    return reverse_iterator(end());
}

template <typename T>
typename CircularList<T>::reverse_iterator CircularList<T>::rend() {
    return reverse_iterator(begin());
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::rbegin()
    const {
    return const_reverse_iterator(end());
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::rend() const {
    return const_reverse_iterator(begin());
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::crbegin()
    const {
    return rbegin();
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::crend()
    const {
    return rend();
}

// Операторы сравнения
template <typename T>
bool CircularList<T>::operator==(const CircularList& other) const {
    if (size() != other.size()) return false;
    if (empty()) return true;

    auto it1 = begin();
    auto it2 = other.begin();
    size_t elements_compared = 0;

    while (it1 != end() && elements_compared < size()) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
        ++elements_compared;
    }

    return elements_compared == size();
}

template <typename T>
bool CircularList<T>::operator!=(const CircularList& other) const {
    return !(*this == other);
}

template <typename T>
bool CircularList<T>::operator<(const CircularList& other) const {
    if (empty() && other.empty()) return false;
    if (empty()) return true;
    if (other.empty()) return false;

    auto it1 = begin();
    auto it2 = other.begin();
    size_t elements_compared = 0;

    while (it1 != end() && it2 != other.end() &&
           elements_compared < std::min(size(), other.size())) {
        if (*it1 < *it2) return true;
        if (*it2 < *it1) return false;
        ++it1;
        ++it2;
        ++elements_compared;
    }

    return size() < other.size();
}

template <typename T>
bool CircularList<T>::operator>(const CircularList& other) const {
    return other < *this;
}

template <typename T>
bool CircularList<T>::operator<=(const CircularList& other) const {
    return !(other < *this);
}

template <typename T>
bool CircularList<T>::operator>=(const CircularList& other) const {
    return !(*this < other);
}

template <typename T>
void CircularList<T>::pop_back() {
    if (empty()) throw std::out_of_range("CircularList::pop_back: empty list");
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
    if (empty()) throw std::out_of_range("CircularList::pop_front: empty list");
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
    if (empty()) throw std::out_of_range("CircularList::erase: empty list");
    if (pos.node == nullptr)
        throw std::invalid_argument("CircularList::erase: invalid iterator");
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
CircularList<T>::const_iterator::const_iterator(Node* n, Node* h)
    : node(n), head(h) {
}

template <typename T>
const T& CircularList<T>::const_iterator::operator*() const {
    if (!node)
        throw std::out_of_range(
            "CircularList::const_iterator::operator*: dereferencing end "
            "iterator");
    return node->data;
}

template <typename T>
typename CircularList<T>::const_iterator&
CircularList<T>::const_iterator::operator++() {
    if (!node)
        throw std::out_of_range(
            "CircularList::const_iterator::operator++: incrementing end "
            "iterator");
    node = node->next;
    return *this;
}

template <typename T>
typename CircularList<T>::const_iterator&
CircularList<T>::const_iterator::operator--() {
    if (!head)
        throw std::out_of_range(
            "CircularList::const_iterator::operator--: no list");
    if (!node) {
        node = head->prev;
    } else {
        node = node->prev;
    }
    return *this;
}

template <typename T>
bool CircularList<T>::const_iterator::operator==(
    const const_iterator& other) const {
    return node == other.node;
}

template <typename T>
bool CircularList<T>::const_iterator::operator!=(
    const const_iterator& other) const {
    return node != other.node;
}

template <typename T>
CircularList<T>::iterator::iterator(Node* n, Node* h) : node(n), head(h) {
}

template <typename T>
T& CircularList<T>::iterator::operator*() {
    if (!node)
        throw std::out_of_range(
            "CircularList::iterator::operator*: dereferencing end iterator");
    return node->data;
}

template <typename T>
typename CircularList<T>::iterator& CircularList<T>::iterator::operator++() {
    if (!node)
        throw std::out_of_range(
            "CircularList::iterator::operator++: incrementing end iterator");
    node = node->next;
    return *this;
}

template <typename T>
typename CircularList<T>::iterator& CircularList<T>::iterator::operator--() {
    if (!head)
        throw std::out_of_range("CircularList::iterator::operator--: no list");
    if (!node) {
        node = head->prev;
    } else {
        node = node->prev;
    }
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

// Размер и проверка на пустоту
template <typename T>
size_t CircularList<T>::size() const {
    return count;
}

template <typename T>
bool CircularList<T>::empty() const {
    return count == 0;
}

// Доступ к элементам
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

// Модификаторы
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
void CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void CircularList<T>::assign(size_t n, const T& value) {
    clear();
    for (size_t i = 0; i < n; ++i) {
        push_back(value);
    }
}

template <typename T>
void CircularList<T>::swap(CircularList& other) noexcept {
    std::swap(head, other.head);
    std::swap(count, other.count);
}

#endif
