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

Node* DLLStructure::getFst() const { return this->first; }
Node* DLLStructure::getLst() const { return this->last; }
void DLLStructure::setFst(Node* first) { this->first = first; }
void DLLStructure::setLst(Node* last) { this->last = last; }

DLLStructure::DLLStructure() : first((Node*)NULL), last((Node*)NULL)
{
    // this->first = (Node*)NULL;
    // this->last = (Node*)NULL;
}

DLLStructure::~DLLStructure()
{
    Node* first = this->first;
    for (Node* current = first->getNext(); current != (Node*)NULL; current = current->getNext())
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

DLLStructure::DLLStructure(int array[], int size) : first((Node*)NULL), last((Node*)NULL)
{
    // this->first = (Node*)NULL;
    // this->last = (Node*)NULL;
    if (size < 1) { return; }

    this->first = new Node();
    this->first->setData(array[0]);
    Node* prev = this->first;
    for (int i = 1; i < size; i++)
    {
        Node* curr = new Node(array[i], (Node*)NULL, prev);
        prev->setNext(curr);
        prev = curr;
    }
    this->last = prev;
}

void DLLStructure::PrintDLL() const
{
    Node* current;
    for (current = this->first; current->getNext() != (Node*)NULL; current = current->getNext())
        { std::cout << current->getData() << ", "; }
    std::cout << current->getData() << std::endl;
}

void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted)
{
    for (Node* current = this->first; current != (Node*)NULL; current = current->getNext())
    {
        if (current->getData() == valueToInsertAfter)
        {
            Node* insert = new Node(valueToBeInserted, current->getNext(), current);
            if (current->getNext() != (Node*)NULL) { current->getNext()->setPrev(insert); }
            current->setNext(insert);
            if (current == this->last) { this->last = insert; }
            return;
        }
    }
}

void DLLStructure::InsertBefore(int valueToInsertBefore, int valueToBeInserted)
{
    for (Node* current = this->first; current != (Node*)NULL; current = current->getNext())
    {
        if (current->getData() == valueToInsertBefore)
        {
            if (current == this->first)
            {
                // ???
            }
            else
            {
                // [1,2,2,4] InsertBefore(4, 99) ???
                this->InsertAfter(current->getPrev()->getData(), valueToBeInserted);
            }
            return;
        }
    }
}

void DLLStructure::Delete(int value)
{
    for (Node* current = this->first; current != (Node*)NULL; current = current->getNext())
    {
        if (current->getData() == value)
        {
            if (current == this->first && this->first == this->last)
            {
                this->first = (Node*)NULL;
                this->last = (Node*)NULL;
                delete current;
            }
            else if (current == this->first)
            {
                this->first = this->first->getNext();
                this->first->setPrev((Node*)NULL);
                delete current;
            }
            else if (current == this->last)
            {
                this->last = this->last->getPrev();
                this->last->setNext((Node*)NULL);
                delete current;
            }
            else
            {
                Node* prv = current->getPrev();
                Node* nxt = current->getNext();
                prv->setNext(nxt);
                nxt->setPrev(prv);
                delete current;
            }
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
    std::cout << dll.getLst()->getData() << std::endl;
    dll.InsertAfter(7,9);
    dll.PrintDLL();
    return EXIT_SUCCESS;
}
