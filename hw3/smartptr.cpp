#include <iostream>
#include <cstdlib>

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
    SmartPointer() : raw_ptr(nullptr) {}
    SmartPointer(int x) : raw_ptr(new int(x)) {}
    ~SmartPointer() {}
    int* get() const { return raw_ptr; }
    SmartPointer& operator=(SmartPointer& sp);
};

SmartPointer& SmartPointer::operator=(SmartPointer& sp)
{
    raw_ptr = sp.raw_ptr;
    sp.raw_ptr = nullptr;
    return *this;
}

auto f() { return 0; }

int main(int argc, char** argv)
{
    auto x {8};
    decltype(x) z;
    constexpr int y {0};
    SmartPointer sPointer(11);
    return EXIT_SUCCESS;
}
