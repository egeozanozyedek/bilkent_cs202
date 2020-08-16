/*
 * Title: Heaps
 * Author: Ege Ozan Özyedek
 * ID: 21703374
 * Assignment: 3
 * Description: The main function which houses the heapsort algorithm. It does several things both for the sorting itself and also for testing. First it takes the input and output file names from the console and inserts the values in the input file into the heap object h. Then it pops all max values and places them in ascending order into a pointer array (I didnt want to use the stack bc the heap already depends on the stack, I dont think it makes a huge difference in this assignment but still). Then the number of comparisons and array elements are written into the output file.
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
 #include <math.h>
#include "heap.h"


using namespace std;

int main(int argc, const char * argv[]) {
    
    
    Heap h;
    string inFileName(argv[1]), outFileName(argv[2]);
    //        string inFileName = "data5", outFileName = "out.txt"; //for testing

    ifstream inFile(inFileName.c_str());
    ofstream outFile(outFileName.c_str());
    string line, word, output;
    
    while(getline(inFile, line))
        h.insert(atoi(line.c_str()));
    
    //clock_t start = clock();
    int size = h.getSize(), *arr = new int[size], i = 0;

    
    while (!h.isEmpty()) {
        arr[size - 1 - i] = h.popMaximum();
        i++;
    }
    
    outFile << "Comparison Amount: " << h.getComparisons() << "\n";
    
    for (int i = 0; i < size; i++) {
        outFile << arr[i] << "\n";
    }
    
    outFile.close();
    delete [] arr;
    
    //========================================
    // DIFFERENT IMPLEMENTATION WITHOUT AN INT ARRAY
    // LESS EFFICIENT IN TERMS OF TIME
    //========================================
    
    
    //    output = to_string(h.popMaximum()) + output;
    //    while (!h.isEmpty()) {
    //        output = to_string(h.popMaximum()) + "\n" + output;
    //    }
    //
    //    output = "\nComparison Amount: " + to_string(h.getComparisons()) + "\n" + output;
    //
    //    outFile << output;
    
    
    
    //========================================
    // FOR TESTING -- COMPUTES THE EXPECTED
    // NUMBER OF COMPARISONS AND ALSO THE TIME
    //========================================
    
//    float time = (clock() - start ) / (float) CLOCKS_PER_SEC;
//
    int expectedComp = 0;

    for (int n = 1; n <= size; n++) {
        expectedComp += ceil(log2(n+1)) - 1;
        
    }
    expectedComp *= 2;
    cout << "Expected Comparison Amount: " << expectedComp << "\n";
    cout << "Comparison Amount of HeapSort: " << h.getComparisons() << "\n";
    
    double acc = (h.getComparisons() - expectedComp) * 100 / (double) expectedComp;
    acc = 100 - abs(acc);
    
    cout << "Accuracy: " << acc << "\n";
//
//    cout << "TIME: " << time << "\n";
}
