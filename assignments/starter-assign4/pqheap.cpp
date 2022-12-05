#include "pqheap.h"
#include "error.h"
#include "random.h"
#include "strlib.h"
#include "datapoint.h"
#include "testing/SimpleTest.h"
using namespace std;

const int INITIAL_CAPACITY = 10;
const int NONE = -1; // used as sentinel index

/*
 * The default constructor for the PQHeap class.
 */
PQHeap::PQHeap() {
    _elements = new DataPoint[INITIAL_CAPACITY]();
    _numAllocated = INITIAL_CAPACITY;
    _numFilled = 0;
}

/*
 * The default destructor for the PQHeap class.
 */
PQHeap::~PQHeap() {
    delete[] _elements;
}

/*
 * Insert the given element into the heap.
 */
void PQHeap::enqueue(DataPoint elem) {
    if (_numFilled == _numAllocated) {
        resize();
    }
    int index = _numFilled;
    int cur;
    _elements[index] = elem;
    while ((cur = getParentIndex(index)) != NONE) {
        if (_elements[index].priority < _elements[cur].priority) {
            swap(index, cur);
            index = cur;
        } else {
            break;
        }
    }
    _numFilled++;
}

void PQHeap::swap(int index1, int index2) {
    DataPoint temp = _elements[index1];
    _elements[index1] = _elements[index2];
    _elements[index2] = temp;
}
void PQHeap::resize() {
    DataPoint *_new = new DataPoint[_numAllocated * 2]();
    for (int i = 0; i < _numFilled; i++) {
        _new[i] = _elements[i];
    }
    delete[] _elements;
    _elements = _new;
    _numAllocated *= 2;
}

/*
 * Get the foremost element of the heap.
 */
DataPoint PQHeap::peek() const {
    return _elements[0];
}

/*
 * Remove the foremost element.
 */
DataPoint PQHeap::dequeue() {
    DataPoint res = _elements[0];
    _elements[0] = _elements[_numFilled - 1];
    _numFilled--;
    int left, right;
    int index = 0;
    while ((left = getLeftChildIndex(index)) != NONE) {
        if ((right = getRightChildIndex(index)) == NONE) {
            if (_elements[left].priority < _elements[index].priority) {
                swap(left, index);
                index = left;
            } else {
                break;
            }
        } else {
            if (_elements[left].priority < _elements[index].priority 
                    && _elements[left].priority <= _elements[right].priority) {
                swap(left, index);
                index = left;
            } else if (_elements[right].priority < _elements[index].priority 
                    && _elements[right].priority <= _elements[left].priority) {
                swap(right, index);
                index = right;
            } else {
                break;
            }
        }
    }
    return res;
}

/*
 * This method return whether the heap is empty.
 */
bool PQHeap::isEmpty() const {
    return _numFilled == 0;
}

/*
 * Return the size of the heap.
 */
int PQHeap::size() const {
    return _numFilled;
}

/*
 * The method to clear up the heap.
 */
void PQHeap::clear() {
    _numFilled = 0;
}

/*
 * The helper function to print the entire heap to help 
 * debug the heap program.
 */
void PQHeap::printDebugInfo(string msg) const {
    cout << msg << endl;
    for (int i = 0; i < _numFilled; i++) {
        cout << i << " : " << _elements[i] << endl;
    }
}

/*
 * We strongly recommend implementing this helper function, which
 * should traverse the heap array and ensure that the heap property
 * holds for all elements in the array. If elements are found that
 * violate the heap property, an error should be thrown.
 */
void PQHeap::validateInternalState() const {
    int left, right;
    for (int index = 0; index < _numFilled; index++) {
        left = getLeftChildIndex(index);
        right = getRightChildIndex(index); 
        if (left != NONE) {
            if (right != NONE) {
                if (_elements[right].priority < _elements[index].priority) {
                    cout << "Error order!" << endl;
                    cout << right << " : " << _elements[right] << endl;
                    cout << index << " : " << _elements[index] << endl;
                    error("This is not a valid heap!");
                }
            } else {
                if (_elements[left].priority < _elements[index].priority) {
                    cout << "Error order!" << endl;
                    cout << left << " : " << _elements[left] << endl;
                    cout << index << " : " << _elements[index] << endl;
                    error("This is not a valid heap!");
                }
            }
        }
    }
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the parent of the
 * specified child index. If this child has no parent, return
 * the sentinel value NONE.
 */
int PQHeap::getParentIndex(int child) const {
    int parent = (child - 1) / 2;
    if (parent < 0) return NONE;
    return parent;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the left child of the
 * specified parent index. If this parent has no left child, return
 * the sentinel value NONE.
 */
int PQHeap::getLeftChildIndex(int parent) const {
    int child = parent * 2 + 1;
    if (child >= _numFilled) return NONE;
    return child;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the right child of the
 * specified parent index. If this parent has no right child, return
 * the sentinel value NONE.
 */
int PQHeap::getRightChildIndex(int parent) const {
    int child = parent * 2 + 2;
    if (child >= _numFilled) return NONE;
    return child;
}

/* * * * * * Test Cases Below This Point * * * * * */

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("PQHeap example from writeup, validate each step") {
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 4 }, { "A", 5 }, { "B", 3 }, { "K", 7 }, { "G", 2 },
        { "V", 9 }, { "T", 1 }, { "O", 8 }, { "S", 6 } };

    pq.validateInternalState();
    for (DataPoint dp : input) {
        pq.enqueue(dp);
        pq.printDebugInfo("The content of the heap: ");
        pq.validateInternalState();
    }
    while (!pq.isEmpty()) {
        pq.dequeue();
        pq.printDebugInfo("The content of the heap: ");
        pq.validateInternalState();
    }
}
