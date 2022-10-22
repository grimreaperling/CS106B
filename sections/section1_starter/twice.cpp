/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "set.h"
#include "vector.h"
#include "SimpleTest.h"
using namespace std;

/*
 * Twice (Code Write)
 * ----------------------------------
 * Write a function named twice that takes a vector of integers
 * and returns a set containing all the numbers in the vector
 * that appear exactly twice.
 */

Set<int> twice(Vector<int> nums) {
    Set<int> set1;
    Set<int> set2;
    int size = nums.size();
    for (int i = 0; i < size; ) {
        if (!set1.contains(nums[i])) {
            set1.add(nums[i]);
            nums.remove(i);
            size--;
        } else {
            i++;
        }
    }
    for (int i = 0; i < size; ) {
        if (!set2.contains(nums[i])) {
            set2.add(nums[i]);
            nums.remove(i);
            size--;
        } else {
            i++;
        }
    }
    set1 = set1.intersect(set2);
    for (int num : nums) {
        set1.remove(num);
    }
    return set1;
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("test case from handout") {
    Vector<int> v = {1, 3, 1, 4, 3, 7, -2, 0, 7, -2, -2, 1};
    Set<int> soln = {3, 7};
    EXPECT_EQUAL(twice(v), soln);
}
