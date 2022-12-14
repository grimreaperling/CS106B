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

/*
 * Braiding a Linked List (Code Writing)
 * --------------------------------------------------------
 * Write a function braid that takes a linked list, and weaves
 * the reverse of that list into the original. (In this case,
 * you will need to create new nodes.)
 */
Node* reverse(Node* front);

void braid(Node*& front) {
    Node *rev = nullptr;
    for (Node *curr = front; curr != nullptr; curr = curr->next) {
        Node *newNode = new Node{curr->data, nullptr};
        newNode->next = rev; 
        rev = newNode;
    }
    /*
    // reverse now addresses a memory-independent copy of the original list,
    // where all of the nodes are in reverse order.
    for (Node *curr = front; curr != nullptr; curr = curr->next->next) {
        Node *next = reverse->next;
        reverse->next = curr->next;
        curr->next = reverse;
        reverse = next;
    }
    */
    Node* cur = front;
    //Node* rev = reverse(front); 
    while (rev != nullptr) {
        Node* temp = cur->next;
        cur->next = rev;
        rev = rev->next;
        cur = cur->next;
        cur->next = temp;
        cur = cur->next;
    }
}
/*
Node* reverse(Node* front) {
    if (front == nullptr) return nullptr;
    int data = front->data;
    Node* prev = reverse(front->next);
    Node* res = prev;
    if (res == nullptr) {
        res = new Node({data, nullptr});
        return res;
    }
    while (prev->next) prev = prev->next;
    prev->next = new Node({data, nullptr});
    return res;
}
*/

/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("First example from handout") {
    Node *originalList = createListFromVector({1, 4, 2});
    Node *braidedList = createListFromVector({1, 2, 4, 4, 2, 1});

    braid(originalList);

    EXPECT(listEqual(originalList, braidedList));
}

PROVIDED_TEST("Second example from handout") {
    Node *originalList = createListFromVector({3});
    Node *braidedList = createListFromVector({3, 3});

    braid(originalList);

    EXPECT(listEqual(originalList, braidedList));
}

PROVIDED_TEST("Third example from handout") {
    Node *originalList = createListFromVector({1, 3, 6, 10, 15});
    Node *braidedList = createListFromVector({1, 15, 3, 10, 6, 6, 10, 3, 15, 1});

    braid(originalList);

    EXPECT(listEqual(originalList, braidedList));
}
