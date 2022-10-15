#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
using namespace std;

int main() {
    ifstream input;
    input.open("streamErrors-data.txt");

    string name;
    name = input.getline();      // #1   "Donald Knuth"
    cout << name << endl;

    char gender;
    gender = input.get();        // #2   'M'
    cout << gender << endl;

    int age;
    getline(input, age);
    stringToInteger(age);        // #3   76
    cout << age << endl;

    string jobtitle;
    input >> jobtitle;           // #4   "Stanford U."
    cout << jobtitle << endl;

    return 0;
}
