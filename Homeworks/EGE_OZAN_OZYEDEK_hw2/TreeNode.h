/*
* Title: Trees
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 2
* Description: Header file for TreeNode class. Includes definitions of constructors. The TreeNode class contains two children pointers, the string ngram and the int count. This class is used in NgramTree.
*/

#ifndef TreeNode_h
#define TreeNode_h

#include "TreeException.h"


class TreeNode {
private:
    
    friend class NgramTree;
    string ngram;
    int count;
    TreeNode *leftChildPtr;
    TreeNode *rightChildPtr;
    
    
    TreeNode();
    TreeNode(const string& nodeNgram, const int& nodeCount = 0, TreeNode* left = NULL, TreeNode* right = NULL);
    
    friend class BinarySearchTree;
};


#endif /* TreeNode_h */
