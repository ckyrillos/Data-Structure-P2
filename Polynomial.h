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
using namespace std;

class Polynomial
{
public:
    Polynomial();
    Polynomial(string);
    ~Polynomial();
    void pushBack(int, int);
    int searchByPower(int) const;
    Polynomial operator+(const Polynomial&) const;
    void print();


private:
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

// Destructor
Polynomial::~Polynomial()
{
    Node *current = headPtr;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

// Linearly searches for coef associated with inputted power. Returns 0 if term doesn't exist.
int Polynomial::searchByPower(int power) const
{
    Node *ptr = headPtr;
    while(ptr != NULL)
    {
        if(ptr->pow == power)
        {
            return ptr->coef;
        }
        ptr = ptr->next;
    }
    return 0;
}

void Polynomial::pushBack(int coef, int pow)
{
    Node *n = new Node(coef, pow, NULL, NULL);
    if (headPtr == NULL)
    {
        headPtr = n;
    }
    if (tailPtr != NULL)
    {
        tailPtr->next = n;
    }

    n->next = NULL;
    n->prev = tailPtr;
    tailPtr = n;
    numTerms++;
}

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
        coef1 = searchByPower(pow);
        coef2 = other.searchByPower(pow);
        int sum = coef1+coef2;

        if(sum != 0)
        {
            poly3.pushBack(sum, pow);
        }
    }

    return poly3;
}

void Polynomial::print()
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
