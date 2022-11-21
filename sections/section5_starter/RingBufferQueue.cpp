#include "RingBufferQueue.h"
#include "SimpleTest.h"

const int defaultCapacity = 10;

using namespace std;
/**
 * This is the default constructor for the RBQ datastrcutrue.
 */
RBQueue::RBQueue() {
    _capacity = defaultCapacity;
    _elements = new int[_capacity];
    _head = 0;
    _size = 0;
}

/**
 * The default destructor for the queue class.
 */
RBQueue::~RBQueue() {
    delete[] _elements;
}

/**
 * The method to add a given element into the queue.
 */
void RBQueue::enqueue(int elem) {
    int loc = _head + _size;
    if (loc + 1 > _capacity) {
        if (loc - _capacity < _head) {
            loc = loc - _capacity;
        } else {
            error("The queue is full!");
        }
    }
    _elements[loc] = elem;
    _size++;
}

/**
 * The function to remove last element.
 */
int RBQueue::dequeue() {
    if (_size < 1) error("The queue is empty!");
    _size -= 1;
    int res = _elements[_head];
    _head++;
    if (_head > _capacity - 1) _head = _head - _capacity; 
    return res;
}

/**
 * Return the first element of the string.
 */
int RBQueue::peek() {
    if (_size < 1) error("The queue is empty!");
    return _elements[_head];
}

/**
 * Return whether the queue is empty.
 */
bool RBQueue::isEmpty() {
    if (_size == 0) return true;
    return false;
}

/**
 * Return whether the queue is full.
 */
bool RBQueue::isFull() {
    if (_size == _capacity) return true;
    return false;
}

/**
 * Return the size of the queue.
 */
int RBQueue::size() {
    return _size;
}

/**
 * Overload the << operator to output the queue.
 */
ostream& operator<<(ostream& out, const RBQueue& queue) {
    // The following lines are just here to
    // disable compiler warnings and errors.
    // Delete these lines, then implement
    // this method.
    for (int i = 0; i < queue._size; i++) {
        int loc = i + queue._head;
        if (i > queue._capacity - 1)  loc = i - queue._capacity;
        out << queue._elements[loc];
    }
    return out;
}

/* Provided Tests Below This Line */

PROVIDED_TEST("Simple Example From Handout") {
    RBQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQUAL(q.peek(), 1);
    q.enqueue(4);
    q.enqueue(5);
    EXPECT(!q.isFull());
    cout << q << endl;
    EXPECT_EQUAL(q.dequeue(), 1);
    EXPECT_EQUAL(q.dequeue(), 2);
    EXPECT_EQUAL(q.peek(), 3);
    q.enqueue(6);
    cout << q << endl;
    EXPECT_EQUAL(q.dequeue(), 3);
    EXPECT_EQUAL(q.dequeue(), 4);
    EXPECT_EQUAL(q.dequeue(), 5);
    EXPECT_EQUAL(q.dequeue(), 6);
    EXPECT(q.isEmpty());
}
