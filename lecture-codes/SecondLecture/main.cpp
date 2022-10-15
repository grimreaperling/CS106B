/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "linkedlist.h"
#include "stack.h"
#include "queue.h"
using namespace std;


int main()
{
    Queue<int> q = {1,2,3};
    Stack<int> s = {1,2,3};
    s.push(2);
    q.dequeue();
    Vector<int> row1 = {1,2,3};
    Vector<int> row2 = {1,2,3,4};
    Vector<int> row3 = {1,2,3,4,5};
    Vector<Vector<int> > vv;
    LinkedList<int> list1 = {1,2,3,4};
    list1.add(2);
    vv.add(row1);
    vv.add(row2);
    vv.add(row3);
    string name = getLine("What is your name?");
    cout << "Hello, " << name << endl;
    cout << vv << endl;
    cout << list1 << endl;
    cout << s << endl;
    return 0;
}
