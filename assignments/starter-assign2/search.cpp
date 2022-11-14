// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
#include "testing/SimpleTest.h"
using namespace std;


// Clean up the token by trim the punctuation and convert the token into the lowercase.
string cleanToken(string s)
{
    while (ispunct(s[0])) s = s.substr(1);
    while (ispunct(s.back())) s.pop_back(); bool flag = false;
    for (char c : s) {
        if(isalpha(c)) flag = true;
    }
    if (!flag) return "";
    s = toLowerCase(s);
    return s;
}

// Gather the unique tokens by parsing the given text.
Set<string> gatherTokens(string text)
{
    Set<string> tokens;
    Vector<string> words = stringSplit(text, " ");
    for (string s : words) {
        s = cleanToken(s);
        if(s != "") tokens.add(s);
    }
    return tokens;
}

// Read in the dbfile and than read in and save into a map.
int buildIndex(string dbfile, Map<string, Set<string>>& index)
{
    ifstream in;
    
    if (!openFile(in, dbfile)) 
        error("Cannot open file named " + dbfile);

    Vector<string> lines;
    readEntireFile(in, lines);
    int size = lines.size();
    int i = 0;
    int count = 0;

    while (i < size) {
        string url = lines[i];
        string text = lines[i+1];
        Set<string> tokens = gatherTokens(text);
        for (string token : tokens) {
            if (!index.containsKey(token)) {
                Set<string> entrys;
                entrys.add(url);
                index.put(token, entrys);
            } else {
                index[token].add(url);
            }
        }
        i = i + 2;
        count++;
    }
    return count;
}

// Get a set of urls use the given terms.
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;
    Vector<string> terms = stringSplit(query, " ");
    string term = cleanToken(terms[0]);
    result = index[term];
    if (terms.size() == 1) return result;
    int i = 1;
    while (i < terms.size()) {
        string s = terms[i];
        if (s[0] == '+') {
            s = s.substr(1);
            s = cleanToken(s);
            Set<string> next = index[s];
            result.intersect(next);
        } else if (s[0] == '-') {
            s = s.substr(1);
            s = cleanToken(s);
            Set<string> next = index[s];
            result.difference(next);
        } else {
            s = cleanToken(s);
            Set<string> next = index[s];
            result.unionWith(next);
        }
        i++;
    }
    return result;
}

// The function to offer the service build by rest functions to the user.
void searchEngine(string dbfile)
{
    Map<string, Set<string>> index;
    cout << "Stand by while building index..." << endl;
    int nPages = buildIndex(dbfile, index);
    int size = index.size();
    cout << "Indexed " << nPages << "Pages containing " << size << " unique terms" << endl;
    while (1) {
        string query = getLine("Enter query sentence (RETURN/ENTER to quit):");
        if (query == "") {
            cout << "All done!" << endl;
            return;
        }
        Set<string> res = findQueryMatches(index, query);
        cout << "Found " << res.size() << " matching pages" << endl;
        cout << res << endl;
    }
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}

PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

STUDENT_TEST("Test not to touch the inner punctuation") {
    EXPECT_EQUAL(cleanToken("he//llo"), "he//llo");
    EXPECT_EQUAL(cleanToken("/he//llo/"), "he//llo");
}

STUDENT_TEST("Some more test") {
    EXPECT_EQUAL(cleanToken("**"), "");
    EXPECT_EQUAL(cleanToken("*Red*"), "red");
    EXPECT_EQUAL(cleanToken("10"), "");
    EXPECT_EQUAL(cleanToken("Fish?"), "fish");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here
