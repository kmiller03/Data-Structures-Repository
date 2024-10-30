#ifndef CALCLIST_HPP
#define CALCLIST_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <exception>

// Test Function
void CalcListTestFunction();

// Function for converting a double to a string, cutting off at the decimal place indicated by precision. Returns string.
std::string doubleToString(double value = 0, int precision = 0);

// Enumerator type for linked list function input
enum FUNCTION
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};

// Node class for the calculator with inbuilt constructor
class Node
{
public:
    FUNCTION operation;
    double operand;
    double previousValue;
    double outputValue;
    Node *previous = nullptr;
    Node *next = nullptr;

    Node(FUNCTION operation = ADDITION, double operand = 0, double previousValue = 0, double outputValue = 0, Node *previous = nullptr, Node *next = nullptr)
    {
        this->operation = operation;
        this->operand = operand;
        this->previousValue = previousValue;
        this->outputValue = outputValue;
        this->previous = previous;
        this->next = next;
    }
};

// Class for the calculator linked list and its necessary functions
class CalcList
{
public:
    Node *head;

    double totalValue = 0;
    int totalSteps = 0;

    void newOperation(const FUNCTION func, const double operand); // Applies operand to totalValue according to the operation provided by func and creates a new node within the linked list
    void removeLastOperation();                                   // Removes the last operation performed, returning the previous totalValue
    std::string toString(unsigned short precision);               // Converts linked list contents to precise string
    double total();                                               // Returns current total
};

#endif
