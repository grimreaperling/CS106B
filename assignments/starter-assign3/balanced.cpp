/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/*
 * This function clean up the string and return the string
 * which contains only the tokens need to be balanced.
 */
string operatorsFrom(string str) {
    if (str.size() == 0) return "";
    char curr = str[0];
    if (curr == '(' or curr == ')' or curr == '[' or curr == ']' 
            or curr == '{' or curr == '}')
        return curr + operatorsFrom(str.substr(1));
    return operatorsFrom(str.substr(1)); 
}

/*
 * The function to judge whether the expression is balanced.
 */
bool operatorsAreMatched(string ops) {
    if (ops.size() == 0) return true;
    for (int i = 0; i < ops.size(); i++) {
        char curr = ops[i];
        if (curr == '(') {
            if (ops[i + 1] == ')')
                return operatorsAreMatched(ops.substr(0, i) + ops.substr(i + 2));
        }
        if (curr == '[') {
            if (ops[i + 1] == ']')
                return operatorsAreMatched(ops.substr(0, i) + ops.substr(i + 2));
        }
        if (curr == '{') {
            if (ops[i + 1] == '}')
                return operatorsAreMatched(ops.substr(0, i) + ops.substr(i + 2));
        }
    }
    return false;
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

STUDENT_TEST("operatorsFrom on some complex example") {
    EXPECT_EQUAL(operatorsFrom("(vecsfjow[[fwef]]}}"), "([[]]}}");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("isBalanced on some complex balanced examples") {
    EXPECT(isBalanced("int main(int argc, char** argv) { return 0; }"));
}
