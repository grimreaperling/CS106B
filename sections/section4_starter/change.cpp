/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Chase Davis for CS106B
 * Fall 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "SimpleTest.h"
#include "error.h"
#include "stack.h"
#include "set.h"
using namespace std;

/*
 * Make Chance (Code Writing)
 * --------------------------------------------------------
 * Your task is to write a function fewestCoinsFor that takes
 * as input a number of cents and a Set indicating the different
 * denominations of coins used in a country, then returns the
 * minimum number of coins required to make change for that total.
 */

int fewestCoinsFor(int cents, Set<int>& coins) {
    // TODO: Your code here
    return 0;
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: US Currency System") {
    Set<int> coins = {1, 5, 10, 25, 50};
    EXPECT_EQUAL(fewestCoinsFor(31, coins), 3);
}

PROVIDED_TEST("Provided Test: Recursia Currency System") {
    Set<int> coins = {1, 12, 14, 63};
    EXPECT_EQUAL(fewestCoinsFor(24, coins), 2);
}

