/*
 * CS106B Section Handout Test Harness: Section 8
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
#include "SimpleTest.h"
#include "listnode.h"
#include "utility.h"
#include "vector.h"
using namespace std;

/*
 * Kth-To-Last (Code Writing)
 * --------------------------------------------------------
 * Write a function that, given a pointer to a singly-linked
 * list and a number k, returns the kth-to last element of
 * the linked list (or a null pointer if no such element
 * exists). As a challenge, see if you can solve this in
 * O(n) time with only O(1) auxiliary storage space.
 */

ListNode* kthToLast(ListNode* list, int k) {
    ListNode* cur = list;
    int size = 0;
    while (cur != nullptr) {
        cur = cur->next;
        size++; 
    }
    int depth = size - k;
    ListNode* res = list;
    if (depth < 0) return nullptr;
    while (depth > 0) {
        res = res->next;
        depth--;
    }
    return res;
}

PROVIDED_TEST("Simple test cases for kthToLast function") {
    ListNode *input = createListFromVector({1, 2, 3, 4, 5});
    EXPECT_EQUAL(kthToLast(input, 1), input->next->next->next->next);
    EXPECT_EQUAL(kthToLast(input, 2), input->next->next->next);
    EXPECT_EQUAL(kthToLast(input, 3), input->next->next);
    EXPECT_EQUAL(kthToLast(input, 4), input->next);
    EXPECT_EQUAL(kthToLast(input, 5), input);
    EXPECT_EQUAL(kthToLast(input, 6), nullptr);
}
