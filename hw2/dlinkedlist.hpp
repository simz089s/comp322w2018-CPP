#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

class Node
{
private:
    int data;
    Node* next;
    Node* previous;

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
};

class DLLStructure
{
private:
    Node* first;
    Node* last;
    int size;

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
    Node* Get(int idx) const;
    void Sort();
    bool IsEmpty() const;
    int GetHead() const;
    int GetTail() const;
    int GetSize() const;
    int GetMax() const;
    int GetMin() const;
    DLLStructure(DLLStructure& dlls);
};

#endif /* DLINKEDLIST_H */
