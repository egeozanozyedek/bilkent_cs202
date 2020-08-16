/**
 * Title: AVL Trees
 * Author: Ege Ozan Özyedek
 * ID: 21703374
 * Assignment: 4
 * Description: The AVLFreq class header file. Contains the classes Node and AVLFreq, function definitions and also descriptions of given functions.
 */

#ifndef avlfreq_h
#define avlfreq_h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <math.h>

enum rotation {left, right};

using std::string;
using std::cout;
using std::ofstream;
using std::ifstream;
using std::istringstream;
/**
 * Node class
 * Contains pointers to left and right nodes
 * Contains the word element and its frequency
 * The constructor initializes NULL to pointers and zero to frequency
 * friend class is declared as AVLFreq since it will be using Node class private members
 */
class Node {
    Node(): left(NULL), right(NULL), frequency(0) {}
private:
    Node *left, *right;
    string word;
    int frequency;
    friend class AVLFreq;
};

/**
 * AVLFreq Class
 * An AVL tree which contains word elements. Generated from a file.
 * Contains the root node as a  private member
 */
class AVLFreq {
    
public:
    
    /**
     * Constructor of AVLFreq class
     * Initializes root node to NULL
     */
    AVLFreq();
    
    /**
     * Destructor of AVLFreq class
     * Uses destroyTree function to delete all allocations
     */
    ~AVLFreq();
    
    /**
     * Parses the given txt file to add words into the AVL tree.
     * The function obtains strings which are seperated by spaces.
     * Punctuations in string are replaced with space charachters to create individual words.
     * Digits are allowed to be interpreted as words.
     * @param fileName the name of the input file to be parsed
     */
    void generateTree(string fileName);
    
    /**
     * The function only serves the purpose of changing the root node of the tree.
     * Uses insert function to add parameter word
     * @param word the input string that was obtained from the file
     */
    void addWord(string word);
    
    /**
     * Prints each word and its frequency next to it
     * @param file the output file which the word and frequencies will be written to
     * @relatesalso wordFrequenciesHelper
     */
    void printWordFrequencies(ofstream& file);
    
    /**
     * Prints the height of the tree
     * @param file the output file which the height data will be written to
     * @relatesalso getHeight
     */
    void printHeight(ofstream& file);
    
    /**
     * Prints the total word count of the tree, a.k.a its node size
     * @param file the output file for printing
     * @relatesalso getSize
     */
    void printTotalWordCount(ofstream& file);
    
    /**
     * Prints the most frequent word in the tree
     * @param file the output file for printing
     * @relatesalso findMostFrequent
     */
    void printMostFrequent(ofstream& file);
    
    /**
     * Prints the least frequent word in the tree
     * @param file the output file for printing
     * @relatesalso findLeastFrequent
     */
    void printLeastFrequent(ofstream& file);
    
    /**
     * Computes and prints the standard deviation of the word frequencies contained in the tree
     * @param file the output file
     * @relatesalso getSize
     * @relatesalso getTotal
     * @relatesalso findSquareSum
     */
    void printStandartDeviation(ofstream& file);
    
protected:
    
    /**
     * The insertion part is no different than normal insertion to a BST, recursively finds the correct placement to insert
     * If no node exists then creates a new node with given word
     * If a node with the same word exists then it increases its frequency
     * After the insertion, from the insertion point, while the recursion unfolds, the function tries to find imbalance
     * If imbalance exists, the function finds which type of rotation to make according to the insertion point
     * @param node a reference to a pointer to traverse and insert a new node into the tree
     * @return Node* which for the first step of recursion represents the root node of the tree after insertion
     * @relatesalso rotation
     * @relatesalso getBalance
     */
    Node* insert(Node*& node, string word);
    
    /**
     * Makes rotation according to the given direction
     * @param r the direction of the rotation, enumerated as left or right
     * @param node the problematic parent node which the rotation will occur on
     * @return Node* the final parent node after rotation, to keep track of connections in the tree
     */
    Node* rotation(rotation r, Node*& node);
    
    /**
     * Deletes all members of a tree with given root, in postOrder
     * @param node the root of tree/subtree which will be destroyed
     */
    void destroyTree(Node*& node);
    
    /**
     * Returns the balance of the tree
     * @param node the parent node which will be used to find the balance
     * @return the height difference, i.e. balance
     */
    int getBalance(Node* node) const;
    
    /**
     * Recursively prints the words and their frequencies, inOrder (alphabetic)
     * @param node the node which contains the word and the frequency to be printed
     * @param file the output file
     */
    void wordFrequenciesHelper(Node* node, ofstream& file);
    
    /**
     * Recursively computes the height of tree with given parent node
     * @param node the parent node from which the height will be computed
     * @return the height of the tree
     */
    int getHeight(Node* node) const;
    
    /**
     * Recursively traverses all elements of the tree to find the most frequent word node
     * @param node the root node of the tree, used for recursion
     * @param most a pointer reference which contains the node with the word that has the least frequency
     */
    void findMostFrequent(Node* node, Node*& most);
    
    /**
     * Recursively traverses all elements of the tree to find the least frequent word node
     * @param node the root node of the tree, used for recursion
     * @param least a pointer reference which contains the node with the word that has the least frequency
     */
    void findLeastFrequent(Node* node, Node*& least);
    
    /**
     * Recursively counts all nodes in the tree to find the number of nodes
     * @param node the root node of the tree
     * @return the number of nodes in the tree
     */
    int getSize(Node* node);
    
    /**
     * Recursively sums up all frequencies in all nodes, used to find the standard deviation
     * @param node the root node of the tree
     * @return the total frequency amount in the tree
     */
    int getTotal(Node* node);
    
    /**
     * Recursively finds the square sum of the tree, used to find the standard deviation
     * @param node the root node of the tree
     * @param mean the mean average of all frequencies in the tree
     * @return the square sum needed to find the standard deviation
     */
    int findSquareSum(Node* node, double mean);
    
    
private:
    
    Node *root; ///root node of the tree
};


#endif /* avlfreq_h */
