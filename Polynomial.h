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
    void sort();
    void pushBack(int, int);
    Node * searchByPower(int) const;
    Polynomial operator+(const Polynomial&) const;
    Polynomial operator*(const Polynomial&) const;
    void print() const;


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

// Sorts the doubly linked list
void Polynomial::sort()
{
//    Node *ptr = headPtr;
//    for (int i = 0; i < numTerms; ptr = ptr->next)
//    {
//        Node *temp = ptr;
//        Node *largest = temp;
//
//        while (temp != NULL)
//        {
//            if (temp->pow > largest->pow)
//            {
//                largest = temp;
//            }
//            temp = temp->next;
//        }
//        largest->next = ptr->next;
//        headPtr = ptr;
//    }
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
