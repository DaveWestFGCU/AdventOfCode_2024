/*  Dev: Dave West
 * Date: December 11, 2024
 * Desc: Class declarations for the linked list data structure.
 */

// TODO: Use template datatype
// TODO: Add iterators for range based looping
// TODO: Overload subscript operator for array-like access


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <climits>
#include <vector>

class LinkedList {
    struct Node
    {
        long long value;
        Node* next;
        Node* prev;

        explicit Node(long long _value) : value(_value), next(nullptr), prev(nullptr) {}
        Node(long long _value, Node *_next, Node *_prev) : value(_value), next(_next), prev(_prev) {}
    };

    Node *head;
    Node *tail;
    size_t _size;

    [[nodiscard]] Node* traverse(int index) const;

public:
    LinkedList();
    explicit LinkedList(long long value);
    explicit LinkedList(const std::vector<long long> &vec);
    ~LinkedList();

    void insert(long long value, int insertIndex = -1);
    long long remove(int index);
    [[nodiscard]] long long getValue(int index) const;
    bool setValue(int index, long long value);
    [[nodiscard]] int findValue(long long value) const;
    [[nodiscard]] size_t size() const { return _size; };
};



#endif //LINKEDLIST_H
