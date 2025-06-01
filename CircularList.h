/**
 * @mainpage CircularList - Implementation of a Circular Doubly Linked List
 * 
 * @section overview Overview
 * CircularList is a template class implementing a circular doubly linked list.
 * The list supports all basic STL container operations and provides
 * bidirectional iterators.
 * 
 * @section features Key Features
 * - Insertion and deletion of elements at the beginning and end of the list
 * - Insertion and deletion of elements at arbitrary positions
 * - Bidirectional iteration
 * - Support for constant iterators
 * - Support for reverse iterators
 * - List comparison operations
 * 
 * @section usage Usage Example
 * @code
 * CircularList<int> list;
 * list.push_back(1);
 * list.push_back(2);
 * list.push_front(0);
 * 
 * for (const auto& value : list) {
 *     std::cout << value << " ";
 * }
 * @endcode
 * 
 * @section complexity Operation Complexity
 * - Access to first and last element: O(1)
 * - Insertion/deletion at beginning/end: O(1)
 * - Insertion/deletion at arbitrary position: O(1)
 * - Element search: O(n)
 * 
 * @author Platon Lukyanov
 * @version 1.0
 */

#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <stdexcept>

/**
 * @brief Template class for a circular doubly linked list
 * 
 * @tparam T Type of elements stored in the list
 * 
 * The class implements a circular doubly linked list with support for all basic
 * STL container operations. Each element in the list contains pointers to
 * the previous and next elements, with the last element linked to the first,
 * forming a circular structure.
 */
template <typename T>
class CircularList {
    private:
        /**
         * @brief Node structure for the list
         * 
         * Represents an element of the circular doubly linked list.
         * Each node contains data and pointers to the previous and next nodes.
         */
        struct Node {
                T data;        ///< Data stored in the node
                Node* next;    ///< Pointer to the next node
                Node* prev;    ///< Pointer to the previous node

                /**
                 * @brief Node constructor
                 * 
                 * @param value Value to initialize the node's data
                 * 
                 * Creates a new node with the specified value and initializes
                 * pointers to itself, forming a circular structure.
                 */
                Node(const T& value) : data(value), next(this), prev(this) {}
        };

        Node* head;    ///< Pointer to the head node of the list
        size_t count;  ///< Number of elements in the list

    public:
        /**
         * @brief Default constructor
         * 
         * Creates an empty list
         */
        CircularList();

        /**
         * @brief Copy constructor
         * 
         * @param other List to copy from
         * 
         * Creates a new list by copying all elements from other
         */
        CircularList(const CircularList& other);

        /**
         * @brief Move constructor
         * 
         * @param other List to move elements from
         * 
         * Moves elements from other to the new list
         */
        CircularList(CircularList&& other) noexcept;

        /**
         * @brief Destructor
         * 
         * Frees all memory allocated by the list
         */
        ~CircularList();

        /**
         * @brief Copy assignment operator
         * 
         * @param other List to copy from
         * @return Reference to the current list
         */
        CircularList& operator=(const CircularList& other);

        /**
         * @brief Move assignment operator
         * 
         * @param other List to move elements from
         * @return Reference to the current list
         */
        CircularList& operator=(CircularList&& other) noexcept;

        /**
         * @brief Iterator class for CircularList
         * 
         * Implements a bidirectional iterator for traversing list elements.
         * Supports increment, decrement, and dereference operations.
         */
        class iterator
            : public std::iterator<std::bidirectional_iterator_tag, T> {
                Node* node;
                Node* head;

            public:
                /**
                 * @brief Iterator constructor
                 * 
                 * @param n Pointer to a list node
                 * @param h Pointer to the head node of the list
                 */
                iterator(Node* n = nullptr, Node* h = nullptr);

                /**
                 * @brief Dereference operator
                 * 
                 * @return Reference to the node's value
                 * @throw std::out_of_range if iterator points to end of list
                 */
                T& operator*();

                /**
                 * @brief Prefix increment operator
                 * 
                 * @return Reference to iterator after increment
                 * @throw std::out_of_range if iterator points to end of list
                 */
                iterator& operator++();

                /**
                 * @brief Prefix decrement operator
                 * 
                 * @return Reference to iterator after decrement
                 * @throw std::out_of_range if list is empty
                 */
                iterator& operator--();

                /**
                 * @brief Equality comparison operator
                 * 
                 * @param other Iterator to compare with
                 * @return true if iterators point to the same node
                 */
                bool operator==(const iterator& other) const;

                /**
                 * @brief Inequality comparison operator
                 * 
                 * @param other Iterator to compare with
                 * @return true if iterators point to different nodes
                 */
                bool operator!=(const iterator& other) const;

                friend class CircularList;
        };

