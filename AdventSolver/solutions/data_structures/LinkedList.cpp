/*  Dev: Dave West
 * Date: December 11, 2024
 * Desc: Method definitions for the linked list data structure.
 */

#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), tail(nullptr), _size(0) {}


LinkedList::LinkedList(int value) : head(new Node(value)), _size(1) { tail = head; }


LinkedList::LinkedList(const std::vector<int> &vec) : head(nullptr), tail(nullptr), _size(0)
{
    for (int item : vec)
        this->insert(item);
}


LinkedList::~LinkedList()
{
    
}


/**
 * 
 * @param value 
 * @param index 
 */
void LinkedList::insert(const int value, const int index)
{
    if (!head)
    {   // First element
        head = new Node(value);
        tail = head;
        ++_size;
        return;
    }

    if(index == -1)
    {   // No index given: add to tail end
        Node *newNode = new Node(value, nullptr, tail);
        Node *prevTail = tail;
        tail = newNode;
        prevTail->next = tail;

        ++_size;
        return;
    }

    Node *currentNode = traverse(index);
        // insert
    Node *prevNode = currentNode->prev;
    Node *newNode = new Node(value, currentNode, prevNode);
    currentNode->prev = newNode;
    prevNode->next = newNode;
    
    ++_size;
}


/**
 * 
 * @param index 
 * @return Value at index, INT_MIN if out-of-bounds.
 */
int LinkedList::remove(int index)
{
    if (index < 0 || index > _size-1)
        return INT_MIN;

    if (_size == 1)
    {
        int value = head->value;
        delete head;
        head = nullptr;
        tail = nullptr;
        --_size;
        return value;
    }

    if (index == 0)
    {
        Node *newHead = head->next;
        int value = head->value;
        delete head;
        --_size;
        head = newHead;

        if (_size == 1)
            tail = head;

        return value;
    }

    if (index == _size-1)
    {
        Node *newTail = tail->prev;
        int value = tail->value;
        delete tail;
        tail = newTail;
        --_size;

        if (_size == 1)
            head = tail;

        return value;
    }

    Node *currentNode = traverse(index);

    currentNode->next->prev = currentNode->prev;
    currentNode->prev->next = currentNode->next;

    int value = currentNode->value;
    delete currentNode;
    return value;
}


/**
 * 
 * @param traverseToIndex 
 * @return Node pointer to index, nullptr if out-of-bounds
 */
LinkedList::Node* LinkedList::traverse(int traverseToIndex) const
{
    if (traverseToIndex < 0 || traverseToIndex > _size-1)
        return nullptr;
    
    int currentIndex = 0;
    Node *currentNode = head;
    
    // Traverse to appropriate index
    while (currentIndex < traverseToIndex)
    {
        currentNode = currentNode->next;
        ++currentIndex;
    }

    return currentNode;
}


/**
 * 
 * @param index 
 * @return Value at index, -1 if out-of-bounds
 */
int LinkedList::getValue(int index) const
{
        // Invalid index
    if (index < 0 || index > _size-1)
        return -1;

    return traverse(index)->value;
}


/**
 * 
 * @param value 
 * @return Index if found, -1 if not found.
 */
int LinkedList::findValue(int value) const
{
    int index {0};
    Node *currentNode = head;
    
        // Traverse to find value 
    while (currentNode->value != value && index < _size-1)
    {
        currentNode->next;
        ++index;
    }

    if (currentNode->value == value)
        return index;

    if (index > _size-1)
        return -1;
}

