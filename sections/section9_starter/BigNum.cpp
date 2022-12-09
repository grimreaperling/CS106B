#include "BigNum.h"
#include "SimpleTest.h"
#include <iostream>

using namespace std;

const int kDefaultSize = 10;

BigNum::BigNum(int value) {
    _elements = new int[kDefaultSize]();
    int loc = kDefaultSize - 1;
    if (value == 0) {
        _elements[loc] = 0;
        _size = 1;
        return;
    }
    while (value != 0) {
        _elements[loc] = value % 10;
        value = value / 10;
        loc--;
    }
    _size = kDefaultSize - loc - 1;
}

BigNum::~BigNum() {
    delete[] _elements;
}

string BigNum::toString() const {
    string res = "";
    int index = kDefaultSize - _size;
    while (index < kDefaultSize) {
       res += to_string(_elements[index]); 
       index++;
    }
    return res;
}

void BigNum::add(const BigNum& value) {
    if (getSize() > value.getSize()) {
        for (int i = 0; i < value.getSize(); i++) {
            int res = getNumber(i) + value.getNumber(i);
            setNumber(i, res);
        }
    } else {
        for (int i = 0; i < getSize(); i++) {
            int res = getNumber(i) + value.getNumber(i);
            setNumber(i, res);
        }
        int index = getSize();
        while (index < value.getSize()) {
            setNumber(index, value.getNumber(index));
            index++;
        }
        _size = value.getSize();
    }
}

int BigNum::getSize() const {
    return _size;
}

/* Get the number of the given index. */
int BigNum::getNumber(int index) const {
    if (index >= _size) error("Out of the boundary!");
    int loc = kDefaultSize - index - 1;
    return _elements[loc];
}

/* Set the number of the index with the given value. */
void BigNum::setNumber(int index, int val) {
    int loc = kDefaultSize - index - 1;
    _elements[loc] = val;
}

STUDENT_TEST("Test on the getNumber!") {
    BigNum small(106);
    EXPECT_EQUAL(small.getNumber(0), 6);
    EXPECT_EQUAL(small.getNumber(1), 0);
    EXPECT_EQUAL(small.getNumber(2), 1);
}

PROVIDED_TEST("Simple BigNum Tests") {
    BigNum zero(0);
    BigNum small(106);
    BigNum large(78979871);

    EXPECT_EQUAL(zero.toString(), "0");
    EXPECT_EQUAL(small.toString(), "106");
    EXPECT_EQUAL(large.toString(), "78979871");

    small.add(zero);
    EXPECT_EQUAL(zero.toString(), "0");
    EXPECT_EQUAL(small.toString(), "106");

    zero.add(small);
    EXPECT_EQUAL(zero.toString(), "106");
    EXPECT_EQUAL(small.toString(), "106");

    large.add(small);
    EXPECT_EQUAL(small.toString(), "106");
    EXPECT_EQUAL(large.toString(), "78979977");
}
