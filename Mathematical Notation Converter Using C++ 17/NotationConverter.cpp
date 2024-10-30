// Made by K Miller and Trace Comiskey
// Name: K Miller
// UID: U95099011
// Description: Implement class NotationConverter which includes a student made deque. Has 6 functions that take a string and
//               convert it from prefix, infix, or postfix notation to any other notation.

#include <iostream>
#include <string>
#include <cctype>
#include "NotationConverter.hpp"
#include "NotationConverterInterface.hpp"

using namespace std;

// Add node to front of deque
void NotationConverter::pushFront(const dequeNode &newNode)
{
    dequeNode *newNodePointer = new dequeNode(newNode.element);

    // If the deque is empty, make the new node the head and tail. Else,
    // Adds the new node to the top of the deque and increases dequeLength by 1
    if (empty())
    {
        head = newNodePointer;
        tail = newNodePointer;
    }
    else
    {
        newNodePointer->next = head;
        head->previous = newNodePointer;
        head = newNodePointer;
    }
    dequeLength++;
};

// Add node to back of deque
void NotationConverter::pushBack(const dequeNode &newNode)
{
    dequeNode *newNodePointer = new dequeNode(newNode.element);

    // If the deque is empty, make the new node the head and tail. Else,
    // Adds the new node to the top of the deque and increases dequeLength by 1
    if (empty())
    {
        head = newNodePointer;
        tail = newNodePointer;
    }
    else
    {
        newNodePointer->previous = tail;
        tail->next = newNodePointer;
        tail = newNodePointer;
    }
    dequeLength++;
};

// Remove first node of deque
void NotationConverter::popFront()
{
    if (empty())
    {
        throw std::invalid_argument("Error");
    }

    // Allocates head to a temporary pointer node. Sets 1 node long deques to null, or removes the head and points it at its next if not. Then deletes the old head.
    dequeNode *temp = head;
    if (head == tail)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = head->next;
        head->previous = nullptr;
    }
    delete temp;
    dequeLength--;
};

// Remove last node of deque
void NotationConverter::popBack()
{
    if (empty())
    {
        throw std::invalid_argument("Error");
    }

    // Allocates head to a temporary pointer node. Sets 1 node long deques to null, or removes the tail and points it at its previous if not. Then deletes the old tail.
    dequeNode *temp = tail;
    if (head == tail)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        tail = tail->previous;
        tail->next = nullptr;
    }
    delete temp;
    dequeLength--;
};

// Return the front node value
const std::string NotationConverter::front()
{
    if (empty())
    {
        throw std::invalid_argument("Error");
    }
    return head->element;
};

// Return the back node value
const std::string NotationConverter::back()
{
    if (empty())
    {
        std::invalid_argument("Error");
    }
    return tail->element;
};

// Returns true if deque is empty
bool NotationConverter::empty()
{
    return dequeLength == 0;
};

