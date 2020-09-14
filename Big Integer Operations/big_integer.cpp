#include <iostream>
#include <algorithm>
#include "big_integer.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Big Integer.
// --------------------------------------------------------------------------------------

/**
 * The default constructor.
 */
big_integer::big_integer()
{
    _data = "0";
    _sign = 1;
}

/**
 * The copy constructor.
 * @param bInt to copy
 */
big_integer::big_integer(const big_integer &bInt)
{
    _data = bInt._data; // todo check deep copy
    _sign = bInt._sign;
}

/**
 * A constructor with an int
 * @param a
 */
big_integer::big_integer(int a)
{
    if (a >= 0)
    {
        _sign = POSITIVE;
    }
    else
    {
        _sign = NEGATIVE;
    }
    a *= _sign;
    _data = std::to_string(a);
    std::reverse(_data.begin(), _data.end());
}

/**
 * helper method that clean zero at the initialisation
 * @param result
 */
void cleanZerosInit(std::string &result)
{
    unsigned long i = 0;
    while (i < result.length() - 1)
    {
        if (result[i] == '0')
        {
            i++;
        }
        else
        {
            break;
        }
    }
    result = result.substr(i, result.length());
}
/**
 * A constructor with a string
 * @param data
 */
big_integer::big_integer(const std::string &data)
{
    std::string relevantData;
    if (data[0] == MINUS_SIGN)
    {
        _sign = NEGATIVE;
        relevantData = data.substr(1, data.length() - 1);
    }
    else
    {
        _sign = POSITIVE;
        relevantData = data;
    }
    for (unsigned int i = 0; i < relevantData.length(); i++)
    {
        // check string validity
        if (!std::isdigit(relevantData[i]))
        {
            _data = "0";
            _sign = POSITIVE;
            return;
        }
    }
    cleanZerosInit(relevantData);
    if (relevantData.length() == 0)
    {
        _data = "0";
        _sign = POSITIVE;
        return;
    }
    if (relevantData[0] == '0')
    {
        _data = "0";
        _sign = POSITIVE;
    }
    else
    {
        std::reverse(relevantData.begin(), relevantData.end());
        _data = relevantData;
    }

}
// ------------------ Access methods ------------------------
/**
 * Access method for the data value.
 * @return The data value
 */
const std::string &big_integer::getData() const
{
    return _data;
}

/**
 * Access method for the sign value.
 * @return The sign value
 */
int big_integer::getSign() const
{
    return _sign;
}
/**
 * set the data value
 * @param newData
 */
void big_integer::setData(std::string newData)
{
    _data = newData;
}
/**
 * set the sign value
 * @param newSign
 */
void big_integer::setSign(int sign)
{
    _sign = sign;
}

// ------------------ Other methods ------------------------
/**
 * compare two big integer with the sign that we want
 * @param first
 * @param second
 * @return 0 if first greater that second , 1 if first smaller than second and 2 if it's equal
 */
int compare(const std::string &firstData, int firstSign, const std::string &secondData, int secondSign)
{
    if (firstSign == NEGATIVE && secondSign == POSITIVE)
    {
        return 1;
    }
    else if (firstSign == POSITIVE && secondSign == NEGATIVE)
    {
        return 0;
    }
    else
    {
        if ((firstData.length() < secondData.length()))
        {
            return firstSign == POSITIVE;
        }
        else if (firstData.length() > secondData.length())
        {
            return firstSign != POSITIVE;
        }
        else
        {
            long i = firstData.length() - 1;
            while (i >= 0)
            {
                if (firstData[i] < secondData[i])
                {
                    return firstSign == POSITIVE;
                }
                else if (firstData[i] > secondData[i])
                {
                    return firstSign != POSITIVE;
                }
                else
                {
                    i--;
                }
            }
            return 2;
        }
    }
}
/**
 * smaller operation
 * @param first
 * @param second
 * @return
 */
bool operator<(const big_integer &first, const big_integer &second)
{
    return compare(first._data, first._sign, second._data, second._sign) == 1;
}
/**
 * greater operation
 * @param first
 * @param second
 * @return
 */
bool operator>(const big_integer &first, const big_integer &second)
{
    return compare(first._data, first._sign, second._data, second._sign) == 0;
}
/**
 * difference operator
 * @param first
 * @param second
 * @return
 */
bool operator!=(const big_integer &first, const big_integer &second)
{
    return ((first > second) || (first < second));
}
/**
* equal operator
* @param first
* @param second
* @return
*/
bool operator==(const big_integer &first, const big_integer &second)
{
    return !(first != second);
}

/**
 * smaller or equal operation
 * @param first
 * @param second
 * @return
 */
bool operator<=(const big_integer &first, const big_integer &second)
{
    return ((first < second) || (first == second));
}
/**
 * greater or equal operation
 * @param first
 * @param second
 * @return
 */
bool operator>=(const big_integer &first, const big_integer &second)
{
    return ((first > second) || (first == second));
}

