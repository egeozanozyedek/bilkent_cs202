/*
* Title: Trees
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 2
* Description: implementations for the NgramTree functions. NgramTree creates a tree with a given string that contains n-grams. The user can add ngrams, which either adds a new node or increments the node if it exists. The completeness or fullness of the tree can also be checked. The NgramTree class also contains other standart BST methods for insetion, deletion and retrieval.
*/

#include "NgramTree.h"

//------------------------------------------------------------
// Constructor, Copy Construtor, Destructor and Assignment
//------------------------------------------------------------


/*
 constructor, initializes the root as NULL
 */
NgramTree::NgramTree(): root(NULL) { }


/*
 copy constructor, uses private copy helper to copy using the two roots of the. BST's. copy in preorder traversal.
 */
NgramTree::NgramTree(const NgramTree& copy): root(NULL) {
    copyHelper(root, copy.root);
}

void NgramTree::copyHelper(TreeNode*& thisPtr,const TreeNode* copyPtr) {
    if (copyPtr != NULL) {
        thisPtr = new TreeNode;
        thisPtr->ngram = copyPtr->ngram;
        thisPtr->count = copyPtr->count;
        copyHelper(thisPtr->leftChildPtr, copyPtr->leftChildPtr);
        copyHelper(thisPtr->rightChildPtr, copyPtr->rightChildPtr);
    }
}


/*
 destructor, uses destroyTree function to recursively delete the whole tree.
 */
NgramTree::~NgramTree() {
    destroyTree(root);
}

/*
 destroyTree method, deletes nodes in postorder starting from treePtr. treePtr is used as the root in the destructor, and also is used to delete the remainder tree in the assignment operator
 */
void NgramTree::destroyTree(TreeNode*& treePtr)  {
    
    if (treePtr != NULL){
        destroyTree(treePtr->leftChildPtr);
        destroyTree(treePtr->rightChildPtr);
        delete treePtr;
        treePtr = NULL;
    }
    
}

/*
 assignment operator overload, uses assignmentHelper to assign rhs to this BST
 */
NgramTree& NgramTree::operator=(const NgramTree& rhs) {
    assignmentHelper(root, rhs.root);
    return *this;
}

/*
 assignmentHelper function, takes nodes of the lhs and rhs trees. Assigns in preorder. Deletes remaining tree if the rhs ends. Creates new TreeNode if lhs ends.
 */
void NgramTree::assignmentHelper(TreeNode*& thisPtr,const TreeNode* rhsPtr) {
    
    if (thisPtr != NULL && rhsPtr != NULL) {
        thisPtr->ngram = rhsPtr->ngram;
        thisPtr->count = rhsPtr->count;
        assignmentHelper(thisPtr->leftChildPtr, rhsPtr->leftChildPtr);
        assignmentHelper(thisPtr->rightChildPtr, rhsPtr->rightChildPtr);
    }
    
    else if (rhsPtr != NULL) {
        thisPtr = new TreeNode;
        thisPtr->ngram = rhsPtr->ngram;
        thisPtr->count = rhsPtr->count;
        assignmentHelper(thisPtr->leftChildPtr, rhsPtr->leftChildPtr);
        assignmentHelper(thisPtr->rightChildPtr, rhsPtr->rightChildPtr);
    }
    
    else if (thisPtr != NULL) {
        destroyTree(thisPtr);
    }
    
}

//------------------------------------------------------------
// Functions for Insertion, Deletion, Retrieval and Info
//------------------------------------------------------------

/*
 uses insertItem to add given ngram or increment the count value by one for more info see the insertItem function
 */
void NgramTree::addNgram(string ngram) {
    insertItem(root, ngram, 1);
}

/*
 uses ngramCounter, which takes the tree root, to recursively count the amount of ngrams
 */
int NgramTree::getTotalNgramCount() {
    
    return ngramCounter(root);
}

/*
 ngramCounter which counts how many ngrams exist in the tree. I used the ternary operation to write it i one line to give the idea of an algebrai coperation. If the pointer is NULL it adds 0 to the sum, if it exists it adds 1.
 */
int NgramTree::ngramCounter(TreeNode *treePtr) {
    return (treePtr != NULL ? 1 + ngramCounter(treePtr->leftChildPtr) + ngramCounter(treePtr->rightChildPtr): 0);
}

/*
 generateTree function which reads the file with the given file name. All objects used are under the standard library. first all lines are obtained while a line exists. Then istringstream divides the words in a given line, while t
 */
void NgramTree::generateTree(string fileName, int n){
    fstream file(fileName.c_str());
    string line, word;
    istringstream words;
    
    while(getline(file, line)) {
        
        words.str(line);
        
        while(words >> word) {
            
            int i = 0;
            
            while ((i + n) <= word.size()) {
                
                insertItem(root, word.substr(i, n), 1);
                i++;
                
            }
        }
    }
}

