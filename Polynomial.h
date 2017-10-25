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
#include <stdexcept>
using namespace std;

class Polynomial
{
    // Overloads String Insertion Operator
    friend ostream& operator<<(ostream& os, Polynomial& poly)
    {
        poly.print();
        return os;
    }

public:
    // Operators and Destructor
    Polynomial();
    Polynomial(string) throw(bad_alloc);
    Polynomial(const Polynomial&) throw (bad_alloc);
    ~Polynomial();

    // Public Operations
    void copyList(const Polynomial&) throw(bad_alloc);
    Polynomial& operator=(const Polynomial&) throw(bad_alloc);
    Polynomial operator+(const Polynomial&) const throw(bad_alloc, overflow_error);
    Polynomial operator*(const Polynomial&) const throw(bad_alloc, overflow_error);
    Polynomial operator^(int) const throw(invalid_argument, overflow_error);
    int solve(int) const throw(overflow_error);

private:
    Node *headPtr;
    Node *tailPtr;
    int numTerms;

    // Private Operations
    void insert(int, int) throw(bad_alloc);
    Node * searchByPower(int) const;
    void clear();
    void print() const;

    // Safe Elementary Arithmetic Operators
    int safeAdd(int, int) const throw(overflow_error);
    int safeMultiply(int, int) const throw(overflow_error);
};


// Default Constructor
Polynomial::Polynomial()
{
    headPtr = NULL;
    tailPtr = NULL;
    numTerms = 0;
}


// Constructor
Polynomial::Polynomial(string nums) throw(bad_alloc)
{
    try
    {
        numTerms = 0;
        headPtr = NULL;
        tailPtr = NULL;
        int coef;
        int pow;

        // Creates stringstream from numbers in file and reads them into nodes
        stringstream iss(nums);
        while(iss >> coef >> pow)
        {
            insert(coef, pow);
        }
    }
    catch (bad_alloc error)
    {
        cout << error.what() << endl;
    }
}


// Copy Constructor
Polynomial::Polynomial(const Polynomial & other) throw(bad_alloc)
{
    try
    {
        if(this != &other)
        {
            this->copyList(other);
        }
    }
    catch (bad_alloc error)
    {
        cout << error.what() << endl;
    }
}


// Destructor
Polynomial::~Polynomial()
{
    clear();
}


// Inserts node in order
void Polynomial::insert(int coef, int pow) throw(bad_alloc)
{
    try
    {
        Node *newNode = new Node(coef, pow, NULL, NULL);
        Node * current = headPtr;

        // If list is empty, the newNode is set to both head and tail
        if (headPtr == NULL)
        {
            headPtr = tailPtr = newNode;
        }

        // If the list isn't empty, but the newNode belongs in front it points to the head and becomes new head
        else if(headPtr->pow < newNode->pow)
        {
            newNode->next = headPtr;
            newNode->next->prev = newNode;
            headPtr = newNode;
        }

        // Else the newNode is added to middle of list, if added at end, it becomes the tail
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

        // Increments the number of terms in the polynomial
        numTerms++;
    }
    catch (bad_alloc error)
    {
        cout << error.what() << endl;
    }
}


// Linearly searches for Node associated with inputted power, returns NULL if term doesn't exist.
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


// Makes a copy of the polynomial
void Polynomial::copyList(const Polynomial &other) throw(bad_alloc)
{
    try
    {
        Node *currentNode = other.headPtr;
        headPtr = NULL;

        while (currentNode != NULL)
        {
            insert(currentNode->coef, currentNode->pow);
            currentNode = currentNode->next;
        }

        numTerms = other.numTerms;
    }
    catch (bad_alloc error)
    {
        cout << error.what() << endl;
    }
}


// Overloads Assignment Operator
Polynomial& Polynomial::operator=(const Polynomial &other) throw(bad_alloc)
{
    try
    {
        if(this != &other)
        {
            this->clear();
            this->copyList(other);
        }
        return *this;
    }
    catch (bad_alloc error)
    {
        cout << error.what() << endl;
    }
}


// Overloads Addition Operator
Polynomial Polynomial::operator+(const Polynomial &other) const throw(bad_alloc, overflow_error)
{
    try
    {
        Polynomial result;
        int highestOrder;
        int coef1;
        int coef2;
        int sum;

        // Checks to see which term is greater
        if(headPtr->pow > other.headPtr->pow)
        {
            highestOrder = headPtr->pow;
        }
        else
        {
            highestOrder = other.headPtr->pow;
        }

        // Iterates down from highest order until power is 0
        for (int pow = highestOrder; pow >= 0; pow--)
        {
            // If term for this power exists get its coefficient if not set it to 0
            if (searchByPower(pow) != NULL)
            {
                coef1 = searchByPower(pow)->coef;
            }
            else
            {
                coef1 = 0;
            }

            // If term for this power exists get its coefficient if not set it to 0
            if (other.searchByPower(pow) != NULL)
            {
                coef2 = other.searchByPower(pow)->coef;
            }
            else
            {
                coef2 = 0;
            }

            // Adds the two sums
            sum = safeAdd(coef1, coef2);

            // If the sum isn't zero, no term at this power exists so one is created
            if(sum != 0)
            {
                result.insert(sum, pow);
            }
        }
        return result;
    }
    catch (bad_alloc error)
    {
        cout << error.what() << endl;
    }
    catch (overflow_error error)
    {
        cout << error.what() << endl;
        Polynomial badPoly;
        return badPoly;
    }
}


