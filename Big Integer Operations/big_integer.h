// Created by danou0301 on 8/28/18.
//

#include <ostream>

#define POSITIVE 1
#define NEGATIVE (-1)
#define MINUS_SIGN '-'

#ifndef EX1_BIG_INTEGER_H
#define EX1_BIG_INTEGER_H

/**
 *  A big_integer class.
 *  This class represents a big integer
 */
class big_integer
{
public:
    /**
     * The default constructor.
     */
    big_integer();

    /**
     * The copy constructor.
     * @param bInt to copy
     */
    big_integer(const big_integer &bInt);

    /**
     * A constructor with an int
     * @param a
     */
    big_integer(int a);

    /**
     * A constructor with a string
     * @param data
     */
    big_integer(const std::string &data);

    /**
	 * Access method for the sign value.
	 * @return The sign value
	 */
    int getSign() const;

    /**
	 * Access method for the data value.
	 * @return The data value
	 */
    const std::string &getData() const;

    /**
     * set the sign value
     * @param newSign
     */
    void setSign(int newSign);

    /**
     * set the data value
     * @param newData
     */
    void setData(std::string newData);

    /**
     * operator +=
     * @param second
     * @return
     */
    big_integer &operator+=(const big_integer &second);

    /**
     * operator +
     * @param first
     * @param second
     * @return the sum of the two big integer
     */
    friend big_integer operator+(const big_integer &first, const big_integer &second);

    /**
     * operator -
     * @param first
     * @param second
     * @return the substraction of the two big integer
     */
    friend big_integer operator-(const big_integer &first, const big_integer &second);

    /**
     * operator -=
     * @param second
     * @return
     */
    big_integer &operator-=(const big_integer &second);

    /**
     * product operator
     * @param first
     * @param second
     * @return
     */
    friend big_integer operator*(const big_integer &first, const big_integer &second);

    /**
     * product operator with assignment
     * @param second
     * @return
     */
    big_integer &operator*=(const big_integer &second);

    /**
     * divisor operator
     * @param first
     * @param second
     * @return the division of the two big integers
     */
    friend big_integer operator/(const big_integer &first, const big_integer &second);

    /**
     * divide operator with assignment
     * @param second
     * @return
     */
    big_integer &operator/=(const big_integer &second);

    /**
     * the modulo operator
     * @param first
     * @param second
     * @return
     */
    friend big_integer operator%(const big_integer &first, const big_integer &second);

    /**
     * assignment operator
     * @param second
     * @return
     */
    big_integer &operator=(const big_integer &second);

    /**
     * equal operator
     * @param first
     * @param second
     * @return
     */
    friend bool operator==(const big_integer &first, const big_integer &second);

    /**
     * difference operator
     * @param first
     * @param second
     * @return
     */
    friend bool operator!=(const big_integer &first, const big_integer &second);

    /**
     * greater operation
     * @param first
     * @param second
     * @return
     */
    friend bool operator>(const big_integer &first, const big_integer &second);

    /**
     * greater or equal operation
     * @param first
     * @param second
     * @return
     */
    friend bool operator>=(const big_integer &first, const big_integer &second);

    /**
     * smaller operation
     * @param first
     * @param second
     * @return
     */
    friend bool operator<(const big_integer &first, const big_integer &second);

    /**
     * smaller or equal operation
     * @param first
     * @param second
     * @return
     */
    friend bool operator<=(const big_integer &first, const big_integer &second);

    /**
     * print operator
     * @param os
     * @param first
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const big_integer &first);

private:
    std::string _data;
    int _sign;
};

#endif //EX1_BIG_INTEGER_H
