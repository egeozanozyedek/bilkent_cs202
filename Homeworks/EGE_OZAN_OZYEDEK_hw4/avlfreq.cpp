/**
 * Title: AVL Trees
 * Author: Ege Ozan Özyedek
 * ID: 21703374
 * Assignment: 4
 * Description: AVLFreq class implementations
 */

#include "avlfreq.h"

AVLFreq::AVLFreq(): root(NULL) {}

AVLFreq::~AVLFreq() {
    destroyTree(root);
}


void AVLFreq::destroyTree(Node*& node)  {
    if (node != NULL){
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
        node = NULL;
    }
}

void AVLFreq::generateTree(string fileName) {
    
    ifstream file(fileName.c_str());
    string line, word;
    std::istringstream words;
    
    //pass each line
    while(getline(file, line)) {
        
        for (int i = 0; i < line.size(); i++) {
            
            //get rid of punctuations and replace with space
            if (ispunct(line[i]))
                line.replace(i--, 1, " ");
            
            //creating case insensitivity
            if(isupper(line[i])) {
                string str(1,tolower(line[i]));
                line.replace(i--, 1, str);
            }
            
        }
        
        words.clear();
        words.str(line);
        
        while(words >> word)
            addWord(word);
        
    }
}


void AVLFreq::addWord(string word) {
    //unlike a regular BST the root node changes with insertion because of rotations
    root = insert(root, word);
}

Node* AVLFreq::insert(Node*& node, string word) {
    
    //if node dne then create a new node
    if (node == NULL) {
        node = new Node;
        node->word = word;
        node->frequency++;
        return node;
    }
    
    //if node with same word exists increase frequency return same root node
    else if (word == node->word) {
        node->frequency++;
        return node;
    }
    
    //continue on left and right nodes for insertion
    else if (word < node->word)
        node->left = insert(node->left, word);
    else
        node->right = insert(node->right, word);
    
    
    int balance = getBalance(node);
    
    //tree is not balanced, will fall in at the problematic node
    
    if (abs(balance) > 1) {
        
        /*
         left substree of node is higher (insertion into left child)
         word is smaller than left child (insertion into left subtree of left child)
         Single right rotation
         */
        if (balance > 1 and word < node->left->word) {
            return rotation(right, node);
            
        }
        
        /*
         Left substree of node is higher (insertion into left child)
         Word is bigger than left child (insertion into right subtree of left child)
         Double rotation, left-right
         */
        else if (balance > 1 and word > node->left->word) {
            node->left = rotation(left, node->left);
            return rotation(right, node);
        }
        
        /*
         Right substree of node is higher (insertion into right child)
         Word is bigger than right child (insertion into right subtree of right child)
         Single left rotation
         */
        else if (balance < -1 and word > node->right->word) {
            return rotation(left, node);
        }
        
        /*
         Right substree of node is higher (insertion into right child)
         Word is smaller than right child (insertion into left subtree of right child)
         Double rotation, right-left
         */
        else if (balance < -1 and word < node->right->word) {
            node->right = rotation(right, node->right);
            return rotation(left, node);
        }
    }
    
    return node;
}

Node* AVLFreq::rotation(enum rotation r, Node*& node) {
    
    //the k2 and k1's below represent the nodes from the lecture slides, returns the final parent node
    //after rotation
    
    if (r == left) {
        Node *k2 = node->right;
        Node *B = k2->left;
        
        k2->left = node;
        node->right = B;
        return k2;
    }
    
    if (r == right) {
        Node *k1 = node->left;
        Node *B = k1->right;
        
        k1->right = node;
        node->left = B;
        return k1;
    }
    
    return NULL;
}


/*
 functions below this point are pretty self explanatory since most traverse the tree
 and some action occurs such as printing or finding the least-most frequent word
 */

int AVLFreq::getHeight(Node *node) const {
    if (node == NULL)
        return 0;
    else {
        int left = getHeight(node->left);
        int right = getHeight(node->right);
        return 1 + (left > right ? left : right);
    }
}

int AVLFreq::getBalance(Node *node) const {
    return getHeight(node->left) - getHeight(node->right);
}

void AVLFreq::printWordFrequencies(ofstream& file) {
    wordFrequenciesHelper(root, file);
}

void AVLFreq::wordFrequenciesHelper(Node* node, ofstream& file) {
    if (node != NULL) {
        wordFrequenciesHelper(node->left, file);
        file << node->word << ": " << node->frequency << "\n";
        wordFrequenciesHelper(node->right, file);
    }
}

void AVLFreq::printMostFrequent(ofstream& file) {
    Node* most = root;
    findMostFrequent(root, most);
    if(most != NULL)
        file << "Most Frequent: " << most->word << " " << most->frequency << "\n";
}
void AVLFreq::findMostFrequent(Node* node, Node*& most) {
    if (node != NULL) {
        findMostFrequent(node->left, most);
        if (most->frequency < node->frequency)
            most = node;
        findMostFrequent(node->right, most);
    }
}


void AVLFreq::printLeastFrequent(ofstream& file) {
    Node* least = root;
    findLeastFrequent(root, least);
    if(least != NULL)
        file << "Least Frequent: " << least->word << " " << least->frequency << "\n";
}
void AVLFreq::findLeastFrequent(Node* node, Node*& least) {
    if (node != NULL) {
        findLeastFrequent(node->left, least);
        if (least->frequency > node->frequency)
            least = node;
        findLeastFrequent(node->right, least);
    }
}


void AVLFreq::printHeight(ofstream& file) {
    file << "Tree Height: " << getHeight(root) << "\n";
}


void AVLFreq::printTotalWordCount(ofstream& file) {
    int size;
    size = getSize(root);
    file << "Total Word Count: " << size << "\n";
}

/*
 below this point are the functions needed for the standard deviation
 its pretty hefty compared to other printing functions since it needs
 a ton of prior information such as the mean and the tree size.
 */

void AVLFreq::printStandartDeviation(ofstream& file) {
    int size = 0, total = 0;
    double mean = 0, sum = 0, std = 0;
    
    size = getSize(root);
    total = getTotal(root);
    
    mean = total / (double) size;
    sum = findSquareSum(root, mean);
    std = sqrt(sum / size);
    
    file << "Standard Deviation: " << std << "\n";
}

int AVLFreq::getSize(Node* node) {
    if (node != NULL)
        return 1 + getSize(node->left) +getSize(node->right);
    else
        return 0;
}

int AVLFreq::getTotal(Node* node) {
    if (node != NULL)
        return node->frequency + getTotal(node->left) + getTotal(node->right);
    else
        return 0;
}

int AVLFreq::findSquareSum(Node* node, double mean) {
    if (node != NULL) {
        return pow((node->frequency - mean), 2) + findSquareSum(node->left, mean) + findSquareSum(node->right, mean);
    }
    else
        return 0;
}
