#ifndef EX1_MY_SET_H
#define EX1_MY_SET_H

#include <ostream>
#include "big_integer.h"

/**
 * my_set class
 */
class my_set
{
    /**
     * node class
     */
    class node
    {
    public:
        node *next;
        big_integer data;

        /**
         * construcor
         */
        node(node *, big_integer);

        /**
         * default constructor
         */
        node() = default;
    };

public:
    /**
     * constructor
     */
    my_set();

    /**
     * destructor
     */
    ~my_set();

    /**
     * copy constructor
     * @param other
     */
    my_set(const my_set &other);

    /**
     * check if a big integer in the set
     * @param other the big integer to look up
     * @return true if find it false if not
     */
    bool is_in_set(const big_integer &other) const;
    /**
     * add a big integer in the set
     * @param newBigInteger
     * @return true if we successfully add it
     */
    bool add(big_integer newBigInteger);

    /**
     * remove a big integer from the set
     * @param removeBigInteger
     * @return true if we successfully remove it
     */
    bool remove(big_integer removeBigInteger);

    /**
     * sum all the big integers in the set
     * @return
     */
    big_integer sum_set();

    /**
     * complement operator
     * @param first
     * @param second
     * @return return a set that contains all the elements of first that are not in second.
     */
    friend my_set operator-(my_set &first, const my_set &second);

    /**
     * union operator
     * @param first
     * @param second
     * @return the set of the union of the two set
     */
    friend my_set operator|(my_set &first, my_set &second);

    /**
     * inter operator
     * @param first
     * @param second
     * @return return a set of element that are in first and in second
     */
    friend my_set operator&(const my_set &first, const my_set &second);

    /**
     * print operator
     * @param os
     * @param mySet the set to print
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const my_set &mySet);

    /**
     * assignment operator
     * @param other
     * @return
     */
    my_set &operator=(const my_set &other);

private:
    node *head;

};

#endif //EX1_MY_SET_H
