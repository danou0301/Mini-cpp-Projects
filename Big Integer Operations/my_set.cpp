#include "my_set.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class my_set.
// --------------------------------------------------------------------------------------
/**
 * default constructor
 */
my_set::my_set()
{
    head = nullptr;
}

/**
 * copy constructor
 * @param other set to copy
 */
my_set::my_set(const my_set &other)
{
    head = nullptr;
    node *currentNode = other.head;
    while (currentNode)
    {
        this->add(currentNode->data);
        currentNode = currentNode->next;
    }
}

/**
 * node constructor
 * @param node next node
 * @param data1 data
 */
my_set::node::node(my_set::node *node, big_integer data1)
{
    next = node;
    data = data1;
}

/**
 * check if a big integer in the set
 * @param other the big integer to look up
 * @return true if find it false if not
 */
bool my_set::is_in_set(const big_integer &other) const
{
    node *currentNode = head;
    while (currentNode)
    {
        if (currentNode->data == other)
        {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}
/**
 * add a big integer in the set
 * @param newBigInteger
 * @return true if we successfully add it
 */
bool my_set::add(big_integer newBigInteger)
{
    if (is_in_set(newBigInteger))
    {
        return false;
    }
    node *currentNode = head;
    node *newNode = new node(nullptr, newBigInteger);

    if (currentNode == nullptr || currentNode->data > newBigInteger)
    {
        newNode->next = head;
        head = newNode;
        return true;
    }
    if (currentNode->next == nullptr)
    {
        newNode->next = head->next;
        head->next = newNode;
        return true;
    }
    while (currentNode->next->data < newBigInteger)
    {
        currentNode = currentNode->next;
        if (currentNode->next == nullptr)
        {
            break;
        }
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    return true;
}

/**
 * remove a big integer from the set
 * @param removeBigInteger
 * @return true if we successfully remove it
 */
bool my_set::remove(big_integer removeBigInteger)
{
    if (!is_in_set(removeBigInteger))
    {
        return false;
    }
    if (head->data == removeBigInteger)
    {
        node *temp = head;
        head = head->next;
        delete (temp);
        return true;
    }
    node *currentNode = head;
    node *previousNode = head;
    while (currentNode->data != removeBigInteger)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;

    }
    previousNode->next = currentNode->next;
    delete (currentNode);
    return true;

}
/**
 * sum all the big integers in the set
 * @return
 */
big_integer my_set::sum_set()
{
    big_integer result;
    node *currentNode = head;
    while (currentNode)
    {
        result += currentNode->data;
        currentNode = currentNode->next;
    }
    return result;
}
/**
 * complement operator
 * @param first
 * @param second
 * @return return a set that contains all the elements of first that are not in second.
 */
my_set operator-(my_set &first, const my_set &second)
{
    my_set result;
    my_set::node *firstCurrentNode = first.head;

    while (firstCurrentNode)
    {
        if (!second.is_in_set(firstCurrentNode->data))
        {
            result.add(firstCurrentNode->data);
        }
        firstCurrentNode = firstCurrentNode->next;
    }
    return result;
}
/**
 * union operator
 * @param first
 * @param second
 * @return the set of the union of the two set
 */
my_set operator|(my_set &first, my_set &second)
{
    my_set result = first; // copy the first set
    my_set::node *current = second.head;
    while (current) // add the second set
    {
        result.add(current->data);
        current = current->next;
    }
    return result;
}
/**
 * inter operator
 * @param first
 * @param second
 * @return return a set of element that are in first and in second
 */
my_set operator&(const my_set &first, const my_set &second)
{
    my_set result;
    my_set::node *currentNodeLval = first.head;
    while (currentNodeLval)
    {
        if (second.is_in_set(currentNodeLval->data))
        {
            result.add(currentNodeLval->data);
        }
        currentNodeLval = currentNodeLval->next;
    }
    return result;
}
/**
 * print operator
 * @param os
 * @param mySet the set to print
 * @return
 */
std::ostream &operator<<(std::ostream &os, const my_set &mySet)
{
    if (!mySet.head)
    {
        os << "\n";
        return os;
    }
    else
    {
        my_set::node *current = mySet.head;
        while (current)
        {
            os << current->data << std::endl;
            current = current->next;
        }
        return os;
    }
}

/**
 * destructor
 */
my_set::~my_set()
{
    node *current = head;
    while (current)
    {
        node *temp = current->next;
        delete (current);
        current = temp;
    }
}

/**
 * assignment operator
 * @param other
 * @return
 */
my_set &my_set::operator=(const my_set &other)
{
    node *current = head;
    while (current)
    {
        node *temp = current->next;
        delete (current);
        current = temp;
    }
    head = nullptr;
    node *newCurrent = other.head;
    while (newCurrent)
    {
        this->add(newCurrent->data);
        newCurrent = newCurrent->next;
    }
    return *this;
}