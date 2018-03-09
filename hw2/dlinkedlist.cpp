/**
 * Student name:
 * First: Simon
 * Last: Zheng
 * 
 * Student ID:
 * 260 744 353
 * 
 * TODO :
 * - Write test code in main
 * - Implement optimizations for last questions
 */

#include <iostream>
#include <cstdlib>

#include "dlinkedlist.h"

// using namespace std;

// Something like `static constexpr Node* const NNULL = (Node*)NULL;` (C++11)
// might be useful or using nullptr (C++11)

/**
 * Header file structure:

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

DLLStructure::DLLStructure() : first((Node*)NULL), last((Node*)NULL), size(0)
{
    // this->first = (Node*)NULL;
    // this->last = (Node*)NULL;
}

DLLStructure::~DLLStructure()
{
    if (this->first == (Node*)NULL) { return; }
    this->size = 0;
    if (this->first == this->last) { delete this->first; return; }
    for (Node* current = this->first->getNext(); current != (Node*)NULL; current = current->getNext())
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

DLLStructure::DLLStructure(int array[], int size) : first((Node*)NULL), last((Node*)NULL), size(size)
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
    if (this->first == (Node*)NULL) { return; }
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
            this->size++;
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
                Node* newFirst = new Node(valueToBeInserted, current, (Node*)NULL);
                current->setPrev(newFirst);
                this->first = newFirst;
                this->size++;
            }
            else
            {
                // [1,2,2,4] InsertBefore(4, 99) ???
                // HACK
                Node* tmpFirst = this->first;
                this->first = current->getPrev();
                this->InsertAfter(this->first->getData(), valueToBeInserted);
                this->first = tmpFirst;
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
            this->size--;
            return;
        }
    }
}

// Get node at index
Node* DLLStructure::Get(int idx) const
{
    for (Node* current = this->first; current != (Node*)NULL; current = current->getNext(), idx--)
        if (idx == 0) { return current; }
    return (Node*)NULL;
}

// Shell sort
void DLLStructure::Sort()
{
    if (this->first == (Node*)NULL || this->first->getNext() == (Node*)NULL) { return; }
    int size = this->GetSize();
	for (int h = size/2; h > 0; h/=2)
    {
		for (int i = h; i < size; i++)
        {
			int tmp = this->Get(i)->getData();
            int j;
			for (j = i; j >= h && this->Get(j-h)->getData() > tmp; j-=h)
				this->Get(j)->setData(this->Get(j-h)->getData());
			this->Get(j)->setData(tmp);
		}
	}
}

bool DLLStructure::IsEmpty() const
{
    return this->first == (Node*)NULL;
    // return this->size == 0;
}

int DLLStructure::GetHead() const
{
    if (this->IsEmpty()) { return 0; }
    return this->first->getData();
}

int DLLStructure::GetTail() const
{
    if (this->IsEmpty()) { return 0; }
    return this->last->getData();
}

/**
 * Using a size private class variable/field/member that gets propely updated by
 * methods that change the size would be much more convenient and efficient.
 */
int DLLStructure::GetSize() const
{
    // int size = 0;
    // for (Node* current = this->first; current != (Node*)NULL; current = current->getNext(), size++);
    // return size;
    return this->size;
}

/**
 * We could keep a max and min private class variable/field/member in DLLStructure.
 * Only updating the max and min when a node gets added or remove, or when a node
 * data changes could make things more efficient. Adding a node or changing a
 * value would be easier as it just requires a comparison to the new value with
 * the current max and min to update them.
 * Also, depending on the use of the linked list, we could keep the list sorted.
 */

int DLLStructure::GetMax() const
{
    int max = this->GetHead();
    for (Node* current = this->first->getNext(); current != (Node*)NULL; current = current->getNext())
        max = max > current->getData() ? max : current->getData();
    return max;
}

int DLLStructure::GetMin() const
{
    int min = this->GetHead();
    for (Node* current = this->first->getNext(); current != (Node*)NULL; current = current->getNext())
        min = min < current->getData() ? min : current->getData();
    return min;
}

/**
 * The default copy constructor would only make a shallow copy, i.e. copy the
 * references (or rather pointers) of the list. This is because of the structure
 * of the list which is actually a chain of pointers to node objects. So the
 * supposed "copy" would actually reference or point to the original list and
 * thus any changes to the "copy" would change the original, ruining the point
 * of the copy (at least if we wanted a deep copy).
 */
DLLStructure::DLLStructure(DLLStructure& dlls) : first((Node*)NULL), last(this->first), size(0)
{
    // int a[] = {dlls.GetHead()};
    // DLLStructure dll(a, sizeof(a)/sizeof(int)); Could also use delegate constructor (C++11)
    if (dlls.IsEmpty()) { return; }
    this->first = new Node(dlls.GetHead(), (Node*)NULL, (Node*)NULL);
    this->size++;
    if (dlls.first == dlls.last/* && dlls.GetSize() == 2*/)
    {
        this->last = this->first;
        return;
    }
    for (Node* current = dlls.last; current != dlls.first; current = current->getPrev())
    {
        this->InsertAfter(this->GetHead(), current->getData());
        if (current == dlls.last) { this->last = this->first->getNext(); }
    }
}

// Test function to print head and tail
void prFstLst(DLLStructure& dll)
{ std::cout << dll.GetHead() << ", " << dll.GetTail() << std::endl; }