/*
 isComplete function. Uses completeCheck to determine whether the tree is a complete one or not.
 */
bool NgramTree::isComplete() {
    int ngramCount = getTotalNgramCount();
    return completeCheck(root, 0, ngramCount);
}

/*
 completeCheck, this function uses 2 other variables, index and ngramCount. ngramCount is th amount of ngrams in the tree (nodes) and index is the given index of the node in the tree. If a parent node in the tree has index i, then its left child node should have index i = 2*i+1 and its right i = 2*i+2. In a complete tree, we should have for each node i < ngramCount. Example: Think of a simple tree, with only 2 nodes, a root and its RIGHT child node. The root has index i = 0. The right child has index i = 2 * 0 + 2 = 2, the nodeCount is also 2. We know that this is not a compete tree since it doesnt have all nodes in h in the leftside, and by using i < ngramCount (2 < 2, false) the program also finds the tree to be NOT complete.
 */
bool NgramTree::completeCheck(TreeNode* treePtr, int index, const int& ngramCount) {
    if (treePtr == NULL)
        return true;
    else if (index < ngramCount)
        return completeCheck(treePtr->leftChildPtr, 2 * index + 1, ngramCount) && completeCheck(treePtr->rightChildPtr, 2 * index + 2, ngramCount);
    else
        return false;
    
    
}

/*
 isFull function. Uses fullCheck to recursively check whether the tree is full or not
 */
bool NgramTree::isFull() {
    
    return fullCheck(root);
}

/*
 fullCheck, if a BST is a full tree, then all non-NULL nodes should have two child nodes (both NULL or non-NULL). This function recursively checks this case. If the node at hand is NULL, or both its childs are NULL, then returns true. If both children are non-NULL, then it continues recirsively to check the child trees' full condition. Otherwise, its false.
 */
bool NgramTree::fullCheck(TreeNode* treePtr) {
    
    if (treePtr == NULL || (treePtr->leftChildPtr == NULL && treePtr->rightChildPtr == NULL))
        return true;
    else if (treePtr->leftChildPtr != NULL && treePtr->rightChildPtr != NULL)
        return fullCheck(treePtr->leftChildPtr) && fullCheck(treePtr->rightChildPtr);
    else
        return false;
    
}

/*
 isEmpty, checks the emptiness of the BST. Pretty self-explanatory, if the root is NULL, the tree is empty. If the root exists, then its not.
 */
bool NgramTree::isEmpty() const {
    return root == NULL;
}

/*
 public retrieve, insert and delete methods. These call their protected/private counterparts which have access to the root.
 */
void NgramTree::searchTreeRetrieve(string ngram, int& count) const{
    retrieveItem(root, ngram, count);
}
void NgramTree::searchTreeInsert(const string& ngram, const int& count) {
    insertItem(root, ngram, count);
}
void NgramTree::searchTreeDelete(string ngram) {
    deleteItem(root, ngram);
}


/*
 Similar to a normal retrieveItem function in a BST, it takes the string ngram as key and count as a reference. Recursively traverses, if the ngram exists in the tree then count is returned as reference. If not, throws exception.
 */
void NgramTree::retrieveItem(TreeNode* treePtr, string ngram, int& count) const throw(TreeException) {
    
    if (treePtr == NULL) {
        throw TreeException("NgramTreeException: Specified ngram not found.");
    }
    
    else if (ngram < treePtr->ngram) {
        retrieveItem(treePtr->leftChildPtr, ngram, count);
    }
    else if (ngram > treePtr->ngram) {
        retrieveItem(treePtr->rightChildPtr, ngram, count);
    }
    else {
        count = treePtr->count;
    }
}


/*
 This is pretty similar to a normal insertion in a default BST. This function asks for the count value as well, in case the user wants to enter a specific amount of ngram, default takes count as 1. Determines the placement in alphabetic order. In the case that the strings are equal, count of the node is incremented by 1.
 */
void NgramTree::insertItem(TreeNode*& treePtr,const string& ngram, const int& count) throw(TreeException) {
    if (treePtr == NULL) {
        treePtr = new TreeNode(ngram, count);
        if (treePtr == NULL)
            throw TreeException("NgramTreeException: Insertion Failed.");
    }
    
    else if (ngram < treePtr->ngram) {
        insertItem(treePtr->leftChildPtr, ngram, count);
    }
    else if (ngram > treePtr->ngram) {
        insertItem(treePtr->rightChildPtr, ngram, count);
    }
    else {
        treePtr->count += count;
    }
}


/*
 deleteItem function, recursively traverses the tree, if the node to be deleted is found, the function deleteNodeItem is called. If not, the function either continues traversing or if the ngram is not found, throws exception.
 */