        /**
         * @brief Constant iterator class for CircularList
         * 
         * Implements a bidirectional constant iterator for traversing list elements.
         * Supports increment, decrement, and dereference operations.
         * Does not allow modification of element values.
         */
        class const_iterator
            : public std::iterator<std::bidirectional_iterator_tag, const T> {
                Node* node;
                Node* head;

            public:
                /**
                 * @brief Constant iterator constructor
                 * 
                 * @param n Pointer to a list node
                 * @param h Pointer to the head node of the list
                 */
                const_iterator(Node* n = nullptr, Node* h = nullptr);

                /**
                 * @brief Dereference operator
                 * 
                 * @return Constant reference to the node's value
                 * @throw std::out_of_range if iterator points to end of list
                 */
                const T& operator*() const;

                /**
                 * @brief Prefix increment operator
                 * 
                 * @return Reference to iterator after increment
                 * @throw std::out_of_range if iterator points to end of list
                 */
                const_iterator& operator++();

                /**
                 * @brief Prefix decrement operator
                 * 
                 * @return Reference to iterator after decrement
                 * @throw std::out_of_range if list is empty
                 */
                const_iterator& operator--();

                /**
                 * @brief Equality comparison operator
                 * 
                 * @param other Iterator to compare with
                 * @return true if iterators point to the same node
                 */
                bool operator==(const const_iterator& other) const;

                /**
                 * @brief Inequality comparison operator
                 * 
                 * @param other Iterator to compare with
                 * @return true if iterators point to different nodes
                 */
                bool operator!=(const const_iterator& other) const;

                friend class CircularList;
        };

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        /**
         * @brief Returns an iterator to the first element
         * 
         * @return Iterator pointing to the first element of the list
         */
        iterator begin();

        /**
         * @brief Returns an iterator to the element after the last
         * 
         * @return Iterator pointing to the position after the last element
         */
        iterator end();

        /**
         * @brief Returns a constant iterator to the first element
         * 
         * @return Constant iterator pointing to the first element of the list
         */
        const_iterator begin() const;

        /**
         * @brief Returns a constant iterator to the element after the last
         * 
         * @return Constant iterator pointing to the position after the last element
         */
        const_iterator end() const;

        /**
         * @brief Returns a constant iterator to the first element
         * 
         * @return Constant iterator pointing to the first element of the list
         */
        const_iterator cbegin() const;

        /**
         * @brief Returns a constant iterator to the element after the last
         * 
         * @return Constant iterator pointing to the position after the last element
         */
        const_iterator cend() const;

        /**
         * @brief Returns a reverse iterator to the last element
         * 
         * @return Reverse iterator pointing to the last element of the list
         */
        reverse_iterator rbegin();

        /**
         * @brief Returns a reverse iterator to the element before the first
         * 
         * @return Reverse iterator pointing to the position before the first element
         */
        reverse_iterator rend();

        /**
         * @brief Returns a constant reverse iterator to the last element
         * 
         * @return Constant reverse iterator pointing to the last element of the list
         */
        const_reverse_iterator rbegin() const;

        /**
         * @brief Returns a constant reverse iterator to the element before the first
         * 
         * @return Constant reverse iterator pointing to the position before the first element
         */
        const_reverse_iterator rend() const;