// Test function
void Test()
{
    int array[] = {13,42,69,360,420};
    DLLStructure dll(array, sizeof(array)/sizeof(int));
    dll.PrintDLL();
    dll.InsertAfter(13,7);
    dll.PrintDLL();
    dll.InsertAfter(420,7);
    dll.PrintDLL();
    prFstLst(dll);
    dll.InsertAfter(7,9);
    dll.PrintDLL();
    dll.Delete(7);
    dll.Delete(7);
    dll.Delete(9);
    dll.InsertAfter(13, 12);
    dll.Delete(13);
    dll.Delete(420);
    dll.PrintDLL();
    prFstLst(dll);
    dll.InsertAfter(360,420);
    dll.PrintDLL();
    prFstLst(dll);
    std::cout << dll.GetSize() << std::endl;
    dll.Delete(12); dll.Delete(42); dll.Delete(69); dll.Delete(360); dll.Delete(420);
    dll.PrintDLL();
    std::cout << dll.GetSize() << std::endl;
    std::cout << (dll.IsEmpty() ? "true" : "false") << std::endl;
    dll.setFst(new Node(1, new Node(2, (Node*)NULL, (Node*)NULL), (Node*)NULL));
    dll.setLst(dll.getFst()->getNext());
    dll.getLst()->setPrev(dll.getFst());
    dll.PrintDLL();
    prFstLst(dll);
    std::cout << dll.GetSize() << std::endl;
    dll.InsertBefore(2, 0);
    dll.PrintDLL();
    prFstLst(dll);
    dll.InsertBefore(1, -1);
    dll.PrintDLL();
    prFstLst(dll);
    dll.InsertBefore(1, -1);
    dll.PrintDLL();
    prFstLst(dll);
    dll.InsertBefore(1, 9);
    dll.PrintDLL();
    prFstLst(dll);
    dll.Sort();
    dll.PrintDLL();
    // for(int i=0;i<dll.GetSize();i++)std::cout<<dll.Get(i)->getData()<<" ";std::cout<<std::endl;
    prFstLst(dll);
    // int a[] = {10000};
    // DLLStructure bigdll(a, sizeof(a)/sizeof(int));
    // for(int i=0;i<a[0];i++)bigdll.InsertAfter(10000, i);
    // bigdll.PrintDLL();
    // bigdll.Sort();
    // bigdll.PrintDLL();
    // prFstLst(bigdll);
    std::cout << dll.GetMax() << std::endl;
    std::cout << dll.GetMin() << std::endl;
    std::cout << "COPY" << std::endl;
    DLLStructure dllcopy(dll);
    dllcopy.PrintDLL();
    prFstLst(dllcopy);
    dllcopy.InsertAfter(0, -2);
    dllcopy.InsertBefore(0, 10);
    dllcopy.PrintDLL();
    dll.PrintDLL();
    dllcopy.Sort();
    dllcopy.PrintDLL();
    prFstLst(dllcopy);
    std::cout << dllcopy.GetSize() << std::endl <<
                 dllcopy.GetMax()  << std::endl <<
                 dllcopy.GetMin()  << std::endl;
}

int main(void)
{
    // TEST NODE CLASS DIRECTLY
    Node node(42, nullptr, nullptr);
    std::cout << node.getData() << " " << node.getPrev() << " " << node.getNext() << std::endl;
    node.setData(-1);
    node.setPrev(&node);
    node.setNext(&node);
    std::cout << node.getData() << " " << node.getPrev() << " " << node.getNext() << std::endl;
    Node* node_ptr = new Node();
    delete node_ptr;

    // TEST DLLSTRUCTURE CLASS
    DLLStructure* dll_ptr = new DLLStructure();
    delete dll_ptr;
    int array[] = { 11, 2, 7, 22, 4 };
    DLLStructure dll_original(array, sizeof(array)/sizeof(int)); // note that 5 is the size of the array
    DLLStructure dll(dll_original);
    dll.PrintDLL();
    dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
    dll.PrintDLL(); // the output should be: 11, 2, 7, 13, 22, 4
    dll.InsertBefore(7, 26); // To insert 26 before the first occurence of 7
    dll.PrintDLL(); // the output should be: 11, 2, 26, 7, 13, 22, 4
    dll.Delete(22);
    dll.PrintDLL(); // the output should be: 11, 2, 26, 7, 13, 4
    dll.Sort();
    dll.PrintDLL(); // the output should be: 2, 4, 7, 11, 13, 26
    std::cout << "isEmpty: " << dll.IsEmpty() << std::endl
              << "GetHead: " << dll.GetHead() << std::endl
              << "GetTail: " << dll.GetTail() << std::endl
              << "GetSize: " << dll.GetSize() << std::endl
              << "GetMax : " << dll.GetMax () << std::endl
              << "GetMin : " << dll.GetMin () << std::endl;
    dll_original.PrintDLL();
    std::cout << "isEmpty: " << dll_original.IsEmpty() << std::endl
              << "GetHead: " << dll_original.GetHead() << std::endl
              << "GetTail: " << dll_original.GetTail() << std::endl
              << "GetSize: " << dll_original.GetSize() << std::endl
              << "GetMax : " << dll_original.GetMax () << std::endl
              << "GetMin : " << dll_original.GetMin () << std::endl;

    // Test();
    return EXIT_SUCCESS;
}
