/*
 * This file contain a boggle game implementatin.
 * In this file we use the recursive backtracing to implement a search algorithm
 * to search for the path which in the grid board of words in the lexicon.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "backtracking.h"
#include "gridlocation.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * The function to return the point of a given word.
 */
int points(string str) {
    if (str.size() < 4) return 0;
    return str.size() - 3;
}

/*
 * This function return whether the stack contains a particular element.
 */
bool containLoc(Stack<GridLocation> path, GridLocation loc) {
    while (!path.isEmpty()) {
        if (path.pop() == loc) return true;
    }
    return false;
}

/*
 * The function return the available move of the given location.
 */
Set<GridLocation> available(Grid<char> board, GridLocation loc) {
    Set<GridLocation> locs;
    int x = loc.row;
    int y = loc.col;
    if (board.inBounds(x - 1, y - 1)) locs.add(GridLocation(x - 1, y - 1));
    if (board.inBounds(x - 1, y)) locs.add(GridLocation(x - 1, y));
    if (board.inBounds(x - 1, y + 1)) locs.add(GridLocation(x - 1, y + 1));
    if (board.inBounds(x, y - 1)) locs.add(GridLocation(x, y - 1));
    if (board.inBounds(x, y + 1)) locs.add(GridLocation(x, y + 1));
    if (board.inBounds(x + 1, y - 1)) locs.add(GridLocation(x + 1, y - 1));
    if (board.inBounds(x + 1, y)) locs.add(GridLocation(x + 1, y));
    if (board.inBounds(x + 1, y + 1)) locs.add(GridLocation(x + 1, y + 1));
    return locs;
}

/*
 * The function to judge whether a word is contained in the board.
 */
int search(Lexicon& lex, Grid<char>& board, Stack<GridLocation>& path, Set<string>& res, string& curr) {
    int result = 0;
    if (lex.contains(curr)) {
        if (!res.contains(curr)) {
            result += points(curr);
            res.add(curr);
        }
    }
    if (!lex.containsPrefix(curr)) return 0;
    GridLocation loc = path.peek();
    Set<GridLocation> locs = available(board, loc);
    for (GridLocation pos : locs) {
        if (containLoc(path, pos)) continue;
        path.push(pos);
        curr += board.get(pos);
        result += search(lex, board, path, res, curr);
        curr.pop_back();
        path.pop();
    }
    return result;
}

/*
 * The function to calculate the total score of the words 
 * which can be found in the board.
 */
int scoreBoard(Grid<char>& board, Lexicon& lex) {
    int result = 0;
    Set<string> res;
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            GridLocation loc(i, j);
            Stack<GridLocation> path;
            path.push(loc);
            string curr = "";
            curr += board[i][j];
            result += search(lex, board, path, res, curr);
        }
    }
    return result;
}

/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Load shared Lexicon, confirm number of words") {
    Lexicon lex = sharedLexicon();
    EXPECT_EQUAL(lex.size(), 127145);
}

PROVIDED_TEST("Test point scoring") {
    EXPECT_EQUAL(points("and"), 0);
    EXPECT_EQUAL(points("quad"), 1);
    EXPECT_EQUAL(points("quint"), 2);
    EXPECT_EQUAL(points("sextet"), 3);
    EXPECT_EQUAL(points("seventh"), 4);
    EXPECT_EQUAL(points("supercomputer"), 10);
}

PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
}

PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'_','A','_','_'},
                        {'_','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
}
