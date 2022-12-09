#pragma once

#include <climits>
#include "treenode.h"
#include "vector.h"
#include "listnode.h"

#define EMPTY INT_MAX

TreeNode* createTreeFromVector(Vector<int> nums);
void freeTree(TreeNode* root);
bool treeEqual(TreeNode* a, TreeNode *b);
void printTree(TreeNode *root);

ListNode* createListFromVector(Vector<int> nums);
void freeList(ListNode* list);
bool listEqual(ListNode* a, ListNode *b);
void printList(ListNode *list);
