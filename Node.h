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
    int coeff;
    int pow;
    Node * next;
    Node * prev;

    Node(int, int, Node *, Node *);
};

Node::Node(int coefficient, int power, Node * nextNode, Node * prevNode)
{
    coeff = coefficient;
    pow = power;
    next = nextNode;
    prev = prevNode;
}

#endif //PROJECT_2_NODE_H
