#include <iostream>
#include <cstdlib>

// using namespace std;

/**
 * Question 1
 * =============================================================================
 * auto_ptr : the old smart pointer.
 * 
 * The reference is unique, meaning it is held by only one (auto) pointer at any
 * time. It can be passed but not shared or copied (original will become NULL).
 * The pointer is destructed with delete (only for new, not other manual allocs)
 * when it goes out of scope. Useful against memory leaks and dangling pointers.
 * =============================================================================
 * unique_ptr : the new smart pointer used to replace auto_ptr.
 * 
 * The pointer is also unique, hence the name, and can only be moved, not copied
 * in any way (including things like passing by value to a function, etc.). Once
 * again, when it is moved to another unique_ptr the original loses the data.
 * =============================================================================
 * weak_ptr :
 * 
 * This and shared_ptr are like the way we use raw pointers. They can keep track
 * of whether it is still being referenced and if it is allocated or deallocated
 * and thus it helps a lot with dangling pointers. It does not affect the
 * reference count of the associated shared_ptr though. These two types of smart
 * pointers work together. A weak_ptr is like a "view" on a shared_ptr. When it
 * goes out of scope, the pointed object does not disappear.
 * =============================================================================
 * shared_ptr :
 * 
 * A shared_ptr counts the references for the raw pointer. We can also tell
 * ownership and have cyclic references. As their names imply, shared_ptr can
 * share ownership as opposed to unique_ptr.
 * =============================================================================
 * There are also intrusive_ptr (similar to unique_ptr) and scoped_ptr (similar
 * to shared_ptr).
 */

class SmartPointer
{
    int* raw_ptr;
public:
    SmartPointer();
    SmartPointer(int x);
    ~SmartPointer();
    int getValue() const;
    void setValue(int val);
    int* get() const;
    SmartPointer& operator=(SmartPointer& sp);
};

SmartPointer::SmartPointer() : SmartPointer(0)
{
}

SmartPointer::SmartPointer(int x)// : raw_ptr(new int(x))
{
    if (x < 0)
    {
        throw std::invalid_argument("smart pointer does not handle negative numbers");
    }
    try
    {
        raw_ptr = new int(x);
    }
    catch (const std::bad_alloc& e)
    {
        std::cout << "Failure to allocate variable: " << e.what() << std::endl;
    }
}

SmartPointer::~SmartPointer()
{
    delete raw_ptr;
}

int SmartPointer::getValue() const
{
    if (raw_ptr == nullptr)
    {
        throw std::invalid_argument("getting value from null pointer exception");
    }
    else
    {
        return *raw_ptr;
    }
}

void SmartPointer::setValue(int val) {
    if (raw_ptr == nullptr)
    {
        raw_ptr = new int(val);
    }
    else
    {
        *raw_ptr = val;
    }
}

int* SmartPointer::get() const
{
    return raw_ptr;
}

SmartPointer& SmartPointer::operator=(SmartPointer& sp)
{
    if (this == &sp)
    {
        return sp;
    }
    raw_ptr = sp.raw_ptr;
    sp.raw_ptr = nullptr;
    // delete &sp;
    return *this;
}

auto f()
{
    auto x {0};
    decltype(x) y;
    constexpr int z {0};
    return y;
}

int main(int argc, char** argv)
{
    SmartPointer sPointer(11);
    std::cout << sPointer.getValue() << std::endl;

    SmartPointer sPointer2;
    sPointer2.setValue(133);
    std::cout << sPointer2.getValue() << std::endl;

    try
    {
        SmartPointer sPointer3(-1);
    }
    catch (const std::invalid_argument e)
    {
        std::cout << "terminate called after throwing an instance of 'std::invalid_argument'"
                  << std::endl << "  what():  "
                  << e.what() << "\nAborted" << std::endl;
    }

    return EXIT_SUCCESS;
}
