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
#include "vector.h"
using namespace std;

/*
 * Linked List Warmup (Code Writing)
 * --------------------------------------------------------
 * Write a function that adds up the values of all the elements
 * in the linked list. Next, write a function that returns a
 * pointer to the last element of a linked list (and reports an
 * error if the list is empty).
 */

int sumOfElementsIn(Node* list) {
//    int sum = 0;
//    while (list != NULL) {
//        sum += list->data;
//        list = list->next;  
//    }
    if (list == NULL) return 0;
    else return list->data + sumOfElementsIn(list->next);
}

Node* lastElementOf(Node* list) {
//    Node* cur = list;
//    if (cur == nullptr) error("The list is empty!");
//    while (cur->next != NULL) {
//       cur = cur->next;
//    }
    if (list == NULL) error("The list is empty!");
    if (list->next == NULL) return list;
    return lastElementOf(list->next);
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Basic Sum Example") {
    Node *list = createListFromVector({1, 2, 3, 4, 5});
    EXPECT_EQUAL(sumOfElementsIn(list), 15);
    freeList(list);
}

PROVIDED_TEST("Basic Find Last Example") {
    Node *list = createListFromVector({1,2,3});
    EXPECT_EQUAL(lastElementOf(list), list->next->next);
    freeList(list);
}


