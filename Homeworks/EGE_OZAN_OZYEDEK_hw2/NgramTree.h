/*
* Title: Trees
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 2
* Description: Header file for NgramTree class. Includes definitions of functions.
*/

#ifndef NgramTree_h
#define NgramTree_h

#include "TreeNode.h"


using namespace std;
typedef void (*FunctionType)(string& ngram, int& count);

class NgramTree { //instead of writing bst here inherit

public:
    
    //constructor
    NgramTree();
    
    //copy constructor
    NgramTree(const NgramTree& copy);
    
    //destructor
    ~NgramTree();
    
    //assignment operator overload
    NgramTree& operator=(const NgramTree& rhs);
    
    
    void addNgram(string ngram);
    int getTotalNgramCount();
    void generateTree(string fileName, int n);
    
    bool isComplete();
    bool isFull();
    bool isEmpty() const;
    
    void searchTreeRetrieve(string ngram, int& count) const;
    void searchTreeInsert(const string& ngram, const int& count = 1);
    void searchTreeDelete(string ngram);
    
    void preorderTraverse(FunctionType visit);
    void inorderTraverse(FunctionType visit);
    void postorderTraverse(FunctionType visit);
    
protected:
    
    void retrieveItem(TreeNode* treePtr, string ngram, int& count) const throw(TreeException) ;
    void insertItem(TreeNode*& treePtr,const string& ngram, const int& count = 1) throw(TreeException) ;
    void deleteItem(TreeNode*& treePtr, string ngram) throw(TreeException) ;
    void deleteNodeItem(TreeNode*& nodePtr);
    void processLeftmost(TreeNode*& nodePtr, string& ngram, int& count);


    
private:
    
    TreeNode* root;
    
    void destroyTree(TreeNode*& treePtr);
    
    void preorder(TreeNode *treePtr, FunctionType visit);
    void inorder(TreeNode *treePtr, FunctionType visit);
    void postorder(TreeNode *treePtr, FunctionType visit);
    
    int ngramCounter(TreeNode *treePtr);
    void outHelper(ostream& out, TreeNode* treePtr) const;
    void copyHelper(TreeNode*& thisPtr,const TreeNode* copyPtr);
    void assignmentHelper(TreeNode*& thisPtr,const TreeNode* rhsPtr);
    
    bool fullCheck(TreeNode* treePtr);
    bool completeCheck(TreeNode* treePtr, int index, const int& ngramCount);
    
    friend ostream& operator<<( ostream& out, const NgramTree& tree);
    
    
};


#endif /* NgramTree_h */
