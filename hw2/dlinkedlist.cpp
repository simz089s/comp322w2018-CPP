#include <iostream>
#include <cstdlib>

#include "dlinkedlist.h"

/**
 * Header file structure:

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

class Node
{
public:
    Node();
    ~Node();
    Node(int data, Node* next, Node* previous);
    int getData();
    Node* getNext();
    Node* getPrev();
    void setData(int data);
    void setNext(Node* next);
    void setPrev(Node* previous);

private:
    int data;
    Node* next;
    Node* previous;
};

class DLLStructure
{
public:
    DLLStructure();
    ~DLLStructure();
    DLLStructure(int array[], int length);
    Node* getHd();
    Node* getTl();
    void setHd(Node* head);
    void setTl(Node* tail);
    void PrintDLL();
    void InsertAfter(int valueToInsertAfter, int valueToBeInserted);

private:
    Node* head;
    Node* tail;
};

#endif // DLINKEDLIST_H

*/

/**
 * Node
 */

Node::Node() : data(0), next((Node*)NULL), previous((Node*)NULL)
{
    // this->data = 0;
    // this->next = (Node*)NULL;
    // this->previous = (Node*)NULL;
}

// Node::~Node() {} Nothing to delete

Node::Node(int data, Node* next, Node* previous) : data(data), next(next), previous(previous)
{
    // this->data = data;
    // this->next = next;
    // this->previous = previous;
}

int Node::getData() const { return this->data; }
Node* Node::getNext() const { return this->next; }
Node* Node::getPrev() const { return this->previous; }

void Node::setData(int data) { this->data = data; }
void Node::setNext(Node* next){ this->next = next; }
void Node::setPrev(Node* previous) { this->previous = previous; }

/**
 * DLLStructure
 */

Node* DLLStructure::getHd() const { return this->head; }
Node* DLLStructure::getTl() const { return this->tail; }
void DLLStructure::setHd(Node* head) { this->head = head; }
void DLLStructure::setTl(Node* tail) { this->tail = tail; }

DLLStructure::DLLStructure() : head((Node*)NULL), tail((Node*)NULL)
{
    // this->head = (Node*)NULL;
    // this->tail = (Node*)NULL;
}

DLLStructure::~DLLStructure()
{
    Node* head = this->head;
    for (Node* current = head->getNext(); current != (Node*)NULL; current = current->getNext())
    {
        delete current->getPrev();
        if (current->getNext() == (Node*)NULL)
        {
            delete current;
            current = (Node*)NULL;
            break;
        }
    }
}

DLLStructure::DLLStructure(int array[], int length) : head((Node*)NULL), tail((Node*)NULL)
{
    // this->head = (Node*)NULL;
    // this->tail = (Node*)NULL;
    if (length < 1) { return; }

    this->head = new Node();
    this->head->setData(array[0]);
    Node* prev = this->head;
    for (int i = 1; i < length; i++)
    {
        Node* curr = new Node(array[i], (Node*)NULL, prev);
        prev->setNext(curr);
        prev = curr;
    }
    this->tail = prev;
}

void DLLStructure::PrintDLL() const
{
    Node* current;
    for (current = this->head; current->getNext() != (Node*)NULL; current = current->getNext())
        { std::cout << current->getData() << ", "; }
    std::cout << current->getData() << std::endl;
}

void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted)
{
    for (Node* current = this->head; current != (Node*)NULL; current = current->getNext())
    {
        if (current->getData() == valueToInsertAfter)
        {
            Node* insert = new Node(valueToBeInserted, current->getNext(), current);
            if (current->getNext() != (Node*)NULL) { current->getNext()->setPrev(insert); }
            current->setNext(insert);
            return;
        }
    }
}

int main(void)
{
    int array[] = {13,42,69,360,420};
    DLLStructure dll(array, sizeof(array)/sizeof(int));
    dll.PrintDLL();
    dll.InsertAfter(13,7);
    dll.PrintDLL();
    dll.InsertAfter(420,7);
    dll.PrintDLL();
    dll.InsertAfter(7,9);
    dll.PrintDLL();
    return EXIT_SUCCESS;
}
