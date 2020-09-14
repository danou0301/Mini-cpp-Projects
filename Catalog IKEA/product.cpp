
#include <iomanip>
#include "product.h"

#define ASK_QUANTITY "Please enter desired quantity: "
#define ASK_NUM_ITEM "Please enter number of items: "
/**
 * getter item
 * @return
 */
int product::getItem() const
{
    return _item;
}
/**
 * getter name
 * @return
 */
const string &product::getName() const
{
    return _name;
}
/**
 * parse double
 * @param line
 * @param start
 * @param end
 * @return
 */
double getdouble(string &line, unsigned long start, unsigned long end)
{
    for (unsigned long i = start; i < end - 1; ++i)
    {
        int pointCount = 0;
        if (line[i] == '.')
        {
            pointCount++;
        }
        if (!isdigit(line[i]) && (line[i] != '.' || pointCount > 1))
        {
            exit(1);
        }
    }
    return stod(line.substr(start, end));
}
/**
 * constructor of product
 * @param item
 * @param name
 * @param price
 */
product::product(int item, string name, double price) :
        _item(item), _name(name), _priceByUnit(price)
{}
/**
 * print product
 * @param os
 */
void product::print(ostream &os) const
{
    os << "Item: " << _item << endl;
    os << "Name: " << _name << endl;
}
/**
 * constructor of itemUnit
 * @param item
 * @param name
 * @param price
 * @param quantity
 */
itemUnit::itemUnit(int item, string name, double price, int quantity) :
        product(item, name, price), _quantity(quantity)
{}
/**
 * print product
 * @param os
 */
void itemUnit::print(ostream &os) const
{
    product::print(os);
    os << "Quantity: " << _quantity << endl;
    os << "Price: " << setprecision(2) << fixed << _priceByUnit << endl;
}
/**
 * print sell message
 */
void itemUnit::printSellMsg() const
{
    cout << ASK_NUM_ITEM;
}
/**
 * method thqt sell an item
 * @param toSell
 * @return
 */
bool itemUnit::sellItem(double toSell)
{
    toSell = (int) toSell;
    if (toSell <= _quantity)
    {
        _quantity -= (int) toSell;
        return true;
    }
    return false;
}
/**
 * add quantity
 * @param add
 */
void itemUnit::addQuantity(double add)
{
    _quantity += (int) add;
}
/**
 * constructor
 * @param item
 * @param name
 * @param price
 * @param quantity
 */
continuousItem::continuousItem(int item, string name, double price, double quantity) :
        product(item, name, price), _quantity(quantity)
{}
/**
 * print continuous item
 * @param os
 */
void continuousItem::print(ostream &os) const
{
    product::print(os);
    os << "Quantity: " << setprecision(2) << fixed << _quantity << endl;
    os << "Price: " << _priceByUnit << endl;
}
/**
 * print sell message
 */
void continuousItem::printSellMsg() const
{
    cout << ASK_QUANTITY;
}
/**
 * sell an continuous item
 * @param toSell
 * @return
 */
bool continuousItem::sellItem(double toSell)
{
    if (toSell <= _quantity)
    {
        _quantity -= toSell;
        return true;
    }
    return false;
}
/**
 * add quantity
 * @param add
 */
void continuousItem::addQuantity(double add)
{
    _quantity += add;
}

/**
 * constructor of candy
 * @param item
 * @param name
 * @param price
 * @param quantity
 * @param calories
 */
candy::candy(int item, string name, double price, double quantity, double calories) :
        continuousItem(item, name, price, quantity), _calories(calories)
{
}
/**
 * print candy
 * @param os
 */
void candy::print(ostream &os) const
{
    continuousItem::print(os);
    os << "Calories: " << _calories << endl;
    os << SEPARATOR << endl;

}
/**
 * cloth constructor
 * @param item
 * @param name
 * @param price
 * @param quantity
 * @param weight
 */
cloth::cloth(int item, string name, double price, double quantity, double weight) :
        continuousItem(item, name, price, quantity), _weight(weight)
{}
/**
 * print cloth
 * @param os
 */
void cloth::print(ostream &os) const
{
    continuousItem::print(os);
    os << "Weight: " << _weight << endl;
    os << SEPARATOR << endl;

}

/**
 * dimensional constructor
 * @param item
 * @param name
 * @param price
 * @param quantity
 * @param dimensions
 */
dimensional::dimensional(int item, string name, double price, int quantity, string dimensions) :
        itemUnit(item, name, price, quantity)
{
    unsigned long firstSpace = dimensions.find(' ');
    unsigned long secondSpace = dimensions.find(' ', firstSpace + 1);
    _x = getdouble(dimensions, 0, firstSpace);
    _y = getdouble(dimensions, firstSpace + 1, secondSpace);
    _z = getdouble(dimensions, secondSpace + 1, dimensions.length());

}
/**
 * print dimensional object
 * @param os
 */
void dimensional::print(ostream &os) const
{
    itemUnit::print(os);
    os << "Dimensions: " << _x << " " << _y << " " << _z << endl;
}
/**
 * utensil constructor
 * @param item
 * @param name
 * @param price
 * @param quantity
 * @param dimension
 * @param capacity
 */
utensil::utensil(int item, string name, double price, int quantity, string dimension, double capacity) :
        dimensional(item, name, price, quantity, dimension), _capacity(capacity)
{}
/**
 * print utensil
 * @param os
 */
void utensil::print(ostream &os) const
{
    dimensional::print(os);
    os << "Capacity: " << _capacity << endl;
    os << SEPARATOR << endl;

}
/**
 * tableChair constructor
 * @param item
 * @param name
 * @param price
 * @param quantity
 * @param dimension
 * @param material
 * @param color
 */
tableChair::tableChair(int item, string name, double price, int quantity, string dimension, string material,
                       string color) :
        dimensional(item, name, price, quantity, dimension), _material(material), _color(color)
{}
/**
 * print tableChair object
 * @param os
 */
void tableChair::print(ostream &os) const
{
    dimensional::print(os);
    os << "Material: " << _material << endl;
    os << "Color: " << _color << endl;
    os << SEPARATOR << endl;

}
/**
 * bookMovies constructor
 * @param item
 * @param name
 * @param price
 * @param quantity
 * @param author
 * @param year
 * @param length
 */
bookMovies::bookMovies(int item, string name, double price, int quantity, string author, int year, int length) :
        itemUnit(item, name, price, quantity), _author(author), _year(year), _length(length)
{}
/**
 * print bookMovies object
 * @param os
 */
void bookMovies::print(ostream &os) const
{
    itemUnit::print(os);
    os << "Author: " << _author << endl;
    os << "Year of publication: " << _year << endl;
    os << "Length: " << _length << endl;
    os << SEPARATOR << endl;

}