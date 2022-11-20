/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * The function to helpe the checkorder function.
 * which check whether all the number in the queue
 * is greater than a.
 */
void helper(int a1, Queue<int> a) {
    while (!a.isEmpty()) {
        int n = a.dequeue();
        if (n < a1) error("The queue not sorted!");
    }
}

/*
 * The function to implement the basic binaryMerge.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    Queue<int> result;
    while (!a.isEmpty() or !b.isEmpty()) {
        int a1, b1;
        if (a.isEmpty()) {
            //b1 = b.peek(); 
            result.enqueue(b.dequeue());
            //helper(b1, b);
            continue;
        }
        if (b.isEmpty()) {
            //a1 = a.peek();
            result.enqueue(a.dequeue());
            //helper(a1, a);
            continue;
        }
        a1 = a.peek();
        b1 = b.peek();
        if (b1 > a1) {
            result.enqueue(a.dequeue());
            //helper(a1, a);
        } else {
            result.enqueue(b.dequeue());
            //helper(b1, b);
        }
    }
    return result;
}

/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;
    int size = all.size();
    if (size == 1) return all.get(0);
    int k = size / 2;
    Vector<Queue<int>> vector1 = all.subList(0, k);
    Vector<Queue<int>> vector2 = all.subList(k);
    Queue<int> first = recMultiMerge(vector1);
    Queue<int> second = recMultiMerge(vector2);
    return binaryMerge(first, second);
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

//STUDENT_TEST("binaryMerge, test the unordered check") {
//    Queue<int> a = {2, 1, 3};
//    Queue<int> b = {2, 3, 4};
//    EXPECT_ERROR(binaryMerge(a, b));
//}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

STUDENT_TEST("recMultiMerge, compare to naiveMultiMerge on a range of inputs") {
    for (int n = 10; n < 100; n++) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(n);
        distribute(input, all);
        EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
    }
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

STUDENT_TEST("Time binaryMerge operation 2x") {
    int n = 2000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation x2") {
    int n = 180000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}
