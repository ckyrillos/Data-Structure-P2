/*
 * Polynomial.h
 *
 * COSC 160 Fall 2017
 * Project #2
 *
 * Due on: OCT 16, 2017
 * Author: Carl Kyrillos
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 */

#ifndef PROJECT_2_POLYNOMIAL_H
#define PROJECT_2_POLYNOMIAL_H

#include "Node.h"
#include <iostream>
#include <sstream>
#include <exception>
using namespace std;

class Polynomial
{
public:
    Polynomial();
    Polynomial(string);
    Polynomial(const Polynomial&);
    ~Polynomial();
    void pushBack(int, int);
    Node * searchByPower(int) const;
    void copyList(const Polynomial&);
    Polynomial& operator=(const Polynomial&);
    Polynomial operator+(const Polynomial&) const;
    Polynomial operator*(const Polynomial&) const;
//    Polynomial operator^(int) const;
    void clear();
    void print() const;

    Node *headPtr;
    Node *tailPtr;
    int numTerms;

};


// Default Constructor
Polynomial::Polynomial()
{
    headPtr = NULL;
    tailPtr = NULL;
    numTerms = 0;
}


// Constructor
Polynomial::Polynomial(string nums)
{
    numTerms = 0;
    headPtr = NULL;
    tailPtr = NULL;
    int coef;
    int pow;

    stringstream iss(nums);
    while(iss >> coef >> pow)
    {
        pushBack(coef, pow);
    }
}


// Copy Constructor
Polynomial::Polynomial(const Polynomial & other)
{
    if(this != &other)
    {
        this->clear();

        try
        {
            //Uses copyList to avoid code duplication
           this->copyList(other);
        }
        catch(bad_alloc&)
        {
            string badAlloc =
                    "There is no more available data in the heap";
            throw badAlloc;
        }
    }
}


// Destructor
Polynomial::~Polynomial()
{
    clear();
}


// Adds node to end of polynomial
void Polynomial::pushBack(int coef, int pow)
{
    Node *newNode = new Node(coef, pow, NULL, NULL);
    Node * current = headPtr;
    if (headPtr == NULL)
    {
        headPtr = tailPtr = newNode;
    }
    else if(headPtr->pow < newNode->pow)
    {
        newNode->next = headPtr;
        newNode->next->prev = newNode;
        headPtr = newNode;
    }
    else
    {
        while(current->next != NULL && current->next->pow > newNode->pow)
        {
            current = current->next;
        }

        newNode->next = current->next;
        if (current->next != NULL)
        {
            newNode->next->prev = newNode;
        }
        else
        {
            tailPtr = newNode;
        }
        current->next = newNode;
        newNode->prev = current;
    }
    numTerms++;
}


// Linearly searches for Node associated with inputted power. Returns NULL if term doesn't exist.
Node * Polynomial::searchByPower(int power) const
{
    Node *ptr = headPtr;
    while(ptr != NULL)
    {
        if(ptr->pow == power)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}


void Polynomial::copyList(const Polynomial &other)
{
    Node *currentNode = other.headPtr;
    headPtr = NULL;

    while (currentNode != NULL)
    {
        try
        {
            pushBack(currentNode->coef, currentNode->pow);
        }
        catch (bad_alloc&)
        {
            string badAlloc =
                    "There is no more available data in the heap.";
            throw badAlloc;
        }
        currentNode = currentNode->next;
    }

    numTerms = other.numTerms;
}


// Overloads assignment operator
Polynomial& Polynomial::operator=(const Polynomial &other)
{
    if(this != &other)
    {
        this->clear();

        try
        {
            //Uses copyList to avoid code duplication
            this->copyList(other);
        }
        catch(bad_alloc&)
        {
            string badAlloc =
                    "There is no more available data in the heap";
            throw badAlloc;
        }
    }
    return *this;
}


// Overloads addition operator
Polynomial Polynomial::operator+(const Polynomial &other) const
{
    Polynomial poly3;
    int highestOrder;
    int coef1;
    int coef2;

    if(headPtr->pow > other.headPtr->pow)
    {
        highestOrder = headPtr->pow;
    }
    else
    {
        highestOrder = other.headPtr->pow;
    }

    for (int pow = highestOrder; pow >= 0; pow--)
    {
        if (searchByPower(pow) != NULL)
        {
            coef1 = searchByPower(pow)->coef;
        }
        else
        {
            coef1 = 0;
        }

        if (other.searchByPower(pow) != NULL)
        {
            coef2 = other.searchByPower(pow)->coef;
        }
        else
        {
            coef2 = 0;
        }

        int sum = coef1+coef2;

        if(sum != 0)
        {
            poly3.pushBack(sum, pow);
        }
    }

    return poly3;
}


// Overloads multiplication operator
Polynomial Polynomial::operator*(const Polynomial &other) const
{
    Polynomial poly3;
    int pow;
    int coef;
    Node *a = headPtr;

    for(a; a != NULL; a = a->next)
    {
        Node *b = other.headPtr;

        for(b; b != NULL; b = b->next)
        {
            coef = a->coef * b->coef;
            pow = a->pow + b->pow;
            if(poly3.searchByPower(pow) == NULL)
            {
                poly3.pushBack(coef, pow);
            }
            else
            {
               poly3.searchByPower(pow)->coef += coef;
            }
        }
    }
    return poly3;
}


//Polynomial Polynomial::operator^(int power) const
//{
//
//}


void Polynomial::clear()
{
    Node *current = headPtr;
    headPtr = NULL;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
        numTerms--;
    }
    tailPtr = NULL;
}


// Prints terms of polynomial
void Polynomial::print() const
{
    Node *ptr = headPtr;
    while(ptr != NULL)
    {
        if(ptr->pow != 0)
        {
            if(ptr->coef == 1)
            {
                cout << "x^" << ptr->pow;
            }
            else
            {
                cout << ptr->coef << "x^" << ptr->pow;
            }
        }
        else
        {
            cout << ptr->coef;
        }
        if(ptr != tailPtr)
        {
            cout << " + ";
        }
        ptr = ptr->next;
    }
    cout << endl;
}


#endif //PROJECT_2_POLYNOMIAL_H
