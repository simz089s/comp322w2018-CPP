#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

class Node
{
public:
    Node();
    // ~Node(); Nothing to delete
    Node(int data, Node* next, Node* previous);
    int getData() const;
    Node* getNext() const;
    Node* getPrev() const;
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
    Node* getHd() const;
    Node* getTl() const;
    void setHd(Node* head);
    void setTl(Node* tail);
    void PrintDLL() const;
    void InsertAfter(int valueToInsertAfter, int valueToBeInserted);

private:
    Node* head;
    Node* tail;
};

#endif /* DLINKEDLIST_H */
