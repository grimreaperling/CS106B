#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

void partition(ListNode*& front, ListNode*& less, ListNode*& equal, ListNode*& greater);
void concatenate(ListNode*& front, ListNode*& less, ListNode*&equal, ListNode*& greater);
/*
 * The method to implement the quick sort algorithm on the link list.
 */
void quickSort(ListNode*& front) {
    if (front == nullptr) return;
    if (front->next == nullptr) return;
    ListNode* less=nullptr, *equal=nullptr, *greater=nullptr;
    partition(front, less, equal, greater);
    quickSort(less);
    quickSort(greater);
    concatenate(front, less, equal, greater);
}

void partition(ListNode*& front, ListNode*& less, ListNode*& equal, ListNode*& greater) {
    if (front == nullptr) return; 
    int pivot = front->data;

    equal = front;
    front = front->next;
    equal->next = nullptr;

    ListNode *curr1, *curr2, *curr3;
    curr3 = equal;

    while (front != nullptr) {
        int data = front->data;
        ListNode* cur = front;
        front = front->next;
        if (data > pivot) {
            if (greater == nullptr) {
                greater = cur;
                greater->next = nullptr;
                curr1 = greater;
            } else {
                curr1->next = cur;
                curr1->next->next = nullptr;
                curr1 = curr1->next;
            }
        } else if (data < pivot) {
            if (less == nullptr) {
                less = cur;
                less->next = nullptr;
                curr2 = less;
            } else {
                curr2->next = cur;
                curr2->next->next = nullptr;
                curr2 = curr2->next;
            }
        } else {
                curr3->next = cur;
                curr3->next->next = nullptr;
                curr3 = curr3->next;
        }
    }
}

void concatenate(ListNode*& front, ListNode*& less, ListNode*&equal, ListNode*& greater) {
    ListNode* cur = front;
    if (less != nullptr) {
        cur = less;
        front = less;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
    }
    if (equal != nullptr) {
        if (cur != nullptr) {
            cur->next = equal;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
        } else {
            cur = equal;
            front = equal;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
        }
    }
    if (greater != nullptr) {
        if (cur != nullptr) {
            cur->next = greater;
        } else {
            front = greater;
        }
    }
}

/* * * * * * Test Code Below This Point * * * * * */

/*
 * We have provided this utility function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
   cout << "{";
   for (ListNode *cur = front; cur != nullptr; cur = cur->next) {
       cout << cur->data;
       if (cur->next != nullptr){
           cout << ", ";
       }
   }
   cout << "}" << endl;
}

/*
 * This utility function deallocates the memory for all the nodes in a
 * given linked list. It can be used to recycle the memory allocated
 * during a test case and avoid memory leaks.
 */
void deallocateList(ListNode* front) {
//    if (front == nullptr) return;
//    deallocateList(front->next);
//    delete front;
    ListNode* cur = front;
    if (cur == nullptr) return;
    while (cur->next != nullptr) {
        cur = cur->next;
        delete front;
        front = cur;
    }
    delete cur;
}

/*
 * This utility function is given a vector of values and constructs
 * an equivalent linked list containing the same values in the same order.
 * It can be used to construct a linked list to use as an input to
 * a function being tested.
 */
ListNode* createList(Vector<int> values){
//    if (values.size() == 0) return nullptr;
//    int value = values[0];
//    values.remove(0);
//    ListNode *res = new ListNode(value, createList(values));
//    return res;
    if (values.size() == 0) return nullptr;
    ListNode* res = new ListNode(values[0], nullptr);
    ListNode* cur = res;
    for (int i = 1; i < values.size(); i++) {
        ListNode* node = new ListNode(values[i], nullptr);
        cur->next = node;
        cur = cur->next;
    }
    return res;
}

/*
 * This utility function compares a linked list and a vector for
 * equivalence and returns true if both contain the same values in the
 * same order. It can be used to confirm a linked list's contents match
 * the expected.
 */
