#ifndef GTEST_DEMO4_H_
#define GTEST_DEMO4_H_

#include <map>
#include <string>

using std::string;

class FooInterface {
public:
    virtual ~FooInterface() {}

    virtual void VoidReturning(int x) = 0;

    virtual int Nullary() = 0;
    virtual bool Unary(int x) = 0;
    virtual long Binary(short x, int y) = 0;
    virtual int Decimal(bool b, char c, short d, int e, long f,
                        float g, double h, unsigned i, char* j, const string& k) = 0;

    virtual bool TakesNonConstReference(int& n) = 0;
    virtual string TakesConstReference(const int& n) = 0;
    virtual bool TakesConst(const int x) = 0;

    virtual int OverloadedOnArgumentNumber() = 0;
    virtual int OverloadedOnArgumentNumber(int n) = 0;

    virtual int OverloadedOnArgumentType(int n) = 0;
    virtual char OverloadedOnArgumentType(char c) = 0;

    virtual int OverloadedOnConstness() = 0;
    virtual char OverloadedOnConstness() const = 0;

    virtual int TypeWithHole(int (*func)()) = 0;
    virtual int TypeWithComma(const std::map<int, string>& a_map) = 0;

#if GTEST_OS_WINDOWS
    STDMETHOD_(int, CTNullary)() = 0;
    STDMETHOD_(bool, CTUnary)(int x) = 0;
    STDMETHOD_(int, CTDecimal)(bool b, char c, short d, int e, long f,
                               float g, double h, unsigned i, char* j, const string& k) = 0;
    STDMETHOD_(char, CTConst)(int x) const = 0;
#endif  // GTEST_OS_WINDOWS
};


template <typename T>
class StackInterface {
public:
    virtual ~StackInterface() {}

    // Template parameter appears in function parameter.
    virtual void Push(const T& value) = 0;
    virtual void Pop() = 0;
    virtual int GetSize() const = 0;
    // Template parameter appears in function return type.
    virtual const T& GetTop() const = 0;
};


#if GTEST_OS_WINDOWS
template <typename T>
class StackInterfaceWithCallType {
public:
    virtual ~StackInterfaceWithCallType() {}

    // Template parameter appears in function parameter.
    STDMETHOD_(void, Push)(const T& value) = 0;
    STDMETHOD_(void, Pop)() = 0;
    STDMETHOD_(int, GetSize)() const = 0;
    // Template parameter appears in function return type.
    STDMETHOD_(const T&, GetTop)() const = 0;
};
#endif

#endif // GTEST_DEMO11_H_
