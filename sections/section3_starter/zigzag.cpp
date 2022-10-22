/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "SimpleTest.h"
#include "error.h"
using namespace std;

/*
 * Zig Zag (Code Writing)
 * --------------------------------------------------------
 * Write a recursive function named zigzag​ that returns a
 * string of n characters as follows. The middle character
 * (or middle two characters if ​n​ is even) is an asterisk (\*).
 * All characters before the asterisks are ​'<'​. All characters
 * after are ​'>'​. Report an error if ​n​ is not positive.
 */

string zigzag(int n) {
    // TODO: Your code here
    return "";
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Examples from handout.") {
    EXPECT_EQUAL(zigzag(1), "*");
    EXPECT_EQUAL(zigzag(4), "<**>");
    EXPECT_EQUAL(zigzag(9), "<<<<*>>>>");
}

PROVIDED_TEST("Provided Test: Raise error when input is negative") {
    EXPECT_ERROR(zigzag(-3));
}

