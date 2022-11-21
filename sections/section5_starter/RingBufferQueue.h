/***********************************************************************
 * File: RingBufferQueue.h
 * This file defines the interface of a first-in, first-out data
 * structure called the RingBufferQueue, as defined in Section Handout
 * #4 on Classes and Objects. This data structure is implemented using
 * a dynamically-allocated array that acts a circular buffer.
 *
 * The section handout was created by Marty Stepp, Julie Zelenski, and
 * Kate Rydberg. Links to the section handout and the solution PDF are
 * available from the CS106B course website. This starter code project
 * was put together by Anand Shankar.
 */
#pragma once

#include <iostream>

class RBQueue {

public:
    // TODO: label some of these methods as
    // const where appropriate. Don't forget
    // to update the method headers in the
    // .cpp file as well! Then, delete these
    // lines.

    RBQueue();
    ~RBQueue();
    void enqueue(int elem);
    int dequeue();
    int peek();
    bool isEmpty();
    bool isFull();
    int size();

private:
    int *_elements;
    int _head;
    int _size;
    int _capacity;

    /* Note: since this is a header file, we've opted to refer to
     * ostream by its "full name" of std::ostream.
     *
     * This is the overloading of hte << operator 
     * and mark it as firend to get access to the private element of the class.
     */
    friend std::ostream& operator<<(std::ostream& out, const RBQueue& queue);
};
