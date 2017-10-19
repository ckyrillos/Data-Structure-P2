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
#include <climits>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <exception>
using namespace std;

class Polynomial
{
    //
    friend ostream& operator<<(ostream& os, Polynomial& poly)
    {
        poly.print();
        return os;
    }
public:
    //TODO: Before sumbmission make anything that can be private, private
    Polynomial();
    Polynomial(string);
    Polynomial(const Polynomial&);
    ~Polynomial();
    void insert(int, int);
    Node * searchByPower(int) const;
    void copyList(const Polynomial&);
    Polynomial& operator=(const Polynomial&);
    Polynomial operator+(const Polynomial&) const;
    Polynomial operator*(const Polynomial&) const;
    Polynomial operator^(int) const;
    int solve(int) const;
    void clear();
    void print() const;
    friend ostream& operator<<(ostream&, Polynomial&);
    int safeAdd(int, int) const;
    int safeMultiply(int, int) const;

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
        insert(coef, pow);
    }
}


// Copy Constructor
Polynomial::Polynomial(const Polynomial & other)
{
    if(this != &other)
    {
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


// Inserts node in order
void Polynomial::insert(int coef, int pow)
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


// Copies polynomial
void Polynomial::copyList(const Polynomial &other)
{
    Node *currentNode = other.headPtr;
    headPtr = NULL;

    while (currentNode != NULL)
    {
        try
        {
            insert(currentNode->coef, currentNode->pow);
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
    Polynomial result;
    int highestOrder;
    int coef1;
    int coef2;
    int sum;

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

        sum = safeAdd(coef1, coef2);

        if(sum != 0)
        {
            result.insert(sum, pow);
        }
    }

    return result;
}


// Overloads multiplication operator
Polynomial Polynomial::operator*(const Polynomial &other) const
{
    Polynomial result;
    int pow;
    int coef;
    Node *a = headPtr;

    for(a; a != NULL; a = a->next)
    {
        Node *b = other.headPtr;

        for(b; b != NULL; b = b->next)
        {

            coef = safeMultiply(a->coef, b->coef);

            pow = safeAdd(a->pow, b->pow);
            if(result.searchByPower(pow) == NULL)
            {
                result.insert(coef, pow);
            }
            else
            {
               result.searchByPower(pow)->coef = safeAdd(result.searchByPower(pow)->coef, coef);
            }
        }
    }
    return result;
}


Polynomial Polynomial::operator^(int exponent) const
{
    Polynomial result;

    if (exponent < 0)
    {
        return result;
    }
    if (exponent == 0)
    {
        result.insert(1, 0);
        return result;
    }
    else
    {
        result.insert(1, 0);

        Polynomial base = *this;
        while (exponent > 1)
        {
            if (exponent % 2 == 1)
            {
                result = result * base;
            }
            exponent /= 2;
            base = base * base;
        }

        return result * base;
    }
}


// Prints result of polynomial at given x
int Polynomial::solve(int input) const
{
    Node *current = headPtr;
    int order = current->pow;
    int result = 0;
    for (int i = order; i >= 0; i--)
    {
        if (current && current->pow == i)
        {
            result = safeAdd(safeMultiply(result, input), current->coef);
            current = current->next;
        } else
        {
            result = safeMultiply(result, input);
        }
    }
    return result;
}


// Deletes all nodes and reallocates memory
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


//TODO: Remove couts
int Polynomial::safeAdd(int a, int b) const
{
    if ((a > 0 && b > 0) && (a > INT_MAX - b))
    {
        cout << "failed +MAX" << endl;
        return INT_MAX;
    }
    if ((a < 0 && b < 0) && (a < INT_MIN - b))
    {
        cout << "failed +MIN" << endl;
        return INT_MIN;
    }
    else
    {
        return a + b;
    }
}


int Polynomial::safeMultiply(int a, int b) const
{
    if ((a > 0 && b > 0) && abs(a) > INT_MAX/abs(b))
    {
        cout << "failed *MAX" << endl;
        return INT_MAX;
    }
    if ((a < 0 && b < 0) && abs(a) < INT_MIN/abs(b))
    {
        cout << "failed *MIN" << endl;
        return INT_MIN;
    }
    else
    {
        return a * b;
    }
}


#endif //PROJECT_2_POLYNOMIAL_H
