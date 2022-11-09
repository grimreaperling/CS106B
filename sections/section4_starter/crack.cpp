/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Chase Davis for CS106B
 * Fall 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "SimpleTest.h"
#include "error.h"
using namespace std;

/*
 * Cracking Passwords (Code Writing)
 * --------------------------------------------------------
 * Write a function crack that takes in the maximum length a
 * site allows for a user's password and tries to find the
 * password into an account by using recursive backtracking to
 * attempt all possible passwords up to that length (inclusive).
 */

bool login(string password) {
    return (password == "cs");
}

string helper(int n, string str) {
    if (login(str)) return str;
    if (n == 0) return "";
    
    for (char i = 'a'; i <= 'z'; i++) {
        string res = helper(n - 1, str + i);
        if (res != "") return res;
        
        char c = toupper(i);
        res = helper(n - 1, str + c);
        if (res != "") return res;
    }

    return "";
}

string crackingPasswords(int n) {
    if (n == 0) return "";
	if (n < 0) error("max length cannot be negative!");
    string str = "";
    return helper(n, str);
}
//csizawesome
/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Provided Test: Example from handout.") {
    EXPECT_EQUAL(crackingPasswords(2), "cs");
}
