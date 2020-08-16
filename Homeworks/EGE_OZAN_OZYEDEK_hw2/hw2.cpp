/*
* Title: Trees
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 2
* Description: main function, tests several functions of the NgramTree
*/

#include <iostream>
#include <stdlib.h>
#include "NgramTree.h"


int main(int argc, const char * argv[]) {
    
    
    NgramTree tree;
//    string fileName( "input.txt");
//    int n = 4;
    
    string fileName( argv[1]);
    int n = atoi( argv[2] );
    tree.generateTree(fileName, n);
    
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << "\n";
    cout << tree << "\n";
    
    cout << n << "-gram tree is complete: " << (tree.isComplete() ? "Yes" : "No") << "\n";
    
    cout << n << "-gram tree is full: " << (tree.isFull() ? "Yes" : "No") << "\n";
    
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << "\n";
    
    tree.addNgram( "samp" );
    tree.addNgram( "samp" );
    tree.addNgram( "zing" );
    tree.addNgram( "aatt" );
    
    cout << "\nTotal " << n << "-gream count: " << tree.getTotalNgramCount() << "\n";
    cout << tree << "\n";
    
    cout << n << "-gram tree is complete: " << (tree.isComplete() ? "Yes" : "No") << "\n";
    
    cout << n << "-gram tree is full: " << (tree.isFull() ? "Yes" : "No") << "\n";
    
    
    cout << "\n\n------------------------------------------------------------\n";
    cout << "ADDITIONAL TESTS";
      cout << "\n------------------------------------------------------------\n";
    
    NgramTree copy(tree), assignment, nullified, delAPortion, full;;
    //    assignment = tree;
    //    tree = nullified;
    
    cout << "\nCOPY " << n << "-gream count: " << copy.getTotalNgramCount() << "\n";
    cout << copy << "\n";
    
    cout << "\nASSIGNMENT " << n << "-gream count: " << assignment.getTotalNgramCount() << "\n";
    cout << assignment << "\n";
    
    cout << "\n--------\n";
    
    assignment  = tree;
    
    cout << "\nASSIGNMENT " << n << "-gream count: " << assignment.getTotalNgramCount() << "\n";
    cout << assignment << "\n";
    
    int c;
    try {
        assignment.searchTreeRetrieve("sam", c);
        cout << c;
    } catch (TreeException) {
        cout << "Error\n";
    }
    
    copy.searchTreeDelete("ampl");
    
    cout << "\nCOPY " << n << "-gream count: " << copy.getTotalNgramCount() << "\n";
    cout << copy << "\n";
    
    cout << "COPY-gram tree is full: " << (copy.isFull() ? "Yes" : "No") << "\n";
    
    
    full.addNgram("d");
    full.addNgram("b");
    full.addNgram("f");
    full.addNgram("a");
    full.addNgram("c");
    full.addNgram("e");
    full.addNgram("g");
    
    cout << "\nFULL " << n << "-gream count: " << full.getTotalNgramCount() << "\n";
    cout << full << "\n";
    
    cout << "FULL-gram tree is full: " << (full.isFull() ? "Yes" : "No") << "\n";
    cout << "FULL-gram tree is complete: " << (full.isComplete() ? "Yes" : "No") << "\n";
    
    full.searchTreeDelete("g");
    
    cout << "FULL-gram tree is complete: " << (full.isComplete() ? "Yes" : "No") << "\n";
    
    full.searchTreeDelete("c");
    
    cout << "FULL-gram tree is complete: " << (full.isComplete() ? "Yes" : "No") << "\n";
    
    cout << "\nFULL " << n << "-gream count: " << full.getTotalNgramCount() << "\n";
    cout << full << "\n";
    
    return 0;
}
