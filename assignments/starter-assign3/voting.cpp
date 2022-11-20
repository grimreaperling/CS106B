// This file contains the implementation of the power index calculation.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "hashmap.h"
#include "voting.h"
#include "testing/SimpleTest.h"
using namespace std;
/*
 * The function to get the sum of votes without the given block.
 */
Vector<int> getSums(Vector<int> blocks, int block, int gap) {
    Vector<int> res;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == block) {
            blocks.remove(i);
            break;
        }
    }
    int curr = blocks[0];
    if (blocks.size() == 1) {
        res.add(curr);
        res.add(0);
        return res;
    }
    res = getSums(blocks, curr, gap);
    for (int i = 0; i < res.size();) {
        if (res[i] > gap / 2) {
            res.remove(i);
        } else {
            i++;
        }
    }
    Vector<int> with = res;
    for (int& x : with) {
        x = x + curr;
    }
    return res + with;
}

// The main function to calculate the power index.
Vector<int> computePowerIndexes(Vector<int>& blocks)
{
    Vector<int> result;
    HashMap<int, int> map;
    int total = 0;
    int gap = 0;
    for (int block : blocks) {
        gap += block;
    }
    for (int block : blocks) {
        if (map.containsKey(block)) {
            result.add(map.get(block));
            continue;
        }
        int res = 0;
        Vector<int> sums = getSums(blocks, block, gap);
        for (int sum : sums) {
            if (sum <= gap / 2 and sum + block > gap / 2) {
               res++; 
            }
        }
        result.add(res);
        map.put(block, res);
    }
    for (int i : result) {
        total += i;
    }
    for (int& i : result) {
        i = int(float (i) / total * 100);
    }
    return result;
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test power index, blocks 50-49-1") {
    Vector<int> blocks = {50, 49, 1};
    Vector<int> expected = {60, 20, 20};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks Hempshead 1-1-3-7-9-9") {
    Vector<int> blocks = {1, 1, 3, 7, 9, 9};
    Vector<int> expected = {0, 0, 0, 33, 33, 33};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks CA-TX-NY 55-38-39") {
    Vector<int> blocks = {55, 38, 29};
    Vector<int> expected = {33, 33, 33};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks CA-TX-GA 55-38-16") {
    Vector<int> blocks = {55, 38, 16};
    Vector<int> expected = {100, 0, 0};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

//PROVIDED_TEST("Test power index, blocks EU post-Nice") {
//    // Estonia is one of those 4s!!
//    Vector<int> blocks = {29,29,29,29,27,27,14,13,12,12,12,12,12,10,10,10,7,7,7,7,7,4,4,4,4,4,3};
//    Vector<int> expected = {8, 8, 8, 8, 7, 7, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
//    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
//}

PROVIDED_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 15; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}


