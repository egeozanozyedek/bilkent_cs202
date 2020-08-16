/*
* Title: Trees
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 2
* Description: TreeNode class implementation. Implements the constructors, which in default set the count to 0, and child nodes to NULL. If variable definitions are given, they are assigned.
*/


#include "TreeNode.h"

TreeNode::TreeNode(): count(0), leftChildPtr(NULL), rightChildPtr(NULL) {}

TreeNode::TreeNode(const string& nodeNgram, const int& nodeCount, TreeNode* left, TreeNode* right): ngram(nodeNgram), count(nodeCount), leftChildPtr(left), rightChildPtr(right) {}
