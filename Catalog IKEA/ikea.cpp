#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "product.h"

#define CHOICE1 "1. Input stock from file"
#define CHOICE2 "2. Find item by catalog number"
#define CHOICE3 "3. Find item by name"
#define CHOICE4 "4. Print stock by catalog number"
#define CHOICE5 "5. Print stock by name"
#define CHOICE6 "6. Sell item"
#define EXIT_CHOICE "7. Exit"
#define MSG_ERROR_PARSE "Parse error"
#define ASK_FILE_PATH "please enter file path: "
#define MSG_NOT_FOUND "\nItem not found."
#define MSG_NOT_ENOUGH "Not enough stock to sell.\n"
#define MSG_ASK_NUMBER "please enter catalog number: "
#define MSG_ASK_ID "please enter catalog id: "
#define MSG_ASK_NAME "please enter product name: "
#define SAME_PRODUCT_ERROR "product is already in the stock with different name"
#define CANT_OPEN_FILE "Could not open file."
#define INVALID_INPUT "Not valid input."
using namespace std;

/**
 * that function parse a string number to an int
 * @param line  the line
 * @param start start index of the number
 * @param value the new value of the number
 * @return true if the parse successfully worked
 */
bool getInt(string &line, unsigned int start, int &value)
{
    for (unsigned int i = start; i < line.length(); ++i)
    {
        if (!isdigit(line[i]))
        {
            return false;
        }
    }
    value = stoi(line.substr(start, line.length()));
    return true;
}

/**
 * that function parse a string number to a double
 * @param line  the line
 * @param start start index of the number
 * @param value the new value of the number
 * @return true if the parse successfully worked
 */
bool getDouble(string &line, unsigned int start, double &value)
{
    for (unsigned int i = start; i < line.length(); ++i)
    {
        int pointCount = 0;
        if (line[i] == '.')
        {
            pointCount++;
        }
        if (!isdigit(line[i]) && (line[i] != '.' || pointCount > 1))
        {
            return false;
        }
    }
    value = stod(line.substr(start, line.length()));
    return true;
}

/**
 * this function find a product by this number
 * @param productsList the product list
 * @param item product id
 * @return the found product or null pointer
 */
product *findItemByNumber(vector<product *> &productsList, int &item)
{

    for (unsigned int i = 0; i < productsList.size(); ++i)
    {
        if (productsList[i]->getItem() == item)
        {
            return productsList[i];
        }
    }
    return nullptr;
}

/**
 * parse the four basic feature
 * @param myfile myfile
 * @param line the line that we read
 * @param item product id
 * @param name the name of the product
 * @param quantity  the quantity
 * @param priceByUnit the price
 * @return true if the successfully parse these basic features
 */
bool parseBasicFeature(ifstream &myfile, string &line, int &item, string &name, double &quantity, double &priceByUnit)
{
    int numberOfFeature = 0;
    if (line.find("Item") == 0 && getInt(line, 6, item))
    {
        numberOfFeature++;
    }
    getline(myfile, line);
    if (line.find("Name") == 0)
    {
        name = line.substr(6, line.length());
        numberOfFeature++;
    }
    getline(myfile, line);
    if (line.find("Quantity") == 0 && getDouble(line, 10, quantity))
    {
        numberOfFeature++;
    }
    getline(myfile, line);
    if (line.find("Price") == 0 && getDouble(line, 7, priceByUnit))
    {
        numberOfFeature++;
    }
    if (numberOfFeature != 4)
    {
        return false;
    }
    getline(myfile, line);
    return true;
}

/**
 *  add a product to the list, if it is already in the list add this quantity
 * @param productsList
 * @param item
 * @param quantity
 * @param newProduct
 */
void addProduct(vector<product *> &productsList, int &item, double &quantity, product *newProduct)
{

    product *addProduct = findItemByNumber(productsList, item);
    if (addProduct != nullptr)
    {
        if (newProduct->getName() == addProduct->getName())
        {
            addProduct->addQuantity(quantity);
        }
        else
        {
            cerr << SAME_PRODUCT_ERROR << endl;
        }
        delete newProduct;

    }
    else
    {
        productsList.push_back(newProduct);
    }
}

