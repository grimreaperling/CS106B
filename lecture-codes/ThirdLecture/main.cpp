/*
 * File: main.cpp
 * --------------
 * The code file used in the lecture 5 about sets, maps
 */

#include "console.h"
#include "simpio.h"
#include "set.h"
using namespace std;


int main()
{
    Set<int> numbers = {1,2,3,4,5};
    if(numbers.contains(2)){
        cout << numbers << endl;
    }
    string name = getLine("What is your name?");
    cout << "Hello, " << name << endl;
    return 0;
}
