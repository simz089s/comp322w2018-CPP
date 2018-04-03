// <-- UTF-8 BOM right there
/**
 * Student
 *  First name: Simon
 *  Last name:  Zheng
 *  ID:         260 744 353
 * 
 * Simplest :
 *  g++ -Wno-unused -std=gnu++14 smartptr.cpp
 *  clang++ -Wno-unused -Wno-unused-parameter -std=gnu++14 smartptr.cpp
 * 
 * Otherwise, compiled for latest C++ and compiler with either :
 * 
 * gcc C++17 + GNU extensions (or as I like to call it, GNU/extensions)
 *  g++-7 -Wno-unused -std=gnu++17 smartptr.cpp
 *  g++-7 -Wno-unused -std=gnu++2a smartptr.cpp
 * 
 * clang C++17 + GNU extensions
 *  clang++-5.0 -Wno-unused -Wno-unused-parameter -std=gnu++1z smartptr.cpp
 *  clang++-5.0 -Wno-unused -Wno-unused-parameter -std=gnu++2a smartptr.cpp
 * 
 * clang 3.8 C++17 + GNU extensions
 *  clang++-3.8 -Wno-unused -Wno-unused-parameter -std=gnu++1z smartptr.cpp
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

template <typename T>
// template <class T>
class SmartPointer
{
    T* raw_ptr;// = new T{0};
    size_t* size = nullptr; // Whether signed or unsigned is safer for sizes is still argued...
    bool* isArray = nullptr;
    int* refCnt = nullptr;
public:
    // SmartPointer<T>() : SmartPointer{0} {} // Delegate constructor for default constructor
    SmartPointer(T const x = 0) : SmartPointer(&x) {}
    SmartPointer(T const [], int = 0);
	SmartPointer(const SmartPointer&); // Copy constructor
    ~SmartPointer();

    T getValue(int = 0) const;
    void setValue(T, int = 0);
    T* getValues() const;
    void setValues(T[], int);
    // void setValues(std::initializer_list<T>); pls no
    // void setValues(xs...); nope
    // template <typename ... Ts> void setValues(Ts ... cs); nah
    T* getPointer() const { return raw_ptr; }
    auto getSize() const -> decltype(*size) { return *size; } // or size_t getSize() const
    bool getIsArray() const { return *isArray; } // auto getIsArray() -> decltype(*isArray) const

	SmartPointer& operator=(const SmartPointer&);
    friend SmartPointer<T> operator+(const SmartPointer<T>& l, const SmartPointer<T>& r)
    {
        SmartPointer<T> tmpSP{l.getValue() + r.getValue()};
        (*(tmpSP.refCnt))++;
        return tmpSP;
    }
    friend SmartPointer<T> operator-(const SmartPointer<T>& l, const SmartPointer<T>& r)
    {
        if (l.getValue() < r.getValue())
        {
            throw std::invalid_argument("negative numbers not supported by smart pointer");
        }
        SmartPointer<T> tmpSP{l.getValue() - r.getValue()};
        (*(tmpSP.refCnt))++;
        return tmpSP;
    }
    friend SmartPointer<T> operator*(const SmartPointer<T>& l, const SmartPointer<T>& r)
    {
        SmartPointer<T> tmpSP{l.getValue() * r.getValue()};
        (*(tmpSP.refCnt))++;
        return tmpSP;
    }
};

/**
 * Constructors and destructor
 */

// General constructor
template <typename T>
SmartPointer<T>::SmartPointer(T const x[], int n) : raw_ptr{nullptr}
{
    try
    {
        if (n == 0) // Single value
        {
            if (*x < 0)
            {
                throw std::invalid_argument("negative numbers not supported by smart pointer");
            }
            else
            {
                raw_ptr = new T{*x};
                size = new size_t{0};
                isArray = new bool{false};
            }
        }
        else if (n < 0)
        {
            throw std::invalid_argument("array size cannot be a negative number");
        }
        else // Array case
        {
            isArray = new bool{true};
            size = new size_t{(size_t)n};
            if (x == nullptr)
            {
                raw_ptr = nullptr;
            }
            else
            {
                raw_ptr = new T[*size];
                for (size_t i = 0; i < (*size); i++)
                {
                    raw_ptr[i] = x[i];
                }
            }
        }
        refCnt = new int{1};
    }
    catch (const std::bad_alloc& e)
    {
        std::cout << "Failure to allocate variable: " << e.what() << std::endl;
    }
}

/**
 * Delegates to "general" constructor
 * Does not change refCnt itself so still const, should be invisible to
 * interface anyway so acceptable.
 */
template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& original)// : SmartPointer{original.raw_ptr, (int)*original.size}
{
    // std::cout << "Copy ctor" << std::endl; // TEST
    raw_ptr = original.raw_ptr;
    size = original.size;
    isArray = original.isArray;
    refCnt = original.refCnt;
    (*refCnt)++;
}

