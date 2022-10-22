/*
 * CS106B Section Handout Test Harness: Section 1
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
#include <fstream>
#include "grid.h"
#include "filelib.h"
#include "SimpleTest.h"
using std::endl;     using std::cout;
using std::ifstream; using std::string;
/*
 * Sum Numbers (Code Write)
 * ----------------------------------
 * Write a program to read through a given file and sum
 * all of the numbers in the file. You can assume that numbers
 * will be composed entirely of numerical digits, optionally
 * preceded by a single negative sign.
 */
bool isNumber(string s) {
    if (s.size() > 0 and s[0] == '-') {
        s = s.substr(1);
    }
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int sumNumbers(string filename) {
    int result = 0;
    ifstream ifs;
    if (!openFile(ifs, filename)) {
        cout << "Cannot open the file!" << endl;
        return 0;
    }
    Vector<string> sentences;
    readEntireFile(ifs, sentences);
    for (string sentence : sentences) {
        Vector<string> words;
        words = stringSplit(sentence, " "); 
        for (string word : words) {
            if (isNumber(word)) {
                result += stringToInteger(word);
            }
        }
    }
    return result;
}


/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("given file in handout") {
    EXPECT_EQUAL(sumNumbers("res/numbers.txt"), 42);
}

PROVIDED_TEST("Nonexistent file should sum to zero") {
    EXPECT_EQUAL(sumNumbers("nonexistent_filename"), 0);
}

