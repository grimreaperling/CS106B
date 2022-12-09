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
#include "error.h"
using namespace std;

/*
 * Container Classes Review (Code Writing)
 * --------------------------------------------------------
 * Write a function that is given a Map<string, int> that associates
 * string values with integers and produces a Map<int, Set<string>>
 * that’s essentially the reverse mapping, associating each integer
 * value with the set of strings that map to it. (This is an old job
 * interview question from 2010.)
 *
 * Then, consider the following problem. A compound word is a word
 * that can be cut into two smaller strings, each of which is itself
 * a word. The words “keyhole” and “headhunter” are examples of
 * compound words, and less obviously so is the word “question”
 * (“quest” and “ion”). Write a function that takes in a Lexicon of
 * all the words in English and then prints out all the compound
 * words in the English language.
 */

Map<int, Set<string>> reverseMap(Map<string, int>& map) {
    Map<int, Set<string>> result;
    for (string s : map) {
        int number = map[s];
        if (!result.containsKey(number)) {
            Set<string> set;
            set.add(s);
            result.put(number, set);
        } else {
            result[number].add(s);
        }
    }
    return result;
}
bool isCompound(string word, Lexicon &dict) {
    int index = word.size() - 1;
    int i = 2;
    while (i < index) {
        if (dict.contains(word.substr(0, i))&& 
                    dict.contains(word.substr(i)))
            return true;
        i++;
    }
    return false;
}

void printCompoundWords(Lexicon &dict) {
    for (string word : dict) {
        if (isCompound(word, dict)) {
            cout << word << endl;
        }
    }
}

PROVIDED_TEST("Simple Tests for Reversing Map") {
    Map<string, int> map = {{"foo", 4}, {"bar", 4}, {"baz", 3}};
    Map<int, Set<string>> reversed = reverseMap(map);
    Map<int, Set<string>> soln = {{4, {"bar", "foo"}}, {3, {"baz"}}};

    EXPECT_EQUAL(reversed, soln);

    map = {};
    reversed = reverseMap(map);
    soln = {};
    EXPECT_EQUAL(reversed, soln);
}
/*
PROVIDED_TEST("Test for printing compound words. Must inspect console output.") {
    // Warning: The dictionary is large so this test will take a long time to run!
    // Printing out words is an expensive operation that takes a decent amount of time
    Lexicon lex("res/EnglishWords.txt");

    printCompoundWords(lex);
}
*/

