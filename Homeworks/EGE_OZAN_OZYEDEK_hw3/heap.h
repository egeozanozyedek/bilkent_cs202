/*
* Title: Heaps
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 3
* Description: Heap header file. Defines functions and variables for the Heap class.
*/


#ifndef heap_h
#define heap_h

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_HEAP = 100000; // sets the max heap size to 100k. I dont know the extent of size used for testing, but I believe this will cover it.

class Heap {
  
public:
    
    Heap();
    
    /*
     function which inserts the given element a into the heap. The insertion first starts at node n (index = size). Then the value trickles to its place according to its value.
     */
    void insert(const int a);
    
    /*
     function which returns the maximum element in the heap. Since this is a max-heap, it returns the first node element.
     */
    int maximum();
    
    /*
     function which deletes the maximum element and also returns said element. Since this is a max-heap the top node (index = 0) will get deleted. It uses the helper function heapRebuild(index) to rebuild the heap. Returns the value of top node.
     */
    int popMaximum();
    
    /*
     returns the total number of comparisons that occur in the heap object. This exists for the heapsort algorithm.
     */
    int getComparisons();
    
    /*
     returns the size of the heap. Exists for the heapsort algorithm to allocate an array of its own with the same size as the heap.
     */
    int getSize();
    
    /*
     returns whether the heap is empty or not. If size is zero, returns true.
     */
    bool isEmpty();
    
protected:
    
    /*
     recursive function which rebuilds the heap to comply with the definition of binary heap. Called for the deletion of a node with the index of the node. It checks whether the node has children first, and then determines which children has a bigger value. The child with the bigger value then becames the node at index. It then calls the function with the index of the child, hence recursively rebuilds the heap.
     */
    void heapRebuild(int root);
    
private:
    
    int data[MAX_HEAP]; //allocates array from the stack of size MAX_HEAP
    int size; // the current size of the array
    int comparisons; // the amount of comparisons
    
    
};

#endif /* heap_h */
