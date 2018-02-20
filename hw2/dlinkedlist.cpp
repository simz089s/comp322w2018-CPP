#include <iostream>
#include <cstdlib>

#include "dlinkedlist.h"

/**
 * Node
 */

Node::Node()
{
    this->data = 0;
    this->next = (Node*)NULL;
    this->previous = (Node*)NULL;
}

Node::~Node() {}

Node::Node(int data, Node* next, Node* previous)
{
    this->data = data;
    this->next = next;
    this->previous = previous;
}

int Node::getData() { return this->data; }
Node* Node::getNext() { return this->next; }
Node* Node::getPrev() { return this->previous; }

void Node::setData(int data) { this->data = data; }
void Node::setNext(Node* next){ this->next = next; }
void Node::setPrev(Node* previous) { this->previous = previous; }

/**
 * DLLStructure
 */

Node* DLLStructure::getHd() { return this->head; }
Node* DLLStructure::getTl() { return this->tail; }
void DLLStructure::setHd(Node* head) { this->head = head; }
void DLLStructure::setTl(Node* tail) { this->tail = tail; }

DLLStructure::DLLStructure()
{
    this->head = (Node*)NULL;
    this->tail = (Node*)NULL;
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

DLLStructure::DLLStructure(int array[], int length)
{
    this->head = (Node*)NULL;
    this->tail = (Node*)NULL;
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

void DLLStructure::PrintDLL()
{
    for (Node* current = this->getHd(); current != (Node*)NULL; current = current->getNext())
        std::cout << current->getData() << std::endl;
}

void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted)
{
    
}

int main(void)
{
    int array[] = {13,42,69,360,420};
    DLLStructure dll(array, sizeof(array)/sizeof(int));
    dll.PrintDLL();
    return EXIT_SUCCESS;
}