void NgramTree::deleteItem(TreeNode*& treePtr, string ngram) throw(TreeException)  {
    if (treePtr == NULL) // Empty tree
        throw TreeException("NgramTreeException: Deletion Failed. Empty tree / Specified ngram does not exist.");
    
    else if (ngram < treePtr->ngram)
        deleteItem(treePtr->leftChildPtr, ngram);
    
    else if (ngram > treePtr->ngram)
        deleteItem(treePtr->rightChildPtr, ngram);
    else
        deleteNodeItem(treePtr);
}

/*
 deleteNodeItem, checks several possibilities of where the node might be (is it a leaf? does it have only left/right children?, is it a subtree?) and acts accordingly. If the node is a leaf, then the node is directly deleted. If only one child exists, then a temporary node is used to delete the node, and the node is assigned as the child node. If both children exist, then the inorder successor of the node is to be foun. For this, the method processLeftmost is used. It takes the ngram and count as reference variables and these will be assigned to the node at hand after the deletion.
 */
void NgramTree::deleteNodeItem(TreeNode*& nodePtr) {
    
    TreeNode* temp;
    
    if (nodePtr->leftChildPtr == NULL && nodePtr->rightChildPtr == NULL) {
        delete nodePtr;
        nodePtr = NULL;
    }
    else if (nodePtr->leftChildPtr == NULL) {
        temp = nodePtr;
        nodePtr = nodePtr->rightChildPtr;
        temp->rightChildPtr = NULL;
        delete temp;
    }
    else if (nodePtr->rightChildPtr == NULL) {
        temp = nodePtr;
        nodePtr = nodePtr->leftChildPtr;
        temp->leftChildPtr = NULL;
        delete temp;
    }
    else {
        string replaceNgram;
        int replaceCount;
        
        processLeftmost(nodePtr->rightChildPtr, replaceNgram, replaceCount);
        
        nodePtr->ngram = replaceNgram;
        nodePtr->count = replaceCount;
    }
    
}

/*
 processLeftmoost function, deletes the leftmost node of a given tree and assigns the reference variables its values. If the leftchild does not exist then it dertermines that the node at hand is the leftmost node hence deletes the node via a temp pointer and changes the pointer to point to the right child. Otherwise,  recursively continues to traverse until the leftmost node is found.
 */
void NgramTree::processLeftmost(TreeNode*& nodePtr, string& ngram, int& count) {
    
    if (nodePtr->leftChildPtr == NULL) {
        
        ngram = nodePtr->ngram;
        count = nodePtr->count;
        
        TreeNode* temp = nodePtr;
        
        nodePtr = nodePtr->rightChildPtr;
        temp->rightChildPtr = NULL;
        delete temp;
    }
    else
        processLeftmost(nodePtr->leftChildPtr, ngram, count);
    
}


//------------------------------------------------------------
// Traversals Section
//------------------------------------------------------------

/*
 public traversals. In the case that the user wants to traverse the whole tree using their own specified function. FunctionType asks for string reference ngram and int reference count
 */
void NgramTree::preorderTraverse(FunctionType visit) {
    preorder(root, visit);
}
void NgramTree::inorderTraverse(FunctionType visit) {
    inorder(root, visit);
}
void NgramTree::postorderTraverse(FunctionType visit) {
    postorder(root, visit);
}


/*
 traversal implementations. The placement of the recursive lines and the function call determines the order. These were taken from the slides.
 */
void NgramTree::preorder(TreeNode *treePtr, FunctionType visit) {
    if (treePtr != NULL) {
        visit(treePtr->ngram, treePtr->count);
        preorder(treePtr->leftChildPtr, visit);
        preorder(treePtr->rightChildPtr, visit);
    }
}

void NgramTree::inorder(TreeNode *treePtr, FunctionType visit) {
    if (treePtr != NULL) {
        inorder(treePtr->leftChildPtr, visit);
        visit(treePtr->ngram, treePtr->count);
        inorder(treePtr->rightChildPtr, visit);
    }
}

void NgramTree::postorder(TreeNode *treePtr, FunctionType visit) {
    if (treePtr != NULL) {
        postorder(treePtr->leftChildPtr, visit);
        postorder(treePtr->rightChildPtr, visit);
        visit(treePtr->ngram, treePtr->count);
    }
}

//------------------------------------------------------------
// Output Operator Overload
//------------------------------------------------------------

/*
 output operator overload, uses outHelper to recursively print the tree.
 */
ostream &operator<<( ostream& out, const NgramTree& tree) {
    tree.outHelper(out, tree.root);
    return out;
}

/*
 Prints a specified string with the tree data recursively inorder.
 */
void NgramTree::outHelper(ostream& out, TreeNode* treePtr) const{
    if (treePtr != NULL) {
        outHelper(out, treePtr->leftChildPtr);
        out << "\"" << treePtr->ngram << "\"" << " appears " << treePtr->count <<" time(s);\n";
        outHelper(out, treePtr->rightChildPtr);
    }
}
