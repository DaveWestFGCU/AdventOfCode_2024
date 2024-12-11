/*  Dev: Dave West
 * Date: December 11, 2024
 * Desc: Class declarations for the linked list data structure.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <climits>
#include <vector>

class LinkedList {
    struct Node
    {
        int value;
        Node* next;
        Node* prev;

        explicit Node(int _value) : value(_value), next(nullptr), prev(nullptr) {}
        Node(int _value, Node *_next, Node *_prev) : value(_value), next(_next), prev(_prev) {}
    };

    Node *head;
    Node *tail;
    int size;

    [[nodiscard]] Node* traverse(int index) const;

public:
    LinkedList();
    explicit LinkedList(int value);
    explicit LinkedList(const std::vector<int> &vec);
    ~LinkedList();

    void insert(int value, int insertIndex = -1);
    int remove(int index);
    [[nodiscard]] int getValue(int index) const;
    [[nodiscard]] int findValue(int value) const;
};



#endif //LINKEDLIST_H
