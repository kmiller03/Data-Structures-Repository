// Description: Implement class NotationConverter which includes a student made deque. Has 6 functions that take a string and
//               convert it from prefix, infix, or postfix notation to any other notation.
#ifndef NOTATIONCONVERTER_HPP
#define NOTATIONCONVERTER_HPP

#include <string>
#include "NotationConverterInterface.hpp"

// dequeNode class with inbuilt constructor
class dequeNode
{
public:
    // dequeNode constructor
    dequeNode(std::string element = "", dequeNode *previous = nullptr, dequeNode *next = nullptr)
    {
        this->element = element;
        this->previous = previous;
        this->next = next;
    }

private:
    std::string element = "";
    dequeNode *previous = nullptr;
    dequeNode *next = nullptr;

    friend class NotationConverter;
};

// Notation converter class which includes student implemented deque
class NotationConverter : public NotationConverterInterface
{
public:
    int dequeLength = 0; // Length count

    void pushBack(const dequeNode &newNode);  // Add node to back
    void pushFront(const dequeNode &newNode); // Add node to front

    void popFront(); // Remove first node
    void popBack();  // Remove last node

    const std::string front(); // Return the front node
    const std::string back();  // Return the back node

    bool empty(); // Returns true of deque is empty

    std::string postfixToInfix(std::string inStr);  // Takes postfix and converts to infix, then returns string
    std::string postfixToPrefix(std::string inStr); // Takes postfix and converts to prefix, then returns string

    std::string infixToPostfix(std::string inStr); // Takes infix and converts to postfix, then returns string
    std::string infixToPrefix(std::string inStr);  // Takes infix and converts to prefix, then returns string

    std::string prefixToInfix(std::string inStr);   // Takes prefix and converts to infix, then returns string
    std::string prefixToPostfix(std::string inStr); // Takes prefix and converts to postfix, then returns string

private:
    dequeNode *head = nullptr; // First node
    dequeNode *tail = nullptr; // Last node
};

#endif