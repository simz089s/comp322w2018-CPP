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

#endif /* DLINKEDLIST_H */