// Overloads Multiplication Operator
Polynomial Polynomial::operator*(const Polynomial &other) const throw(bad_alloc, overflow_error)
{
    try
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

                // If no term of the current power exists, one is created
                if(result.searchByPower(pow) == NULL)
                {
                    result.insert(coef, pow);
                }

                // Else adds the sum to existing coefficient
                else
                {
                   result.searchByPower(pow)->coef = safeAdd(result.searchByPower(pow)->coef, coef);
                }
            }
        }
        return result;
    }
    catch (bad_alloc error)
    {
        cout << error.what() << endl;
    }
    catch (overflow_error error)
    {
        cout << error.what() << endl;
        Polynomial badPoly;
        return badPoly;
    }
}


// Overloads Exponent Operator
Polynomial Polynomial::operator^(int exponent) const throw (invalid_argument, overflow_error)
{
    try
    {
        Polynomial result;

        // Tests to see if exponent is negative, throws exception if true per project parameters
        if (exponent < 0)
        {
            throw invalid_argument("Exponent can't be negative");
        }

        // If exponent is zero, simply inserts a term with a coefficient of 1
        if (exponent == 0)
        {
            result.insert(1, 0);
            return result;
        }

        // Else evaluate the using Fast Exponentaion
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
    catch (invalid_argument error)
    {
        cout << error.what() << endl;
        Polynomial badPoly;
        return badPoly;
    }
    catch (overflow_error error)
    {
        cout << error.what() << endl;
        Polynomial badPoly;
        return badPoly;
    }
}


// Prints result of polynomial at given x
int Polynomial::solve(int input) const throw (overflow_error)
{
    try
    {
        Node *current = headPtr;
        int order = current->pow;
        int result = 0;

        // Solves the polynomial using Horner's Method
        for (int i = order; i >= 0; i--)
        {
            if (current && current->pow == i)
            {
                result = safeAdd(safeMultiply(result, input), current->coef);
                current = current->next;
            }
            else
            {
                result = safeMultiply(result, input);
            }
        }
        return result;
    }
    catch (overflow_error error)
    {
        cout << error.what() << endl;
        // Returns sentinel which in this case is INT_MAX
        return INT_MAX;
    }
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
        // If the power isn't 0, append a '^' to each term
        if(ptr->pow != 0)
        {
            // If the coef is 1, the coefficient is omitted
            if(ptr->coef == 1)
            {
                if(ptr->pow == 1)
                {
                    cout << "x";
                }
                else
                {
                    cout << "x^" << ptr->pow;
                }
            }
            else
            {
                if(ptr->pow == 1)
                {
                    cout << ptr->coef << "x";
                }
                else
                {
                    cout << ptr->coef << "x^" << ptr->pow;
                }
            }
        }
        else
        {
            cout << ptr->coef;
        }

        // If not the last term, a '+' is appended to the output.
        if(ptr != tailPtr)
        {
            cout << " + ";
        }
        ptr = ptr->next;
    }
    cout << endl;
}


// Function to add two ints so long as their sum won't cause an integer overflow/underflow
int Polynomial::safeAdd(int a, int b) const throw (overflow_error)
{
    // Checks to make sure the resulting sum won't cause an integer overflow
    if ((a > 0 && b > 0) && (a > INT_MAX - b))
    {
        throw overflow_error("Overflow Detected");
    }

    // Checks to make sure the resulting sum won't cause an integer underflow
    if ((a < 0 && b < 0) && (a < INT_MIN - b))
    {
        throw overflow_error("Overflow Detected");
    }

    // Since the ints can be safely added, the sum is returned
    else
    {
        return a + b;
    }
}


// Function to multiply two ints so long as their sum won't cause an integer overflow/underflow
int Polynomial::safeMultiply(int a, int b) const throw (overflow_error)
{
    // Checks to make sure the resulting product won't cause an integer overflow
    if ((a > 0 && b > 0) && abs(a) > INT_MAX/abs(b))
    {
        throw overflow_error("Overflow Detected\n");
    }

    // Checks to make sure the resulting product won't cause an integer underflow
    if ((a < 0 && b < 0) && abs(a) < INT_MIN/abs(b))
    {
        throw overflow_error("Overflow Detected\n");
    }

    // Since the ints can be safely multiplied, the sum is returned
    else
    {
        return a * b;
    }
}

#endif //PROJECT_2_POLYNOMIAL_H