template <typename T>
SmartPointer<T>::~SmartPointer<T>()
{
    (*refCnt)--;
    if (*refCnt > 0)
    {
        raw_ptr = nullptr;
        size = nullptr;
        isArray = nullptr;
        refCnt = nullptr;
        return;
    }

    if (*isArray)
	{
        delete[] raw_ptr;
    }
    else
    {
        delete raw_ptr;
    }
    raw_ptr = nullptr;
    delete size;
    size = nullptr;
    delete isArray;
    isArray = nullptr;
    delete refCnt;
    refCnt = nullptr;
}

/**
 * Getters and setter
 */

// Default idx value is 0 and returns value or first element if array
template <typename T>
T SmartPointer<T>::getValue(int idx) const
{
    if (raw_ptr == nullptr)
    {
        throw std::invalid_argument("getting value from null pointer exception");
    }
    if (*isArray)
    {
        if (idx < 0 || (size_t)idx >= *size)
        {
            throw std::out_of_range("index out of bounds");
        }
        return raw_ptr[idx];
    }
    else
    {
        return *raw_ptr;
    }
}

// Mirror behaviour of getValue
template <typename T>
void SmartPointer<T>::setValue(T val, int idx)
{
    if (*isArray)
    {
        if (idx < 0 || (size_t)idx >= *size)
        {
            throw std::out_of_range("index out of bounds");
        }
        raw_ptr[idx] = val;
    }
    else if (val < 0)
    {
        throw std::invalid_argument("negative numbers not supported by smart pointer");
    }
    else if (raw_ptr == nullptr) // This should be avoided
    {
        raw_ptr = new T{val};
    }
    else
    {
        *raw_ptr = val;
    }
}

// Return array or value
template <typename T>
T* SmartPointer<T>::getValues() const
{
    if (*isArray)
    {
        return getPointer();
    }
    else
    {
        return getValue();
    }
}

// Change value into array or array values up to n if already array
template <typename T>
void SmartPointer<T>::setValues(T a[], int n)
{
    if (n < 0)
    {
        throw std::invalid_argument("array size cannot be a negative number");
    }
    if (a == nullptr)
    {
        throw std::invalid_argument("cannot set values from null pointer");
        // (*refCnt)--;
        // size = nullptr;
        // isArray = nullptr;
        // raw_ptr = nullptr;
    }
    if (raw_ptr == nullptr || !*isArray)
    {
        delete raw_ptr;
        raw_ptr = new T[n];
    }
    for (size_t i = 0; i < (*size < n ? *size : n); i++)
    {
        raw_ptr[i] = a[i];
    }
}

/**
 * Copy assignment operator (equal)
 * Shares reference
 * Similar to copy constructor
 */
template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& r)
{
    // std::cout << "Copy op" << std::endl; // TEST
	if (this == &r || raw_ptr == r.raw_ptr)
	{
		return *this;
	}
    (*refCnt)--;
    // Original pointers will get deleted by destructor when out of scope
	raw_ptr = r.raw_ptr;
    isArray = r.isArray;
    size = r.size;
    refCnt = r.refCnt;
    (*refCnt)++;
	return *this;
}