// Takes postfix and converts to infix, then returns string
std::string NotationConverter::postfixToInfix(std::string inStr)
{
    std::string op1 = "";
    std::string op2 = "";
    std::string opr = "";

    // Iterates over inStr from left to right character
    for (unsigned int i = 0; i < inStr.size(); i++)
    {
        if (isspace(inStr[i]))
        {
            continue;
        }
        else if (isalpha(inStr[i]))
        {
            if (op1 != "")
            {
                dequeNode temp = dequeNode(op1);
                pushFront(temp);
            }
            op1 = op2;
            op2 = inStr[i];
            continue;
        }
        else if ((inStr[i] == '+') || (inStr[i] == '-') || (inStr[i] == '*') || (inStr[i] == '/'))
        {
            opr = inStr[i];
            op2 = "(" + op1 + " " + opr + " " + op2 + ")";

            if (!empty())
            {
                op1 = front();
                popFront();
            }
            else
                op1 = "";
            continue;
        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }
    return op2;
};

// Takes prefix and converts to infix, then returns string
std::string NotationConverter::prefixToInfix(std::string inStr)
{
    std::string op1 = "";
    std::string op2 = "";
    std::string opr = "";

    // Iterates over inStr from left to right character
    for (unsigned int i = 0; i < inStr.size(); i++)
    {
        if (isspace(inStr[i]))
        {
            continue;
        }
        else if (isalpha(inStr[i]))
        {
            if (op1 != "")
            {
                op2 = inStr[i];

                if (opr == "")
                {
                    opr = front();
                    popFront();
                }
                op1 = "(" + op1 + " " + opr + " " + op2 + ")";
                op2 = "";
                opr = "";
                continue;
            }
            op1 = inStr[i];
            continue;
        }
        else if ((inStr[i] == '+') || (inStr[i] == '-') || (inStr[i] == '*') || (inStr[i] == '/'))
        {
            if (opr != "")
            {
                dequeNode temp = dequeNode(opr);
                pushFront(temp);
            }
            opr = inStr[i];
            if (op1 != "")
            {
                dequeNode temp2 = dequeNode(op1);
                pushBack(temp2);
                op1 = "";
            }
            continue;
        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }

    while (!empty())
    {
        op2 = op1;
        opr = front();
        popFront();
        op1 = back();
        popBack();
        op1 = "(" + op1 + " " + opr + " " + op2 + ")";
    }
    return op1;
};

// Takes infix and converts to postfix, then returns string
std::string NotationConverter::infixToPostfix(std::string inStr)
{
    std::string frontChar = "";
    std::string expression = "";
    std::string outExpression = "";

    // Iterates over inStr from left to right character
    for (unsigned int i = 0; i < inStr.size(); i++)
    {
        frontChar = inStr[i];

        if (isalpha(inStr[i]))
        {
            expression += inStr[i];
            // std::cout << "Found operand, current expression: " << expression << '\n';
            continue;
        }
        else if (inStr[i] == '(')
        {
            pushFront(frontChar);
            // std::cout << "Found (, pushing to stack: " << '\n';
            continue;
        }
        else if (inStr[i] == ')')
        {
            // std::cout << "Found ), clearing stack and adding until (: " << '\n';
            while (front() != "(")
            {
                expression += front();
                popFront();
                // std::cout << "Current expression: " << expression << '\n';
            }
            // std::cout << "Finished adding to stack, deleting (: " << '\n';
            popFront();
        }
        else if (isspace(inStr[i]))
        {
            // std::cout << "Found space, skipping: " << '\n';
            continue;
        }
        else if ((inStr[i] == '+') || (inStr[i] == '-') || (inStr[i] == '*') || (inStr[i] == '/'))
        {
            // std::cout << "Found operator " << frontChar << ", checking if empty: " << '\n';
            if (empty())
            {
                pushFront(frontChar);
                continue;
            }

            // std::cout << "Stack is not empty, checking front character: " << '\n';
            while (!empty() && ((front() == "+") || (front() == "-") || (front() == "*") || (front() == "/")))
            {

                // std::cout << "Stack isn't empty and operator " << front() << " is in front" << '\n';
                // std::cout << "Checking if found operator has higher precedence: " << '\n';

                if (((inStr[i] == '/') || (inStr[i] == '*')) && ((front() == "+") || (front() == "-")))
                {
                    // std::cout << "Operator has precedence, pushing and leaving : " << '\n';
                    pushFront(frontChar);
                    break;
                }
                else
                {
                    // std::cout << "Operator does not have precedence, popping until it does or empty:" << '\n';
                    expression += front();
                    popFront();
                }
            }
            pushFront(frontChar);
        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }

    // std::cout << "Reached end of string, outputting stack until empty: " << '\n';
    while (!empty())
    {
        expression += front();
        popFront();
    }

    // std::cout << "Adding Whitespace: " << '\n';
    for (unsigned int i = 0; i < expression.size(); i++)
    {
        outExpression += expression[i];
        if (i != (expression.size() - 1))
            outExpression += ' ';
    }
    return outExpression;
};

// Takes postfix and converts to prefix, then returns string
std::string NotationConverter::postfixToPrefix(std::string inStr)
{
    std::string outputString;

    // Iterates over inStr, adding it to a deque in prefix format
    int stringLength = inStr.length();
    for (int i = 0; i < stringLength; i++)
    {
        char stringCharacter = inStr[i]; // Reads inStr from left to right and creates a string from that character
        std::string stringCharacterToString = "";
        stringCharacterToString += stringCharacter;

        // If the next character is an operator, then pop two nodes, then create a string with the operator, the two popped nodes, and push them as one node to the deque
        if (stringCharacter == '*' || stringCharacter == '/' || stringCharacter == '+' || stringCharacter == '-')
        {
            std::string string1 = back();
            popBack();
            std::string string2 = back();
            popBack();

            std::string tempString = stringCharacterToString + " " + string2 + " " + string1;
            pushBack(tempString);
        }
        // If the next character is an operand, add it to the deque.
        else if (isalpha(stringCharacter))
        {
            pushBack(dequeNode(stringCharacterToString));
        }
        else if (isspace(stringCharacter))
        {
            continue;
        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }

    // Converts the deque to a string, adds spaces between elements, and removes last space
    while (!empty())
    {
        outputString += front() + " "; // Adds the node
        popFront();
    }
    outputString.pop_back();
    return outputString;
};

// Takes infix and converts to prefix via other functions, then returns string
std::string NotationConverter::infixToPrefix(std::string inStr)
{
    std::string temp = infixToPostfix(inStr);
    temp = postfixToPrefix(temp);
    return temp;
};

// Takes infix and converts to postfix via other functions, then returns string
std::string NotationConverter::prefixToPostfix(std::string inStr)
{
    std::string temp = prefixToInfix(inStr);
    temp = infixToPostfix(temp);
    return temp;
};
