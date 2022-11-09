/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* 
 * This program have the problem it add the first element blindly and don't check whether it's letter.
 */
string removeNonLetters(string s) {
    string result;
    if (isalpha(s[0])) {
        result = charToString(s[0]);
    } else {
        result = string("");
    }
    for (int i = 1; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

/*
 * This program is to encode the input string.
 */
string encode(string s) {
    string s1 = "AEIOUHWY";
    string s2 = "BFPV";
    string s3 = "CGJKQSXZ";
    string s4 = "DT";
    string s5 = "MN";
    string res = "";
    for (char c : s) {
        c = toupper(c);
        if (s1.find(c) != string::npos) res += '0';
        else if (s2.find(c) != string::npos) res += '1';
        else if (s3.find(c) != string::npos) res += '2';
        else if (s4.find(c) != string::npos) res += '3';
        else if (c == 'L') res += '4';
        else if (s5.find(c) != string::npos) res += '5';
        else res += '6';
    }
    return res;
}

/*
 * The function to coalesce the string.
 */
string coalesce(string s) {
    if (s.size() == 1) return s;
    if (s[0] == s[1]) {
        if (s.size() == 2) return s.substr(1);
        return coalesce(s.substr(1));
    } else {
        return s[0] + coalesce(s.substr(1));
    }
}

/*
 * Replace the first element with the first character.
 */
string replace(string s, char c) {
    c = toupper(c);
    return s.replace(0, 1, 1, c);
}

/*
 * Remove all the zero in the string.
 */
string removeZero(string s) {
    if (s.size() == 0) return "";
    if (s[0] == '0') {
        return removeZero(s.substr(1));
    }
    return s[0] + removeZero(s.substr(1));
}

/*
 * The function to make the length of the string exact four.
 */
string makeFour(string s) {
    if (s.size() > 4) return s.substr(0, 4);
    if (s.size() < 4) {
        int i = 4 - s.size();
        while (i > 0) {
            s += '0';
            i = i - 1;
        }
    }
    return s;
}

/* 
 * The function take in a string and return the soundex of it.
 */
string soundex(string s) {
    /* TODO: Fill in this function. */
    string res;
    res = removeNonLetters(s);
    res = encode(res);
    res = coalesce(res);
    res = replace(res, s[0]);
    res = removeZero(res);
    res = makeFour(res);
    return res;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames
    while(1) {
        string name = getLine("Enter a surname (RETURN to quit):");
        if (name == "") {
            cout << "All done!" << endl;
            return;
        }
        string code = soundex(name);
        cout << "Soundex code is " << code << endl;
        Vector<string> res;
        for (string s : databaseNames) {
            string dex = soundex(s);
            if (dex == code) res.add(s);
        }
        res.sort();
        cout << res << endl;
    }
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

STUDENT_TEST("Some special case to exposes the hidden problem of the removeNonLetters function.") {
    EXPECT_EQUAL(removeNonLetters("'Huge"), "Huge");
}

STUDENT_TEST("Test the encode function!") {
    EXPECT_EQUAL(encode("Curie"), "20600");
}

STUDENT_TEST("Test the encode function on some more cases!") {
    EXPECT_EQUAL(encode("Huge"), "0020");
}

STUDENT_TEST("Test on the coalesce function!") {
    EXPECT_EQUAL(coalesce("001100"), "010");
}

STUDENT_TEST("Test on the coalesce function on some more cases!") {
    EXPECT_EQUAL(coalesce("555555545561233"), "5456123");
    EXPECT_EQUAL(coalesce("555671"), "5671");
}

STUDENT_TEST("Test on the replace function!") {
    EXPECT_EQUAL(replace("1234", 'c'), "C234");
}

STUDENT_TEST("Test on the replace function!") {
    EXPECT_EQUAL(replace("645241234", 'c'), "C45241234");
}

STUDENT_TEST("Test on the remove function!") {
    EXPECT_EQUAL(removeZero("005671"), "5671");
}

STUDENT_TEST("Test on the remove function!") {
    EXPECT_EQUAL(removeZero("0056007100"), "5671");
}

STUDENT_TEST("Test on the makeFour function!") {
    EXPECT_EQUAL(makeFour("C92"), "C920");
    EXPECT_EQUAL(makeFour("C92231"), "C922");
}
