/*
 * CS106B Section Handout Test Harness: Section 6
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
#include "node.h"
#include "utility.h"
#include "error.h"
#include "stack.h"
#include "set.h"
using namespace std;

void removeAllThreshold(DoubleNode*& front, double value, double threshold) {
    double low = value - threshold;
    double high = value + threshold;
    if (front->data >= low && front->data <= high) front = front->next;
    DoubleNode* cur = front;
    if (cur == nullptr) return;
    while (cur->next != nullptr) {
        double data = cur->next->data;
        if (data >= low && data <= high) {
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
        if (cur == nullptr) return;
    }
}

/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Example from handout") {
    DoubleNode *originalList = createDoubleListFromVector({ 3.0, 9.0, 4.2, 2.1, 3.3, 2.3, 3.4, 4.0, 2.9, 2.7, 3.1, 18.2});
    DoubleNode *solnList = createDoubleListFromVector({9.0, 4.2, 2.1, 2.3, 3.4, 4.0, 18.2});

    removeAllThreshold(originalList, 3.0, 0.3);
    EXPECT(doubleListEqual(originalList, solnList));
}