/**
 * main method that parse a one product
 * @param myfile
 * @param line
 * @param productsList
 * @return true if we successfully parse the product
 */
bool parseProduct(ifstream &myfile, string &line, vector<product *> &productsList)
{

    int item;
    double quantity, priceByUnit;
    string name;

    double weight, calories, capacity;
    string dimensions, material, color, author;
    int year, length;
    if (!parseBasicFeature(myfile, line, item, name, quantity, priceByUnit))
    {
        return false;
    }

    if (line.find("Weight") == 0 && getDouble(line, 8, weight))
    {
        addProduct(productsList, item, quantity, new cloth(item, name, priceByUnit, quantity, weight));
    }
    else if (line.find("Calories") == 0 && getDouble(line, 10, calories))
    {
        addProduct(productsList, item, quantity, new candy(item, name, priceByUnit, quantity, calories));
    }
    else if (line.find("Dimensions") == 0)
    {
        dimensions = line.substr(12, line.length());
        getline(myfile, line);
        if (line.find("Capacity") == 0 && getDouble(line, 10, capacity))
        {
            addProduct(productsList, item, quantity,
                       new utensil(item, name, priceByUnit, (int) quantity, dimensions, capacity));

        }
        else if (line.find("Material") == 0)
        {
            material = line.substr(10, line.length());
            getline(myfile, line);
            if (line.find("Color") == 0)
            {
                color = line.substr(7, line.length());
                addProduct(productsList, item, quantity,
                           new tableChair(item, name, priceByUnit, (int) quantity, dimensions, material, color));
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

    }
    else if (line.find("Author") == 0)
    {
        int bookArgument = 5;
        author = line.substr(8, line.length());
        getline(myfile, line);
        if (line.find("Year of publication") == 0 && getInt(line, 21, year))
        {
            bookArgument++;
            getline(myfile, line);
        }
        if (line.find("Length") == 0 && getInt(line, 8, length))
        {
            bookArgument++;
        }
        if (bookArgument == 7)
        {
            addProduct(productsList, item, quantity,
                       new bookMovies(item, name, priceByUnit, (int) quantity, author, year, length));
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    getline(myfile, line);
    if (line != SEPARATOR)
    {
        productsList.pop_back();
        cerr << MSG_ERROR_PARSE << endl;
        return false;
    }
    return true;
}

/**
 *  parse one file with one or many products
 * @param productsList
 */
void parseFile(vector<product *> &productsList)
{
    string line, fileName;
    cout << ASK_FILE_PATH;
    getline(cin, fileName);
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (!parseProduct(myfile, line, productsList))
            {
                cout << endl;
                return;
            }
        }
        cout << endl;
        myfile.close();
    }
    else
    {
        cout << endl;
        cerr << CANT_OPEN_FILE << endl;
        return;
    }
}

/**
 * ask to the user the product id that he look for and return it
 * @param productsList
 * @return the found product or null pointer
 */
product *askAndFindItemByNumber(vector<product *> &productsList)
{
    string itemInputStr;
    int itemInput;
    getline(cin, itemInputStr);
    if (!getInt(itemInputStr, 0, itemInput))
    {
        cerr << INVALID_INPUT << endl;
        return nullptr;
    }
    else if (findItemByNumber(productsList, itemInput) == nullptr)
    {
        cerr << MSG_NOT_FOUND << endl;
        return nullptr;
    }
    return findItemByNumber(productsList, itemInput);
}

/**
 * ask to the user the product name that he look for and return it
 * @param productsList
 * @return the found product or null pointer
 */
product *findItemByName(vector<product *> &productsList)
{
    cout << MSG_ASK_NAME;
    string itemInputStr;
    getline(cin, itemInputStr);
    for (unsigned int i = 0; i < productsList.size(); ++i)
    {
        if (productsList[i]->getName() == itemInputStr)
        {
            return productsList[i];
        }
    }
    cerr << MSG_NOT_FOUND;
    return nullptr;
}

/**
 * print one product
 * @param myProduct
 */
void printProduct(product *myProduct)
{
    if (myProduct != nullptr)
    {
        myProduct->print(cout);
    }
    cout << endl;
}

/**
 * print all the products on the list
 * @param productsList
 */
void printAllProducts(vector<product *> &productsList)
{
    for (unsigned int i = 0; i < productsList.size(); ++i)
    {
        productsList[i]->print(cout);
    }
    cout << endl;
}

/**
 * compare by number
 * @param first
 * @param second
 * @return
 */
bool compareByNumber(product *first, product *second)
{
    return first->getItem() < second->getItem();
}

/**
 * compare by name
 * @param first
 * @param second
 * @return
 */
bool compareByName(product *first, product *second)
{
    if (first->getName() == second->getName())
    {
        return compareByNumber(first, second);
    }
    return first->getName() < second->getName();
}



/**
 * function that sell an item
 * @param productsList
 */
void sellItem(vector<product *> &productsList)
{
    product *mySellProduct = askAndFindItemByNumber(productsList);
    if (mySellProduct == nullptr)
    {
        cout << endl;
        return;
    }
    mySellProduct->printSellMsg();
    string sellQuantityStr;
    double sellQuantity;
    getline(cin, sellQuantityStr);
    if (getDouble(sellQuantityStr, 0, sellQuantity))
    {
        if (mySellProduct->sellItem(sellQuantity))
        {
            mySellProduct->print(cout);
            return;
        }
        else
        {
            cout << endl;
            cerr << MSG_NOT_ENOUGH << endl;
        }
    }
}

/**
 * check the input choice of the user
 * @param line
 * @return
 */
int checkInput(string line)
{
    int count = 0;
    for (unsigned int i = 0; i < line.length() ; ++i)
    {
        if (line[i] == '0')
        {
            count++;
        }
        else
        {
            break;
        }
    }
    line = line.substr(count, line.length());
    if (line.length() == 1 && isdigit(line[0]))
    {
        return line[0] - '0';
    }
    return 0;
}

/**
 * print the menu
 */
void printMenu()
{
    cout << CHOICE1 << endl << CHOICE2 << endl << CHOICE3 << endl;
    cout << CHOICE4 << endl << CHOICE5 << endl << CHOICE6 << endl;
    cout << EXIT_CHOICE << endl;
}

/**
 * the main function
 * @return
 */
int main()
{
    printMenu();
    int choiceNum;
    string choiceNumStr;
    vector<product *> productsList;

    getline(cin, choiceNumStr);
    while (choiceNumStr == "")
    {
        getline(cin, choiceNumStr);
    }
    choiceNum = checkInput(choiceNumStr);

    while (choiceNum < 7 && choiceNum >= 0) // 0 wrong input
    {
        switch (choiceNum)
        {
            case 1:
                parseFile(productsList);
                break;
            case 2:
                cout << MSG_ASK_ID;
                printProduct(askAndFindItemByNumber(productsList));
                break;
            case 3:
                printProduct(findItemByName(productsList));
                break;
            case 4:
                sort(productsList.begin(), productsList.end(), compareByNumber);
                printAllProducts(productsList);
                break;
            case 5:
                sort(productsList.begin(), productsList.end(), compareByName);
                printAllProducts(productsList);
                break;
            case 6:
                cout << MSG_ASK_NUMBER;
                sellItem(productsList);
                break;


        }
        printMenu();
        getline(cin, choiceNumStr);
        while (choiceNumStr == "")
        {
            getline(cin, choiceNumStr);
        }
        choiceNum = checkInput(choiceNumStr);
    }
    for (product *product1 : productsList)
    {
        delete product1;
    }
    productsList.clear();

    return 0;
}