/*
 * Node.h
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

#ifndef PROJECT_2_NODE_H
#define PROJECT_2_NODE_H

class Node
{
public:
    int coef;
    int pow;
    Node * next;
    Node * prev;

    Node();
    Node(int, int, Node *, Node *);
    ~Node();
};


// Default Constructor
Node::Node()
{
    coef = 0;
    pow = 0;
    next = NULL;
    prev = NULL;
}


// Constructor
Node::Node(int coefficient, int power, Node * nextNode, Node * prevNode)
{
    coef = coefficient;
    pow = power;
    next = nextNode;
    prev = prevNode;
}


// Destructor
Node::~Node()
{
    coef = 0;
    pow = 0;
    next = NULL;
    prev = NULL;
}

#endif //PROJECT_2_NODE_H