/**
 * assignment operator
 * @param second
 * @return
 */
big_integer &big_integer::operator=(const big_integer &second) = default;

/**
 * clean zero at the end of the number
 * @param result
 */
void cleanZerosReverse(std::string &result)
{
    long i = result.length() - 1;
    while (i > 0)
    {
        if (result[i] == '0')
        {
            i--;
        }
        else
        {
            break;
        }
    }
    result = result.substr(0, i + 1);
}
/**
 * find the max and the min length of two big integers
 * @param first_data
 * @param second
 * @param maxLength
 * @param minLength
 * @param firstSmaller
 */
void findMinMaxLength(std::string &first_data, const big_integer &second, long &maxLength, long &minLength,
                      int &firstSmaller)
{
    if (first_data.length() > second.getData().length())
    {
        maxLength = first_data.length();
        minLength = second.getData().length();
        firstSmaller = 0;
    }
    else
    {
        maxLength = second.getData().length();
        minLength = first_data.length();
        firstSmaller = 1;
        if (first_data.length() == second.getData().length())
        {
            firstSmaller = 2;
        }

    }
}
/**
 * helper function that sum two positives numbers
 * @param first_data
 * @param second
 */
void positiveSum(std::string &first_data, const big_integer &second)
{
    int addLast = 0, firstSmaller = 0, secondData;
    long maxLength, minLength;
    findMinMaxLength(first_data, second, maxLength, minLength, firstSmaller);
    if (firstSmaller)
    {
        std::string nZero(maxLength - minLength, '0');
        first_data += nZero;
    }

    for (unsigned int i = 0; i < maxLength; ++i)
    {
        if (i >= second.getData().length())
        {
            secondData = 0;
        }
        else
        {
            secondData = second.getData()[i] - '0';
        }


        if (first_data[i] - '0' + secondData + addLast > 9)
        {
            first_data[i] += secondData - 10 + addLast;
            addLast = 1;
        }
        else
        {
            first_data[i] += secondData + addLast;
            addLast = 0;
        }
    }
    first_data += (char) (addLast + '0');
    cleanZerosReverse(first_data);
}

/**
 * helper function that subtract two positives numbers
 * @param first_data
 * @param second
 */
void positiveSub(std::string &first_data, const big_integer &second)
{

    int add = 0;
    for (unsigned int i = 0; i < second.getData().length(); ++i)
    {
        if (first_data[i] - '0' - (second.getData()[i] - '0' + add) < 0)
        {
            first_data[i] += 10 - (second.getData()[i] - '0' + add);
            add = 1;
        }
        else
        {
            first_data[i] -= (second.getData()[i] - '0' + add);
            add = 0;
        }
    }
    for (unsigned long j = second.getData().length(); j < first_data.length(); ++j)
    {
        if (first_data[j] - '0' > 0)
        {
            first_data[j] = (char) ((first_data[j] - '0' - add + 10) % 10 + '0');
            break;
        }
        first_data[j] = (char) ((first_data[j] - '0' - add + 10) % 10 + '0');
    }
    cleanZerosReverse(first_data);

}
/**
 * operator +=
 * @param second
 * @return
 */
big_integer &big_integer::operator+=(const big_integer &second)
{

    std::string dataTemp = second.getData();

    if (this->_sign * second._sign == POSITIVE)
    {
        positiveSum(this->_data, second);
    }
    else
    {
        if (compare(this->_data, POSITIVE, second._data, POSITIVE) == 0)
        {// first greater than the second
            positiveSub(this->_data, second);

        }
        else if (compare(this->_data, POSITIVE, second._data, POSITIVE) == 1)
        { // first smaller than the second
            positiveSub(dataTemp, *this);
            this->_sign *= -1;
            this->_data = dataTemp;
        }
        else
        {
            this->_data = '0';
            this->_sign = POSITIVE;
        }
    }

    return *this;
}

/**
* operator +
* @param first
* @param second
* @return the sum of the two big integer
*/
big_integer operator+(const big_integer &first, const big_integer &second)
{
    big_integer result(first);
    result += second;
    return result;
}
/**
 * operator -=
 * @param second
 * @return
 */
big_integer &big_integer::operator-=(const big_integer &second)
{

    big_integer secondTemp(second);
    secondTemp._sign *= -1;
    *this += secondTemp;

    return *this;
}
/**
 * operator -
 * @param first
 * @param second
 * @return the substraction of the two big integer
 */
big_integer operator-(const big_integer &first, const big_integer &second)
{
    big_integer result(first);
    result -= second;
    return result;
}
/**
 * print operator
 * @param os
 * @param first
 * @return
 */
std::ostream &operator<<(std::ostream &os, const big_integer &first)
{
    std::string dataToPrint = first._data;
    std::reverse(dataToPrint.begin(), dataToPrint.end());
    if (first._sign == -1)
    {
        os << "-" + dataToPrint;
    }
    else
    {
        os << dataToPrint;
    }
    return os;
}
/**
 * helper function that do the product of two positives numbers
 * @param first
 * @param second
 * @return
 */
