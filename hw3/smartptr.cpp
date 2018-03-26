/**
 * Student name :
 * Simon
 * Zheng
 * 
 * Student ID :
 * 260 744 353
 * 
 * For Trottier Ubuntu machines :
 *  g++-5 -Wno-unused -std=gnu++17 -g -ggdb smartptr.cpp
 * or simply :
 *  gcc -std=gnu++14 smartptr.cpp
 * (C++11 should be enough, Ubuntu compiles with GNU extensions by default)
 * 
 * Otherwise, compiled for (almost) latest C++ with either :
 *  g++-7 -Wno-unused -std=gnu++17 -g -ggdb smartptr.cpp
 *  clang++-4.0 -Wno-unused -Wno-unused-parameter -std=c++1z -g -ggdb smartptr.cpp
 *  g++-6 -Wno-unused -std=gnu++17 -g -ggdb smartptr.cpp
 *  clang++-3.8 -Wno-unused -Wno-unused-parameter -std=c++1z -g -ggdb smartptr.cpp
 * 
 * Trottier Ubuntu machines seem to use gcc 5.4 and clang 3.8 but clang-3.8
 * seems to not work as opposed to (any) gcc.
 */

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

// auto_ptr has a copy constructor and assignment operator but not unique_ptr (see comments)
template <class T>
class SmartPointer
{
    T* raw_ptr;
public:
    SmartPointer<T>(T const x = 0); // SmartPointer<T>() : SmartPointer(0) {} delegate constructor (C++11) also works
	SmartPointer<T>(SmartPointer<T>&);// = delete; // or make them private
    ~SmartPointer<T>();
    T getValue() const;
    void setValue(T);
    T* get() const { return raw_ptr; }
	SmartPointer<T>& operator=(SmartPointer<T>&);// = delete; // or make them private
    template <class U> friend SmartPointer<T> operator+(const SmartPointer<T>& l, const SmartPointer<T>& r);
    template <class U> friend SmartPointer<T> operator-(const SmartPointer<T>& l, const SmartPointer<T>& r);
    template <class U> friend SmartPointer<T> operator*(const SmartPointer<T>& l, const SmartPointer<T>& r);
};

template <typename T>
SmartPointer<T>::SmartPointer(T const x) : raw_ptr(nullptr)
{
    if (x < 0)
    {
        throw std::invalid_argument("negative numbers not supported by smart pointer");
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

template <typename T>
SmartPointer<T>::SmartPointer(SmartPointer<T>& original) : raw_ptr(original.raw_ptr)
{
	// raw_ptr = original.raw_ptr;
	original.raw_ptr = nullptr;
}

template <typename T>
SmartPointer<T>::~SmartPointer<T>()
{
	delete raw_ptr;
	raw_ptr = nullptr;
}

template <typename T>
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

template <typename T>
void SmartPointer<T>::setValue(T val) {
    if (val < 0)
    {
        throw std::invalid_argument("negative numbers not supported by smart pointer");
    }
    if (raw_ptr == nullptr)
    {
        raw_ptr = new T(val);
    }
    else
    {
        *raw_ptr = val;
    }
}

template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>& sp)
{
	if (this == &sp)
	{
		return sp;
	}
	delete raw_ptr;
	raw_ptr = sp.raw_ptr;
	sp.raw_ptr = nullptr;
	return *this;
}

template <typename T>
SmartPointer<T> operator+(const SmartPointer<T>& l, const SmartPointer<T>& r)
{
    return SmartPointer<T>(l.getValue() + r.getValue());
}

template <typename T>
SmartPointer<T> operator-(const SmartPointer<T>& l, const SmartPointer<T>& r)
{
    return SmartPointer<T>(l.getValue() - r.getValue());
}

template <typename T>
SmartPointer<T> operator*(const SmartPointer<T>& l, const SmartPointer<T>& r)
{
    return SmartPointer<T>(l.getValue() * r.getValue());
}

// auto f(int a, double b) -> decltype(a+b)
// {
//     auto x {0};
//     decltype(x) y;
//     constexpr int z {0};
//     decltype(z) zz = 0;
//     decltype(zz) zzz {0};
//     return zz;
// }

int main(int argc, char** argv)
{
    // Question 2
    std::cout << "Question 2 :" << std::endl;

    SmartPointer<int> sPointer(11);
    std::cout << "'SmartPointer<int> sPointer(11)' :" << std::endl;
    std::cout << sPointer.getValue() << std::endl;

    SmartPointer<int> sPointer2;
    sPointer2.setValue(133);
    std::cout << "'SmartPointer<int> sPointer' and 'setValue(133)' :" << std::endl;
    std::cout << sPointer2.getValue() << std::endl;

    // Question 3
    std::cout << "\nQuestion 3 :" << std::endl;
    std::cout << "'SmartPointer<int> sPointer(-1)' (with fake error message) :" << std::endl;
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

    // Question 4
    std::cout << "\nQuestion 4 :" << std::endl;

    SmartPointer<double> sPointer4;
    std::cout << "'SmartPointer<double> sPointer' :" << std::endl;
    std::cout << sPointer4.getValue() << std::endl
              << typeid(sPointer4.getValue()).name() << std::endl;

    SmartPointer<float> sPointer5;
    sPointer5.setValue(13.31f);
    std::cout << "'SmartPointer<float> sPointer' and 'setValue(13.31)' :" << std::endl;
    std::cout << sPointer5.getValue() << std::endl
              << typeid(sPointer5.getValue()).name() << std::endl;

    // Question 5
    std::cout << "\nQuestion 5 :" << std::endl;

    // std::cout << (sPointer4 - sPointer5).getValue() << std::endl;

    SmartPointer<float> sPointer6;
    sPointer6.setValue(1.5f);
    SmartPointer<float> sPointer7;
    sPointer7.setValue(2.5f);
    SmartPointer<float> sPointer8 = sPointer6 + sPointer7;
    std::cout << "'SmartPointer<float> sPointer1' and 'setValue(1.5)'" << std::endl
              << "'SmartPointer<float> sPointer2' and 'setValue(2.5)'" << std::endl
              << "SmartPointer(1.5) + SmartPointer(2.5) = "
              << sPointer8.getValue() << std::endl // prints 4
			  << typeid(sPointer8.getValue()).name() << std::endl;

	// Copying assignment operator (or rather moving)
    std::cout << "\nCopy assignment operator" << std::endl;
	SmartPointer<float> sp1(1);
	SmartPointer<float> sp2;
	sp2 = sp1;
    std::cout << "Original : ";
	try
	{
		std::cout << sp1.getValue() << std::endl;
	}
	catch (const std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "New : " << sp2.getValue()
			  << typeid(sp2.getValue()).name() << std::endl;
    
    // Copy contructor
    std::cout << "\nCopy constructor" << std::endl;
	SmartPointer<float> sp3(sp2);
    std::cout << "Original : ";
	try
	{
		std::cout << sp2.getValue() << std::endl;
	}
	catch (const std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "New : " << sp3.getValue()
		      << typeid(sp3.getValue()).name() << std::endl;
    
	SmartPointer<float> sp4 = sp3;
    std::cout << "Original : ";
	try
	{
		std::cout << sp3.getValue() << std::endl;
	}
	catch (const std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "New : " << sp4.getValue()
		      << typeid(sp4.getValue()).name() << std::endl;

    return EXIT_SUCCESS;
}
