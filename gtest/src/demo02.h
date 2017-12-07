#ifndef GTEST_DEMO2_H_
#define GTEST_DEMO2_H_

#include <string.h>


// A simple string class.
class MyString {
private:
    const char* c_string_;
    const MyString& operator=(const MyString& rhs);

public:
    // Clones a 0-terminated C string, allocating memory using new.
    static const char* CloneCString(const char* a_c_string);

    // The default c'tor constructs a NULL string.
    MyString() : c_string_(NULL) {}

    // Constructs a MyString by cloning a 0-terminated C string.
    explicit MyString(const char* a_c_string) : c_string_(NULL) {
        Set(a_c_string);
    }

    // Copy c'tor
    MyString(const MyString& string) : c_string_(NULL) {
        Set(string.c_string_);
    }

    ~MyString() {
        delete[] c_string_;
    }

    // Gets the 0-terminated C string this MyString object represents.
    const char* c_string() const {
        return c_string_;
    }

    size_t Length() const {
        return c_string_ == NULL ? 0 : strlen(c_string_);
    }

    // Sets the 0-terminated C string this MyString object represents.
    void Set(const char* c_string);
};


#endif  // GTEST_DEMO2_H_