bool areEquivalent(ListNode* front, Vector<int> v){
//    if (v.size() == 0 && front == nullptr) return true;
//    else if (v.size() == 0 || front == nullptr) return false;
//    int value1 = front->data;
//    int value2 = v[0];
//    if (value1 == value2) {
//        return areEquivalent(front->next, v.subList(1, v.size() - 1));
//    }
//    return false;
    int i = 0;
    while (front != nullptr && i < v.size()) {
        if (front->data != v[i]) return false;
        front = front->next;
        i++;
    }
    if (front == nullptr && i == v.size()) return true;
    return false;
}

STUDENT_TEST("Test on the partition function") {
    Vector<int> values = {3, 2, 5, 1, 7};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);
    ListNode *less=nullptr, *equal=nullptr, *greater=nullptr;
    partition(list, less, equal, greater);
    EXPECT(areEquivalent(less, {2, 1}));
    EXPECT(areEquivalent(equal, {3}));
    EXPECT(areEquivalent(greater, {5, 7}));
    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Some more test on the partition function") {
    ListNode* list = createList({1, 2, 3, 4});
    ListNode *less=nullptr, *equal=nullptr, *greater=nullptr;
    partition(list, less, equal, greater);
    EXPECT(areEquivalent(less, {}));
    EXPECT(areEquivalent(equal, {1}));
    EXPECT(areEquivalent(greater, {2, 3, 4}));

    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Some more test on the partition function for some strange cases") {
    ListNode* list = createList({5, 5, 4, 2});
    ListNode *less=nullptr, *equal=nullptr, *greater=nullptr;
    partition(list, less, equal, greater);
    EXPECT(areEquivalent(less, {4, 2}));
    printList(equal);
    EXPECT(areEquivalent(equal, {5, 5}));
    EXPECT(areEquivalent(greater, {}));

    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Test on the concatenate function") {
   ListNode *front = nullptr;
   ListNode *less = createList({1, 2});
   ListNode *equal = createList({3});
   ListNode *greater = createList({4, 5});
   concatenate(front, less, equal, greater);
   EXPECT(areEquivalent(front, {1, 2, 3, 4, 5}));
   deallocateList(front);
}

STUDENT_TEST("Test on concatenate function for some strange input!") {
   ListNode *front = nullptr;
   ListNode *less = createList({});
   ListNode *equal = createList({3});
   ListNode *greater = createList({4, 5});
   concatenate(front, less, equal, greater);
   EXPECT(areEquivalent(front, {3, 4, 5}));
   deallocateList(front);
}

STUDENT_TEST("Test on concatenate function for some strange input!") {
   ListNode *front = nullptr;
   ListNode *less = createList({});
   ListNode *equal = createList({});
   ListNode *greater = createList({4, 5});
   concatenate(front, less, equal, greater);
   EXPECT(areEquivalent(front, {4, 5}));
   deallocateList(front);
}

STUDENT_TEST("This is a skeleton to demonstrate an end-to-end student test."){
    /* Initialize vector to sequence of values */
    Vector<int> values = {1, 1, 1, 1};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    printList(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

STUDENT_TEST("The simple test on the quick sort algorithm"){
    /* Initialize vector to sequence of values */
    Vector<int> values = {4, 9, 6, 1};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    printList(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

STUDENT_TEST("Test the sort on some complex examples."){
    /* Initialize vector to sequence of values */
    Vector<int> values = {5, 5, 3, 2, 4, 5, 6, 1, 6};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    printList(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

STUDENT_TEST("Test the sort on some strange examples."){
    /* Initialize vector to sequence of values */
    Vector<int> values = {5, 5, 3, 2, 4, 5, 6, 1, 6, 9, 7, 3, 1, 6, 5, 4};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    printList(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
    /* Creates a small test list containing the values 1->2->3. */
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(areEquivalent(testList, {1, 2, 3}));
    EXPECT(!areEquivalent(testList, {1, 2}));
    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
    EXPECT(!areEquivalent(testList, {1, 3, 2}));

    /* Test create list function. */
    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }

    /* Test deallocate list functions. There should be no memory leaks from this test. */
    deallocateList(studentList);
    deallocateList(testList);
}

/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        /* Create linked list and vector with the same random sequence. */
        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to compare relative speed. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}

