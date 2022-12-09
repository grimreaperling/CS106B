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
#include "SimpleTest.h"
#include "lexicon.h"
#include "set.h"
using namespace std;

/*
 * Recursive Enumeration and Backtracking Review (Code Writing)
 * --------------------------------------------------------
 * Given a positive integer n, write a function that finds
 * all ways of writing n as a sum of nonzero natural numbers.
 *
 * Next, write a function that, given a set of strings and a number
 * k, lists all ways of choosing k elements from that list, given
 * that order does matter.
 *
 * Finally, revisit one of the problems from earlier in this project.
 * In particular, one of the problems from the "Container Classes"
 * section discussed compound words, which are words that can be
 * cut into two smaller pieces, each of which is a word. You can
 * generalize this idea further if you allow the word to be chopped
 * into even more pieces. Write a function that takes in a word and
 * returns whether it can be split apart into two or more smaller
 * pieces, each of which is itself an English word.
 */

/* Prints a Vector<int> nicely as a sum.
 * You may find this provided helper function useful for printSumsOf.
 */
void printAsSum(Vector<int>& sum) {
    /* The empty sum prints as zero. */
    if (sum.isEmpty()) {
        cout << 0 << endl;
    } else {
        /* Print out each term, with plus signs interspersed. */
        for (int i = 0; i < sum.size(); i++) {
            cout << sum[i];
            if (i + 1 != sum.size()) cout << " + ";
        }
        cout << endl;
    }
}
void helperPrint(int n, Vector<int>& cur) {
    if (n == 0) printAsSum(cur);
    else {
        for (int i = 1; i <= n; i++) {
            cur.add(i);
            helperPrint(n-i, cur);
            cur.remove(cur.size() - 1);
        }
    }
}

void printSumsOf(int n) {
    Vector<int> cur;
    helperPrint(n, cur);
}
void helperList(Vector<string> cur, Set<string> choices, int k) {
    if (k == 0) {
        cout << cur << endl;
    } else {
        for (string s : choices) {
            Set<string> set = choices;
            set.remove(s);
            cur.add(s);
            helperList(cur, set, k - 1);
            cur.remove(cur.size() - 1);
        }
    }
}
void listKOrderings(Set<string> choices, int k) {
    Vector<string> cur;
    helperList(cur, choices, k);
}

bool isMultCompound(string word, Lexicon& dict) {
    if (dict.contains(word)) return true;
    bool res = false;
    int index = word.size() - 1;
    int i = 2;
    while (i < index) {
        if (dict.contains(word.substr(0, i))) {
            if (isMultCompound(word.substr(i), dict)) {
                res = true;
            }
        }
        i++;
    }
    return res;
}

bool compound(string word, Lexicon& dict) {
    int index = word.size() - 1;
    int i = 2;
    while (i < index) {
        if (dict.contains(word.substr(0, i))&& 
                    isMultCompound(word.substr(i), dict))
            return true;
        i++;
    }
    return false;
}

void printMultCompoundWords(Lexicon& dict) {
    for (string word : dict) {
        if (compound(word, dict)) {
            cout << word << endl;
        }
    }
}

PROVIDED_TEST("Handout example for printSumsOf, must inspect console for output.") {
    printSumsOf(3);
}

PROVIDED_TEST("Handout example for listKOrderings, must inspect console for output.") {
    listKOrderings({"A", "B", "C"}, 2);
}

/*
PROVIDED_TEST("Test for printing multi=compound words. Must inspect console output.") {
    // Warning: The dictionary is large so this test will take a long time to run!
    // Printing out words is an expensive operation that takes a decent amount of time
    Lexicon lex("res/EnglishWords.txt");

    printMultCompoundWords(lex);
}
*/


