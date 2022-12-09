#pragma once
#include <string>

class BigNum {
public:
    BigNum(int value = 0); // Default to zero unless specified otherwise.
    ~BigNum();

    std::string toString() const; // Get a string representation
    void add(const BigNum& value);
    int getSize() const;
    int getNumber(int index) const;
    void setNumber(int index, int val);
private:
    int *_elements;
    int _size;
};
