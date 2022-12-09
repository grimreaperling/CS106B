/*
 * CS106B Section Handout Test Harness: Section 8
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
#include <string>
#include "SimpleTest.h"
#include "error.h"
using namespace std;

/*
 * String Review (Code Writing)
 * --------------------------------------------------------
 * Write a function that reverses a string “in-place.” That is,
 * you should take the string to reverse as a reference parameter
 * and modify it so that it ends up holding its reverse. Your
 * function should use only O(1) auxiliary space.
 *
 * Then, imagine you have a string containing a bunch of words
 * from a sentence.Here’s a nifty little algorithm for reversing
 * the order of the words in the sentence: reverse each individual
 * string in the sentence, then reverse the entire resulting
 * string. (Try it – it works!) Go and code a function that
 * accomplishes this task and uses only O(1) auxiliary storage space.
 */

void reverseInPlace(string& str) {
    int time = str.size() / 2;
    int i = 0;
    while (i < time) {
       char temp = str[i];
       str[i] = str[str.size() - 1 - i];
       str[str.size() - 1 - i] = temp;
       i++;
    }
}

void reverseInPlace(string& str, int start, int end) {
    int time = (end - start + 1) / 2;
    int i = 0;
    while (i < time) {
        char temp = str[i + start];
        str[i + start] = str[end - i];
        str[end - i] = temp;
        i++;
    }
}

void reverseWordOrderingIn(string& sentence) {
    int index;
    int start = 0;
    while ((index = sentence.find(' ', start)) != string::npos) {
        reverseInPlace(sentence, start, index - 1);
        start = index + 1;
    }
    reverseInPlace(sentence, start, sentence.size() - 1);
    reverseInPlace(sentence);
}

PROVIDED_TEST("Simple Tests of Reverse String") {
    string s = "Hello, World!";
    string soln = "!dlroW ,olleH";
    reverseInPlace(s);
    EXPECT_EQUAL(s, soln);

    s = "";
    soln = "";
    reverseInPlace(s);
    EXPECT_EQUAL(s, soln);

    s = "I";
    soln = "I";
    reverseInPlace(s);
    EXPECT_EQUAL(s, soln);
}

PROVIDED_TEST("Simple Tests of Reverse Sentence") {
    string s = "Hello, World!";
    string soln = "World! Hello,";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);

    s = "Congrats on finishing CS106B";
    soln = "CS106B finishing on Congrats";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);

    s = "";
    soln = "";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);

    s = "I";
    soln = "I";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);
}
