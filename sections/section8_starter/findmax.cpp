/*
 * CS106B Section Handout Test Harness: Section 7
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
#include "treenode.h"
#include "utility.h"
#include "vector.h"
using namespace std;
bool isLeaf(TreeNode* node);
/*
 * Ultimate and Penultimate Values (Code Writing)
 * --------------------------------------------------------
 * Write a function that takes as input a pointer to the root
 * of a (nonempty) binary search tree, then returns a pointer
 * to the node containing the largest value in the BST. Then,
 * write a function that takes as input a pointer to the root
 * of a BST containing at least two nodes, then returns a
 * pointer to the node containing the second-largest value
 * in the BST.
 */

TreeNode* biggestNodeIn(TreeNode* root) {
    /*
    int max = root->data;
    if (isLeaf(root)) return root;
    if (root->left != nullptr && root->right != nullptr) {
        int res1 = biggestNodeIn(root->left)->data;
        int res2 = biggestNodeIn(root->right)->data;
        if (res1 > res2 && res1 >= max) return biggestNodeIn(root->left);
        if (res2 >= res1 && res2 >= max) return biggestNodeIn(root->right);
        return root;
    } else if (root->left != nullptr) {
        int res = biggestNodeIn(root->left)->data;
        if (res > max) return biggestNodeIn(root->left);
        return root;
    } else {
        int res = biggestNodeIn(root->right)->data;
        if (res > max) return biggestNodeIn(root->right);
        return root;
    }
    */
    while (root->right != nullptr) root = root->right;
    return root;
}

TreeNode* secondBiggestNodeIn(TreeNode* root) {
    if (root->right == nullptr) return root->left;
    TreeNode* cur = root;
    while (cur->right->right != nullptr) cur = cur->right;
    if (cur->right->left != nullptr) return cur->right->left;
    return cur;
}

PROVIDED_TEST("Simple tests for biggestNodeIn function") {
    TreeNode *tree = createTreeFromVector({/* Level 1 */ 5});
    EXPECT_EQUAL(tree, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6});

    EXPECT_EQUAL(tree->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, EMPTY});
    EXPECT_EQUAL(tree->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9});
    EXPECT_EQUAL(tree->right->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9, /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, EMPTY});
    EXPECT_EQUAL(tree->right->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9, /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, 10});
    EXPECT_EQUAL(tree->right->right->right, biggestNodeIn(tree));

    freeTree(tree);
}

PROVIDED_TEST("Simple tests for secondBiggestNodeIn function") {
    TreeNode *tree = createTreeFromVector({/* Level 1 */ 5, 3, EMPTY});
    EXPECT_EQUAL(tree->left, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6});
    EXPECT_EQUAL(tree, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, EMPTY});
    EXPECT_EQUAL(tree, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9});
    EXPECT_EQUAL(tree->right, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9, /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, EMPTY});
    EXPECT_EQUAL(tree->right->right->left, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9, /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, 10});
    EXPECT_EQUAL(tree->right->right, secondBiggestNodeIn(tree));

    freeTree(tree);
}