big_integer doProduct(const std::string &first, const std::string &second)
{
    std::string resultLine;
    big_integer result;
    if (first == "0" || second == "0")
    {
        return result;
    }
    int add = 0;
    for (unsigned int i = 0; i < second.length(); ++i)
    {
        for (unsigned int j = 0; j < first.length(); ++j)
        {
            int product = (second[i] - '0') * (first[j] - '0');

            if (product + add > 9)
            {
                resultLine += (char) ((product + add) % 10 + '0');
                add = (product + add) / 10;
            }
            else
            {
                resultLine += (char) (product + '0' + add);
                add = 0;
            }
        }
        if (add > 0)
        {
            resultLine += (char) (add + '0');
            add = 0;
        }
        std::reverse(resultLine.begin(), resultLine.end());
        big_integer bigA(resultLine);
        result += bigA;
        std::string newLine(i + 1, '0');
        resultLine = newLine;
    }
    return result;
}
/**
* product operator with assignment
* @param second
* @return
*/
big_integer &big_integer::operator*=(const big_integer &second)
{
    int sign = this->getSign() * second.getSign();
    if (this->getData() == "0" || second.getData() == "0")
    {
        sign = 1;
    }
    if (this->getData().length() > second.getData().length())
    {
        *this = doProduct(this->getData(), second.getData());
    }
    else
    {
        *this = doProduct(second.getData(), this->getData());
    }
    this->_sign = sign;
    return *this;
}
/**
 * product operator
 * @param first
 * @param second
 * @return
 */
big_integer operator*(const big_integer &first, const big_integer &second)
{
    big_integer result(first);
    result *= second;
    return result;
}
/**
 * return the reminder
 * @param dividePart
 * @param k
 * @param divisor
 * @return
 */
big_integer getReminder(big_integer &dividePart, big_integer &k, const big_integer &divisor)
{
    if (divisor.getSign() == 1)
    {
        return dividePart - (k * divisor);
    }
    else
    {
        return dividePart + (k * divisor);
    }
}
/**
 * update the reminder and the result
 * @param dividePart
 * @param divisor
 * @param result
 * @param reminder
 * @param k
 */
void updateResultAndReminder(big_integer& dividePart, const big_integer& divisor, std::string &result,
                             big_integer &reminder, big_integer &k)
{
    while (compare(dividePart.getData(), POSITIVE, (divisor * k).getData(), POSITIVE) != 1)
    {
        k += 1;
    }
    k -= 1;
    result += k.getData();
    reminder = getReminder(dividePart, k, divisor);
}
/**
 * helper function that do the division of two positives numbers
 * @param first
 * @param divisor
 * @param reminder
 * @return the divide number
 */
big_integer doDivide(const std::string &first, const big_integer &divisor, big_integer &reminder)
{
    unsigned long divideLength = divisor.getData().length();
    unsigned long i = first.length();
    int flag = 0;
    std::string result = "";
    big_integer k(0);
    if (divisor.getData() == "0" || first == "0")
    { // check divide by 0 or less that 0
        reminder = k;
        return k;
    }
    if (compare(first, POSITIVE, divisor.getData(), POSITIVE) == 1)
    {
        reminder.setData(first);
        return k;
    }

    std::string stringPart = first.substr(i - divideLength, divideLength);
    std::reverse(stringPart.begin(), stringPart.end());
    big_integer dividePart(stringPart);

    if (compare(dividePart.getData(), POSITIVE, divisor.getData(), POSITIVE) == 1)
    {
        flag = 1;

    }
    dividePart.setData(first.substr(i - divideLength - flag, divideLength + flag));
    updateResultAndReminder(dividePart, divisor, result, reminder, k);

    i -= flag + divideLength;
    while (i > 0)
    {
        i--;
        k = 0;
        dividePart.setData(reminder.getData() != "0" ? first.substr(i, 1) + reminder.getData() : first.substr(i, 1));
        updateResultAndReminder(dividePart, divisor, result, reminder, k);
    }
    return big_integer(result);
}
/**
 * divide operator with assignment
 * @param second
 * @return
 */
big_integer &big_integer::operator/=(const big_integer &second)
{

    int sign = this->getSign() * second.getSign();
    big_integer reminder(0);
    *this = doDivide(this->_data, second, reminder);
    if (this->getData() != "0")
    {
        this->_sign = sign;
    }
    return *this;
}
/**
 * divide operator with assignment
 * @param second
 * @return
 */
big_integer operator/(const big_integer &first, const big_integer &second)
{
    big_integer result(first);
    result /= second;
    return result;
}
/**
 * the modulo operator
 * @param first
 * @param second
 * @return
 */
big_integer operator%(const big_integer &first, const big_integer &second)
{
    big_integer reminder(0);
    doDivide(first.getData(), second, reminder);
    if (reminder.getData() != "0")
    {
        reminder.setSign(first.getSign());
    }
    return reminder;
}

