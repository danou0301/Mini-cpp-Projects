#include <iostream>

#ifndef EX2_PRODUCT_H
#define EX2_PRODUCT_H
#define SEPARATOR "-----"

using namespace std;

// -------------------------------------
// Implementation of the class product.
// -------------------------------------
/**
 * the class that represent all products that are sold in ikea
 */
class product
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     */
    product(int item, string name, double price);

    /**
     * Destructor
     */
    virtual ~product() = default;

    /**
     * getter to item number
     * @return
     */
    int getItem() const;

    /**
     * get to the name of the product
     * @return
     */
    const string &getName() const;

    /**
     * print the basic features of the object
     * @param os
     */
    virtual void print(ostream &os) const;
    /**
     * print the sell message
     */
    virtual void printSellMsg() const = 0;

    /**
     * sell an item
     * @param toSell
     * @return
     */
    virtual bool sellItem(double toSell) = 0;

    /**
     * add quantity to an existing product
     * @param add
     */
    virtual void addQuantity(double add) = 0;


protected:
    int _item;
    string _name;
    double _priceByUnit;



};

// -------------------------------------
// Implementation of the class itemUnit.
// -------------------------------------
/**
 * class that represent an item that sell by unit
 */
class itemUnit : public product
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     */
    itemUnit(int item, string name, double price, int quantity);

    /**
     * call print method of the product object and print the itemUnit features
     * @param os
     */
    virtual void print(ostream &os) const override;

    /**
     * print sell msg
     */
    void printSellMsg() const override;

    /**
     * sell an item
     * @param toSell
     * @return
     */
    virtual bool sellItem(double toSell) override;

    /**
     * add quantity to an existing product
     * @param add
     */
    virtual void addQuantity(double add) override;

protected:
    int _quantity;
};

// --------------------------------------------
// Implementation of the class continuousItem.
// --------------------------------------------
/**
 * class that represent an item that sell by quantity
 */
class continuousItem : public product
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     */
    continuousItem(int item, string name, double price, double quantity);

    /**
     * print the features of the object
     * @param os
     */
    virtual void print(ostream &os) const override;

    /**
     * print sell message
     */
    void printSellMsg() const override;

    /**
     * sell an item
     * @param toSell
     * @return
     */
    bool sellItem(double toSell) override;

    /**
     * add quantity to an existing object
     * @param add
     */
    void addQuantity(double add) override;


protected:
    double _quantity;
};

// -----------------------------------
// Implementation of the class candy.
// -----------------------------------
/**
 * candy class
 */
class candy : public continuousItem
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     * @param calories
     */
    candy(int item, string name, double price, double quantity, double calories);

    /**
     * print the features of the object
     * @param os
     */
    void print(ostream &os) const override;

private:
    double _calories;
};

// ----------------------------------
// Implementation of the class cloth.
// ----------------------------------
/**
 * cloth class
 */
class cloth : public continuousItem
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     * @param weight
     */
    cloth(int item, string name, double price, double quantity, double weight);

    /**
     * print the features of the object
     * @param os
     */
    void print(ostream &os) const override;

private:
    double _weight;
};

// ----------------------------------------
// Implementation of the class dimensional.
// ----------------------------------------
/**
 * class of dimensional item
 */
class dimensional : public itemUnit
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     * @param dimension
     */
    dimensional(int item, string name, double price, int quantity, string dimensions);

    /**
     * print the features of the object
     * @param os
     */
    virtual void print(ostream &os) const;

protected:
    double _x, _y, _z;
};

// -------------------------------------
// Implementation of the class utensil.
// -------------------------------------
/**
 * utensil class
 */
class utensil : public dimensional
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     * @param dimension
     * @param capacity
     */
    utensil(int item, string name, double price, int quantity, string dimension, double capacity);

    /**
     * print the features of the object
     * @param os
     */
    void print(ostream &os) const override;

private:

    double _capacity;
};

// ---------------------------------------
// Implementation of the class tableChair.
// ---------------------------------------
/**
 * tableChair class
 */
class tableChair : public dimensional
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     * @param dimension
     * @param material
     * @param color
     */
    tableChair(int item, string name, double price, int quantity, string dimension, string material, string color);

    /**
     * print the features of the object
     * @param os
     */
    void print(ostream &os) const override;

private:

    string _material, _color;
};

// ---------------------------------------
// Implementation of the class bookMovies.
// ---------------------------------------
/**
 * bookMovies class
 */
class bookMovies : public itemUnit
{
public:
    /**
     * constructor
     * @param item
     * @param name
     * @param price
     * @param quantity
     * @param author
     * @param year
     * @param length
     */
    bookMovies(int item, string name, double price, int quantity, string author, int year, int length);

    /**
     * print the features of the object
     * @param os
     */
    void print(ostream &os) const override;

private:
    string _author;
    int _year, _length;
};

#endif //EX2_PRODUCT_H