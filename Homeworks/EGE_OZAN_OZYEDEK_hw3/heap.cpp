/*
* Title: Heaps
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 3
* Description: Heap implementation file. Implements the functions and uses the variables found in the header file.
*/


#include "heap.h"
#include "HeapException.h"

Heap::Heap(): size(0) {}


void Heap::insert(const int a) {
    if (size >= MAX_HEAP)
        throw HeapException("Invalid argument: Maximum heap size reached."); //error if MAX_HEAP is reached
    
    data[size] = a;
    
    int currentNode = size;
    int parent = (currentNode - 1)/2;
    
    //trickles the value into its supposed position
    while ( (currentNode > 0) && (data[currentNode] > data[parent]) ) {
        int temp = data[parent];
        data[parent] = data[currentNode];
        data[currentNode] = temp;
        currentNode = parent;
        parent = (currentNode - 1)/2;
        comparisons++;
    }
    ++size;
}

int Heap::maximum() {
    return isEmpty() ? throw HeapException("Error: Cannot obtain maximum because heap is empty.") : data[0];
}


int Heap::popMaximum() {
    
    if (isEmpty())
        throw HeapException("Error: Cannot obtain maximum because heap is empty.");
    else {
        int max = data[0]; //get value of top node
        data[0] = data[--size]; //delete node and replace it with the last node
        heapRebuild(0); //rebuild heap
        return max;
    }
}

bool Heap::isEmpty() {
    return size == 0;
}

int Heap::getComparisons() {
    return comparisons;
}

int Heap::getSize() {
    return size;
}

void Heap::heapRebuild(int root) {
    
    int child = 2 * root + 1; //left child is assumed first
    
    if ( child < size ) { //if left child exists
        int right = child + 1;
        
        if ( right < size ) { //if right child exists
            comparisons++; //only increased if right child exists
            if (data[right] > data[child]) //if right child is bigger than left child
                child = right; //right child is assumed
        }
        
        comparisons++; //only increased if left child exists
        if ( data[root] < data[child] ) { //if left child is bigger than current node
            int temp = data[root];
            data[root] = data[child];
            data[child] = temp; // swap
            heapRebuild(child); //call the function again for the child node
        }
    }
}



