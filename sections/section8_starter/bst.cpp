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
#include "error.h"
using namespace std;
extern bool isLeaf(TreeNode* root);
/*
 * Validating a Binary Search Tree (Code Writing)
 * --------------------------------------------------------
 * Your task is to write a function isBST that accepts a pointer to 
 * the root of a tree and then determines whether or not that tree
 * satisfies the binary search tree properties. You can assume that what 
 * you’re getting as input is actually a tree, so, for example, you won’t 
 * have a node that has multiple pointers into it, no node will point at itself, 
 * etc.
 */
int min(TreeNode* root);
int max(TreeNode* root);
bool isBST(TreeNode* root) {
    if (root == nullptr) return true;
    if (isLeaf(root)) return true;
    if (!(isBST(root->left) && isBST(root->right))) return false;
    if (root->left != nullptr && root->right != nullptr) {
        if (min(root->right) < root->data || max(root->left) > root->data) return false;
    } else if (root->left != nullptr) {
        if (max(root->left) > root->data) return false;
    } else {
        if (min(root->right) < root->data) return false;
    }
    return true;
}

int max(TreeNode* root) {
    while (root->right != nullptr) root = root->right;
    return root->data;
}
int min(TreeNode* root) {
    while (root->left != nullptr) root = root->left;
    return root->data;
}

PROVIDED_TEST("Simple positive tests for isBST function") {
    TreeNode *tree = nullptr;
    EXPECT(isBST(tree));

    tree = createTreeFromVector({/* Level 1*/ 5});
    EXPECT(isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 3, EMPTY});
    EXPECT(isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ EMPTY, 6});
    EXPECT(isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 3, 6});
    EXPECT(isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 3, 6, /* Level 3*/ 1, 4, EMPTY, EMPTY});
    EXPECT(isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 3, 6, /* Level 3*/ 1, 4, EMPTY, 9});
    EXPECT(isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 3, 6, /* Level 3*/ 1, 4, EMPTY, 9, /* Level 4*/ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, EMPTY});
    EXPECT(isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 3, 6, /* Level 3*/ 1, 4, EMPTY, 9, /* Level 4*/ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, 10});
    EXPECT(isBST(tree));

    freeTree(tree);
}

PROVIDED_TEST("Simple negative tests for isBST function") {
    TreeNode *tree = createTreeFromVector({5, 6});
    EXPECT(!isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 4, 3});
    EXPECT(!isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 4, 6, /* Level 3*/ 1, 7, EMPTY, EMPTY});
    EXPECT(!isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 4, 6, /* Level 3*/ 7, 1, EMPTY, EMPTY});
    EXPECT(!isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 4, 6, /* Level 3*/ 1, EMPTY, 8, 9});
    EXPECT(!isBST(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 4, 6, /* Level 3*/ 1, EMPTY, EMPTY, 9, /* Level 4*/ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 1, 10});
    EXPECT(!isBST(tree));

    freeTree(tree);
}