        /**
         * @brief Returns a constant reverse iterator to the last element
         * 
         * @return Constant reverse iterator pointing to the last element of the list
         */
        const_reverse_iterator crbegin() const;

        /**
         * @brief Returns a constant reverse iterator to the element before the first
         * 
         * @return Constant reverse iterator pointing to the position before the first element
         */
        const_reverse_iterator crend() const;

        /**
         * @brief Returns the number of elements in the list
         * 
         * @return Number of elements
         */
        size_t size() const;

        /**
         * @brief Checks if the list is empty
         * 
         * @return true if the list is empty, false otherwise
         */
        bool empty() const;

        /**
         * @brief Returns a reference to the first element
         * 
         * @return Reference to the first element
         * @throw std::out_of_range if the list is empty
         */
        T& front();

        /**
         * @brief Returns a constant reference to the first element
         * 
         * @return Constant reference to the first element
         * @throw std::out_of_range if the list is empty
         */
        const T& front() const;

        /**
         * @brief Returns a reference to the last element
         * 
         * @return Reference to the last element
         * @throw std::out_of_range if the list is empty
         */
        T& back();

        /**
         * @brief Returns a constant reference to the last element
         * 
         * @return Constant reference to the last element
         * @throw std::out_of_range if the list is empty
         */
        const T& back() const;

        /**
         * @brief Adds an element to the end of the list
         * 
         * @param value Value of the element to add
         */
        void push_back(const T& value);

        /**
         * @brief Adds an element to the beginning of the list
         * 
         * @param value Value of the element to add
         */
        void push_front(const T& value);

        /**
         * @brief Removes the last element from the list
         * 
         * @throw std::out_of_range if the list is empty
         */
        void pop_back();

        /**
         * @brief Removes the first element from the list
         * 
         * @throw std::out_of_range if the list is empty
         */
        void pop_front();

        /**
         * @brief Clears the list
         * 
         * Removes all elements from the list
         */
        void clear();

        /**
         * @brief Inserts an element before the specified position
         * 
         * @param pos Iterator pointing to the position before which to insert
         * @param value Value of the element to insert
         * @return Iterator pointing to the inserted element
         */
        iterator insert(iterator pos, const T& value);

        /**
         * @brief Removes the element at the specified position
         * 
         * @param pos Iterator pointing to the element to remove
         * @return Iterator pointing to the next element
         * @throw std::out_of_range if the list is empty
         * @throw std::invalid_argument if the iterator is invalid
         */
        iterator erase(iterator pos);

        /**
         * @brief Replaces the contents of the list with n copies of value
         * 
         * @param n Number of elements
         * @param value Value to copy
         */
        void assign(size_t n, const T& value);

        /**
         * @brief Exchanges the contents of the list with another list
         * 
         * @param other List to exchange contents with
         */
        void swap(CircularList& other) noexcept;

        /**
         * @brief Checks if lists are equal
         * 
         * @param other List to compare with
         * @return true if lists are equal, false otherwise
         */
        bool operator==(const CircularList& other) const;

        /**
         * @brief Checks if lists are not equal
         * 
         * @param other List to compare with
         * @return true if lists are not equal, false otherwise
         */
        bool operator!=(const CircularList& other) const;

        /**
         * @brief Checks if current list is less than other
         * 
         * @param other List to compare with
         * @return true if current list is less than other, false otherwise
         */
        bool operator<(const CircularList& other) const;

        /**
         * @brief Checks if current list is greater than other
         * 
         * @param other List to compare with
         * @return true if current list is greater than other, false otherwise
         */
        bool operator>(const CircularList& other) const;

        /**
         * @brief Checks if current list is less than or equal to other
         * 
         * @param other List to compare with
         * @return true if current list is less than or equal to other, false otherwise
         */
        bool operator<=(const CircularList& other) const;

        /**
         * @brief Checks if current list is greater than or equal to other
         * 
         * @param other List to compare with
         * @return true if current list is greater than or equal to other, false otherwise
         */
        bool operator>=(const CircularList& other) const;
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
