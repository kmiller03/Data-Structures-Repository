//Name: Kadin Miller
//UID: U95099011
//Description: Implements a linked list class with novel functions to take a series of inputs calculating values. 
#include <iostream>
#include "CalcList.hpp"

#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <exception>
using namespace std;

// Test Function
void CalcListTestFunction()
{
    std::cout << "Linked List Test Function Called!\n";
}

// Function for converting a double to a string, cutting off at the decimal place indicated by precision. Returns string.
string doubleToString(double value, int precision)
{
    stringstream stream;
    stream << std::fixed << std::setprecision(precision) << value; // need to include std::fixed before std::setprecision() to make it deal with trialing zeroes properly
    string output;
    stream >> output;
    return output;
}

// Applies operand to totalValue according to the operation provided by func and creates a new node within the linked list
void CalcList::newOperation(const FUNCTION func, const double operand)
{
    // function call debug
    //std::cout << "debug: newOperation called\n";

    // Performs operation on totalValue, keeping track of the value before operation
    double oldValue = totalValue;
    switch (func)
    {
    case ADDITION:
        totalValue += operand;
        break;
    case SUBTRACTION:
        totalValue -= operand;
        break;
    case MULTIPLICATION:
        totalValue *= operand;
        break;
    case DIVISION:
        // Divide by zero handling
        if (operand == 0)
        {
            throw runtime_error("Error: Divide by Zero");
            return;
        }
        totalValue /= operand;
        break;
    default:
        std::cout << "Error: newOperation function arg is not one of 4 allowed cases\n";
    }

    // Adds the new node to the linked list and increases totalSteps by 1
    head = new Node(func, operand, oldValue, totalValue, nullptr, this->head);
    totalSteps++;

    /*//Miscellaneous
    while (newNode -> next != nullptr) {
        newNode -> previous = newNode;
        newNode -> step = newNode -> step + 1;
        newNode = newNode -> next;
    }
    newNode -> step = head -> step + 1;
    std::cout << newNode -> step;
    head -> next = newNode;
    newNode -> previous = head;
    */
};

// Removes the last operation performed, returning the previous totalValue
void CalcList::removeLastOperation()
{
    // Function call debug
    //std::cout << "debug: removeLastOperation called\n";

    // Error handling for attempting to pop an empty list
    //prints the address of head->next to try and debug the segfault
    //std::cout << head->next << "<- head next\n";
    if (head->next == nullptr)
    {
        throw runtime_error("List is empty");
        return;
    }

    Node *temp = head;
    head = head->next;
    head->previous = nullptr;

    totalValue = head->outputValue;
    totalSteps--;
    if (totalSteps == 0)
    {
        totalValue = 0;
    }
    temp = nullptr;
};

// Prints the operations of the linked list in order with precision determined by the precision argument
string CalcList::toString(unsigned short precision)
{
    // function call debug
    //std::cout << "debug: toString called\n";

    string outputMessage;
    Node *toStringIterator = head;
    string operationCharacter;
    string previousValueString;
    string operandString;
    string resultString;

    // Iterates over the linked list and formats the relevant values stored within to precise strings
    for (int i = totalSteps; i > 0; i--)
    {
        switch (toStringIterator->operation)
        {
        case 0:
            operationCharacter = "+";
            break;
        case 1:
            operationCharacter = "-";
            break;
        case 2:
            operationCharacter = "*";
            break;
        case 3:
            operationCharacter = "/";
            break;
        }
        previousValueString = doubleToString(toStringIterator->previousValue, precision);
        operandString = doubleToString(toStringIterator->operand, precision);
        resultString = doubleToString(toStringIterator->outputValue, precision);

        // concatenates the above strings into the proper format
        outputMessage += std::to_string(i) + ": " + previousValueString + operationCharacter + operandString + "=" + resultString + "\n";
        // Console message equivalent to outputMessage for debugging
        // std::cout << i << ": " << previousValueString << operationCharacter << operandString << "=" << resultString << "\n";

        toStringIterator = toStringIterator->next;
    }

    return outputMessage;
};

// returns the current total value of the linked list
double CalcList::total()
{
    // function call debug
    // std::cout << "debug: total called, total is: " << totalValue << "\n";
    return totalValue;
};


int main()
{
    CalcListTestFunction();
    CalcList calc;

    calc.newOperation(SUBTRACTION, 10);
    std::cout << calc.total() << "\n";
    calc.removeLastOperation();
    std::cout << calc.total() << "\n";
    calc.newOperation(SUBTRACTION, 10);
    std::cout << calc.total() << "\n";
    calc.removeLastOperation();
    std::cout << calc.total() << "\n";
    return 0;
}


// g++ calculatorMain.cpp (header scripts).cpp -o (desired compile name)
// to compile
//  ./(compile name) to run
// shift + alt + f to format code