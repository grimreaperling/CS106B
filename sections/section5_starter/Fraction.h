#pragma once

#include<ostream>
using namespace std;

class Fraction {
public:
    Fraction();
    Fraction(int numer,int denom);
    void reciprocal();
    void add(const Fraction &f);
    void multiply(const Fraction &f);
    void divide(Fraction f);
    double decimal();
    int getNumer();
    int getDenom();
    friend ostream& operator<<(ostream& out, const Fraction &frac);
private:
    int numer;   // stores the numerator of the fraction
    int denom;   // stores the denominator of the fraction
    void reduce(); // simplifies fraction to reduced form (lowest terms)
    int gcd(int u, int v); // calculates and returns Greatest Common Divisor (GCD) of the two inputs
};
