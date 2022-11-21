#include <iostream>
#include "Fraction.h"
#include "SimpleTest.h"


// purpose: the default constructor to create
//          a fraction of 1 / 1
// arguments: none
// return value: none (constructors don't return)
Fraction::Fraction() {
    numer = 1;
    denom = 1;
}

// purpose: an overloaded constructor
//          to create a custom fraction
//	        that immediately gets reduced
// arguments: an int numerator
//            and an int denominator
Fraction::Fraction(int numer, int denom) {
    this->numer = numer;
    this->denom = denom;

    // reduce in case we were given
    // an unreduced fraction
    reduce();
}

// getters for numerator and denominator
int Fraction::getNumer() {
    return numer;
}

int Fraction::getDenom() {
    return denom;
}

void Fraction::reciprocal() {
   int temp = this->numer;
   this->numer = this->denom;
   this->denom = temp;
   reduce();
}

// purpose: to add another fraction
// with this one with the result being
// stored in this fraction
// arguments: another fraction
// return value: none
void Fraction::add(const Fraction &other) {
        // calculate the new numerator
        int newNumer = numer * other.denom + other.numer * denom;

        // calculate the new denominator
        int newDenom = denom * other.denom;

        // replace our values with the new values
        numer = newNumer;
        denom = newDenom;

        // reduce the fraction
        reduce();
}

// purpose: to multiply another fraction
// with this one with the result being
// stored in this fraction
// arguments: another fraction
// return value: none
void Fraction::multiply(const Fraction &other) {
    // multiplies a Fraction
    // with this Fraction
    numer *= other.numer;
    denom *= other.denom;

    // reduce the fraction
    reduce();
}

// purpose: To return a decimal
// value of our fraction
// arguments: None
// return value: the decimal
//               value of this fraction
double Fraction::decimal() {
    // returns the decimal value of our fraction
    return (double)numer / denom; // must cast at least one to double
}
// purpose: to divide this fraction with another fraction
// with this one with the result 
// stored in this fraction
// arguments: another fraction
// return value: none
void Fraction::divide(Fraction other) {
    other.reciprocal();
    multiply(other);

    reduce();
}
// purpose: To reduce the fraction
// arguments: None
// return value: None
void Fraction::reduce() {
    // reduce the fraction to lowest terms
    // find the greatest common divisor
    int divisor = gcd(numer,denom);

    // reduce by dividing num and denom
    // by the gcd
    numer = numer / divisor;
    denom = denom / divisor;
}

// purpose: To recursively find the greatest
// common divisor
// arguments: two integers
// return value: the gcd of the two integers
int Fraction::gcd(int u, int v) {
    if (v != 0) {
        return gcd(v,u%v);
    }
    else {
        return u;
    }
}

// purpose: To overload the << operator
// for use with cout
// arguments: a reference to an outstream and the
//            fraction we are using
// return value: a reference to the outstream
ostream& operator<<(ostream& out, const Fraction &frac) {
    out << frac.numer << "/" << frac.denom;
    return out;
}

/* Provided Tests Below This Line */

PROVIDED_TEST("Simple Example Demonstrating Existing Functionality") {
    Fraction res(1, 5);
    Fraction threeFifths(3, 5);

    res.multiply(threeFifths);
    EXPECT_EQUAL(res.decimal(), 0.12);
    Fraction f(2, 5);
    f.reciprocal();
    Fraction o(5, 2);
    EXPECT_EQUAL(f.decimal(), 2.5); 
    f.divide(o);
    EXPECT_EQUAL(f.decimal(), 1);
    Fraction res1(1, 4);
    Fraction res2(2, 1);
    res1.divide(res2);
    EXPECT_EQUAL(res1.decimal(), 0.125);
}
