/*  Dev: Dave West
 * Date: December 11, 2024
 * Desc: Method definitions for the linked list data structure.
 */

#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), tail(nullptr), _size(0) {}


LinkedList::LinkedList(long long value) : head(new Node(value)), _size(1) { tail = head; }


LinkedList::LinkedList(const std::vector<long long> &vec) : head(nullptr), tail(nullptr), _size(0)
{
    for (long long item : vec)
        this->insert(item);
}


LinkedList::~LinkedList()
{   // Deletes middle-out because I'm re-watching Silicon Valley rn
    int midpoint = _size/2;
    Node *nodeTowardsTail = traverse(midpoint);
    Node *nodeTowardsHead = nodeTowardsTail->prev;


    while (head || tail)
    {
        if (head)
        {
            if (head == nodeTowardsHead)
            {
                delete nodeTowardsHead;
                head = nullptr;
            }
            else
            {
                nodeTowardsHead = nodeTowardsHead->prev;
                delete nodeTowardsHead->next;
            }
        }

        if(tail)
        {
            if (tail == nodeTowardsTail)
            {
                delete nodeTowardsTail;
                tail = nullptr;
            }
            else
            {
                nodeTowardsTail = nodeTowardsTail->next;
                delete nodeTowardsTail->prev;
            }
        }
    }
}


/**
 * 
 * @param value 
 * @param index 
 */
void LinkedList::insert(const long long value, const int index)
{
    if (!head)
    {   // First element
        head = new Node(value);
        tail = head;
        ++_size;
        return;
    }

    if (index == 0)        //  New head
    {
        Node *newNode = new Node(value, head, nullptr);
        head->prev = newNode;
        head = newNode;
        ++_size;
        return;
    }

    if(index == -1 || index == _size)    //  No index given: add to tail
    {
        Node *newNode = new Node(value, nullptr, tail);
        tail->next = newNode;
        tail = newNode;

        ++_size;
        return;
    }

    Node *currentNode = traverse(index);
        //  insert
    Node *newNode = new Node(value, currentNode, currentNode->prev);
    currentNode->prev->next = newNode;
    currentNode->prev = newNode;
    
    ++_size;
}


/**
 * 
 * @param index 
 * @return Value at index, INT_MIN if out-of-bounds.
 */
long long LinkedList::remove(int index)
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

    long long value = currentNode->value;
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
long long LinkedList::getValue(int index) const
{
        // Invalid index
    if (index < 0 || index > _size-1)
        return -1;

    return traverse(index)->value;
}


bool LinkedList::setValue(int index, long long value)
{
    if (index < 0 || index > _size-1)
        return false;

    traverse(index)->value = value;
    return true;
}


/**
 * 
 * @param value 
 * @return Index if found, -1 if not found.
 */
int LinkedList::findValue(long long value) const
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