int main(int argc, char** argv)
{
    // Question 2
    std::cout << "Question 2 :" << std::endl;

    SmartPointer<int> sPointer(11);
    std::cout << "'SmartPointer<int> sPointer(11)' :" << std::endl;
    std::cout << sPointer.getValue() << std::endl; // Should be 11
    std::cout << ((sPointer.getValue() == 11)?"pass":"fail") << std::endl;

    SmartPointer<int> sPointer2;
    std::cout << ((sPointer2.getValue() == 0)?"pass":"fail") << std::endl;
    sPointer2.setValue(133);
    std::cout << "'SmartPointer<int> sPointer' and 'setValue(133)' :" << std::endl;
    std::cout << sPointer2.getValue() << std::endl; // Should be 133
    std::cout << ((sPointer2.getValue() == 133)?"pass":"fail") << std::endl;

    // Question 3
    std::cout << "\nQuestion 3 :" << std::endl;
    std::cout << "'SmartPointer<int> sPointer(-1)' (with fake error message, real one after 'what():') :" << std::endl;
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
    std::cout << sPointer4.getValue() << std::endl // Should be 0.0
              << typeid(sPointer4.getValue()).name() << std::endl; // Should be double
    std::cout << ((sPointer4.getValue() == 0.0)?"pass":"fail") << std::endl;
    std::cout << ((typeid(sPointer4.getValue()) == typeid(double))?"pass":"fail") << std::endl;

    SmartPointer<float> sPointer5;
    sPointer5.setValue(13.31f);
    std::cout << "'SmartPointer<float> sPointer' and 'setValue(13.31)' :" << std::endl;
    std::cout << sPointer5.getValue() << std::endl
              << typeid(sPointer5.getValue()).name() << std::endl;
    std::cout << ((sPointer5.getValue() == 13.31f)?"pass":"fail") << std::endl;
    std::cout << ((typeid(sPointer5.getValue()) == typeid(float))?"pass":"fail") << std::endl;

    // Question 5
    std::cout << "\nQuestion 5 :" << std::endl;

    SmartPointer<float> sPointer6;
    sPointer6.setValue(1.5f);
    SmartPointer<float> sPointer7;
    sPointer7.setValue(2.5f);
    SmartPointer<float> sPointer8 = sPointer6 + sPointer7;
    // sPointer8 = sPointer6 + sPointer7;
    std::cout << "'SmartPointer<float> sPointer1' and 'setValue(1.5)'" << std::endl
              << "'SmartPointer<float> sPointer2' and 'setValue(2.5)'" << std::endl
              << "SmartPointer(1.5) + SmartPointer(2.5) = "
              << sPointer8.getValue() << std::endl // Should be 4.0f
			  << typeid(sPointer8.getValue()).name() << std::endl;
    std::cout << ((sPointer6.getValue() == 1.5f)?"pass":"fail") << std::endl;
    std::cout << ((sPointer7.getValue() == 2.5f)?"pass":"fail") << std::endl;
    std::cout << ((sPointer8.getValue() == 4.0f)?"pass":"fail") << std::endl;
    std::cout << ((typeid(sPointer8.getValue()) == typeid(float))?"pass":"fail") << std::endl;
    std::cout << "SmartPointer(1.5) - SmartPointer(2.5) = ";
    try
    {
        sPointer8 = sPointer6 - sPointer7;
    }
    catch (const std::invalid_argument e)
    {
        sPointer8 = sPointer7 - sPointer6;
        std::cout << e.what() << "\nSmartPointer(2.5) - SmartPointer(1.5) = "
                  << sPointer8.getValue() << std::endl // Should be 1.0f
                  << typeid(sPointer8.getValue()).name() << std::endl;
        std::cout << ((sPointer8.getValue()==1.0f)?"pass":"fail") << std::endl
                  << ((typeid(sPointer8.getValue())==typeid(float))?"pass":"fail") << std::endl;
    }
    sPointer8 = sPointer6 * sPointer7;
    std::cout << "SmartPointer(1.5) * SmartPointer(2.5) = "
              << sPointer8.getValue() << std::endl // Should be 3.75f
			  << typeid(sPointer8.getValue()).name() << std::endl;
    std::cout << ((sPointer8.getValue()==3.75f)?"pass":"fail") << std::endl
              << ((typeid(sPointer8.getValue())==typeid(float))?"pass":"fail") << std::endl;
    sPointer8 = sPointer8 - sPointer8;
    std::cout << "SmartPointer(3.75) - itself = "
              << sPointer8.getValue() << std::endl // Should be 0.0f
			  << typeid(sPointer8.getValue()).name() << std::endl;
    std::cout << ((sPointer8.getValue()==0.0f)?"pass":"fail") << std::endl
              << ((typeid(sPointer8.getValue())==typeid(float))?"pass":"fail") << std::endl;

	// Copying assignment operator
    std::cout << "\nCopy assignment operator" << std::endl;
	SmartPointer<float> sp1(1); // is 1.0f
	SmartPointer<float> sp2; // is 0.0f
	sp2 = sp1; // Both 1.0f now
    std::cout << "Original : ";
    std::cout << sp1.getValue()
			  << typeid(sp1.getValue()).name() << std::endl;
	std::cout << "New : " << sp2.getValue()
			  << typeid(sp2.getValue()).name() << std::endl;
    
    // Copy contructor
    std::cout << "\nCopy constructor" << std::endl;
	SmartPointer<float> sp3(sp2); // is 1.0f
    std::cout << "Original : ";
    std::cout << sp2.getValue()
		      << typeid(sp2.getValue()).name() << std::endl;
	std::cout << "New : " << sp3.getValue()
		      << typeid(sp3.getValue()).name() << std::endl;
    
	SmartPointer<float> sp4 = sp3; // is 1.0f
    std::cout << "Original : ";
    std::cout << sp3.getValue()
		      << typeid(sp3.getValue()).name() << std::endl;
	std::cout << "New : " << sp4.getValue()
		      << typeid(sp4.getValue()).name() << std::endl;
    
    std::cout << ((sp1.getValue() == sp2.getValue() &&
                   sp2.getValue() == sp3.getValue() &&
                   sp3.getValue() == sp4.getValue())?"pass":"fail") << std::endl;
    
    double a[] = {1.0, 2.0, 3.0};
    SmartPointer<double> spa(a, 3);
    spa.setValue(4.0);
    std::cout << spa.getValue() << std::endl;
    spa.setValue(4.0, 0);
    std::cout << spa.getValue() << std::endl
              << spa.getValue(1) << std::endl
              << spa.getValues() << std::endl;
    spa.setValues(a, 3);
    std::cout << spa.getValue() << std::endl;

    return EXIT_SUCCESS;
}
