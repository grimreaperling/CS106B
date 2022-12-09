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
 * Sorting Review (Code Writing)
 * --------------------------------------------------------
 * Write an implementation of insertion sort that works on
 * singly-linked lists. Implement the provided function header.
 */
void insertSortedList(ListNode* node, ListNode*& res);

void listInsertionSort(ListNode*& list) { // Question to ponder: why by reference? For we need to modify the point.
    ListNode* res = nullptr;
    ListNode* cur = list;
    while (cur != nullptr) {
        ListNode* next = cur->next;  // We must do this to avoid the insertSortedList break the cur.
        insertSortedList(cur, res);
        cur = next;
    }
    list = res;
}

void insertSortedList(ListNode* node, ListNode*& res) {
    if (res == nullptr || node->data < res->data) {
        node->next = res;
        res = node;
    } else {
        ListNode* cur = res;
        ListNode* loc;
        while (cur->next != nullptr) {
            if (cur->data < node->data && 
                    cur->next->data > node->data) {
                loc = cur;
                break;
            }
            cur = cur->next;
        } if (cur->next == nullptr) {
            loc = cur;
        }
        ListNode* temp = loc->next;
        loc->next = node;
        node->next = temp;
    }
}

PROVIDED_TEST("Simple Sorting Tests") {
    Vector<int> vals = {1, 100, 10};
    ListNode *list = createListFromVector(vals);
    listInsertionSort(list);
    vals.sort();
    ListNode *soln = createListFromVector(vals);
    EXPECT(listEqual(soln, list));
    freeList(list);
    freeList(soln);

    vals = {100, 10, 1};
    list = createListFromVector(vals);
    listInsertionSort(list);
    vals.sort();
    soln = createListFromVector(vals);
    EXPECT(listEqual(soln, list));
    freeList(list);
    freeList(soln);

    vals = {1, 10, 100};
    list = createListFromVector(vals);
    listInsertionSort(list);
    vals.sort();
    soln = createListFromVector(vals);
    EXPECT(listEqual(soln, list));
    freeList(list);
    freeList(soln);

    vals = {};
    list = createListFromVector(vals);
    listInsertionSort(list);
    vals.sort();
    soln = createListFromVector(vals);
    EXPECT(listEqual(soln, list));
    freeList(list);
    freeList(soln);

    vals = {3, 9, 10, 1, 2, 7, 8, 4, 6, 5};
    list = createListFromVector(vals);
    listInsertionSort(list);
    vals.sort();
    soln = createListFromVector(vals);
    EXPECT(listEqual(soln, list));
    freeList(list);
    freeList(soln);
}

