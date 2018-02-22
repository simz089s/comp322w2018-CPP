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
    Node* getFst() const;
    Node* getLst() const;
    void setFst(Node* head);
    void setLst(Node* tail);
    void PrintDLL() const;
    void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
    void InsertBefore( int valueToInsertBefore, int valueToBeInserted);
    void Delete(int value);
    void Sort();
    bool IsEmpty();
    int GetHead();
    int GetTail();

private:
    Node* first;
    Node* last;
};

#endif /* DLINKEDLIST_H */
