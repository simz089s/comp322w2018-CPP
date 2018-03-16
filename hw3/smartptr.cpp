#include <iostream>
#include <cstdlib>
#include <typeinfo>

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

template <typename T>
class SmartPointer
{
    T* raw_ptr;
public:
    template <class U> SmartPointer<T>();
    template <class U> SmartPointer<T>(T);
    ~SmartPointer<T>();
    template <class U> T getValue() const;
    template <class U> void setValue(T);
    template <class U> T* get() const;
    template <class U> SmartPointer<T>& operator=(SmartPointer<T>&);
    template <class U> friend SmartPointer<T>& operator+(SmartPointer<T>&, SmartPointer<T>&);
    // friend SmartPointer<T>& operator-(SmartPointer&, SmartPointer&);
    // friend SmartPointer<T>& operator*(SmartPointer&, SmartPointer&);
};

template <class T>
SmartPointer<T>::SmartPointer() : SmartPointer(0)
{
}

template <class T>
SmartPointer<T>::SmartPointer(T x) : raw_ptr(nullptr)
{
    if (x < 0)
    {
        throw std::invalid_argument("smart pointer does not handle negative numbers");
    }
    try
    {
        raw_ptr = new T(x);
    }
    catch (const std::bad_alloc& e)
    {
        std::cout << "Failure to allocate variable: " << e.what() << std::endl;
    }
}

template <class T>
SmartPointer<T>::~SmartPointer()
{
    delete raw_ptr;
}

template <class T>
T SmartPointer<T>::getValue() const
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

template <class T>
void SmartPointer<T>::setValue(T val) {
    if (raw_ptr == nullptr)
    {
        raw_ptr = new T(val);
    }
    else
    {
        *raw_ptr = val;
    }
}

template <class T>
T* SmartPointer<T>::get() const
{
    return raw_ptr;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>& sp)
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

template <class T, class L, class R>
SmartPointer<T>& SmartPointer<T>::operator+(const SmartPointer<L>& l, const SmartPointer<R>& r) -> decltype(l.getValue()+r.getValue())
{
    return l.getValue() + r.getValue();
}

auto f()
{
    auto x {0};
    decltype(x) y;
    constexpr int z {0};
    decltype(z) zz = 0;
    return zz;
}

int main(int argc, char** argv)
{
    SmartPointer<int> sPointer(11);
    std::cout << "'SmartPointer<int> sPointer(11)' :" << std::endl;
    std::cout << sPointer.getValue() << std::endl;

    SmartPointer<int> sPointer2;
    sPointer2.setValue(133);
    std::cout << "'SmartPointer<int> sPointer' and 'setValue(133)' :" << std::endl;
    std::cout << sPointer2.getValue() << std::endl;

    std::cout << "'SmartPointer<int> sPointer(-1)' :" << std::endl;
    try
    {
        SmartPointer<int> sPointer3(-1);
    }
    catch (const std::invalid_argument e)
    {
        std::cout << "terminate called after throwing an instance of 'std::invalid_argument'"
                  << std::endl << "  what():  "
                  << e.what() << "\nAborted" << std::endl;
    }

    SmartPointer<double> sPointer4;
    std::cout << "'SmartPointer<double> sPointer' :" << std::endl;
    std::cout << sPointer4.getValue() << std::endl
              << typeid(sPointer4.getValue()).name() << std::endl;

    SmartPointer<float> sPointer5;
    sPointer5.setValue(13.31f);
    std::cout << "'SmartPointer<float> sPointer' and 'setValue(13.31)' :" << std::endl;
    std::cout << sPointer5.getValue() << std::endl;

    return EXIT_SUCCESS;
}
