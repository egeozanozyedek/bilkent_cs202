/*
* Title: Algorithm Efficiency and Sorting
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 1
* Description: Implementations of sorting algorithms
*/

#include <iostream>
#include "sorting.h"

/*
 Same implementation as the slides. Not much excitement here.
 */
void sorting::insertionSort( int* arr, const int size, int& compCount, int& moveCount ) {
    
    for (int unsorted = 1; unsorted < size; ++unsorted) {
        
        int nextItem = arr[unsorted];
        int traverse = unsorted;
        
        while (traverse > 0 && arr[traverse-1] > nextItem){
            
            arr[traverse] = arr[traverse-1];
            traverse--;
            
            moveCount++;
            compCount++;
            
        }
        
        arr[traverse] = nextItem;
        compCount++;
        moveCount++;
        
    }
    
}



/*
 Unlike the implementation given to us, I was required to take only one integer values (size) instead of two (first and last). This perhaps optimizes the function itself but not the implementation. It creates two "arrays", left and right, which are just pointers (left points to the start of the initial array, right points to the middle point of the initial array. They have sizes accordingly)
 */
void sorting::mergeSort( int* arr, const int size, int& compCount, int& moveCount ) {
    
    if (size > 1) {
        
        
        int leftSize = size/2; //there is rounding below here so 5/2 = 2
        int rightSize = size - leftSize; //self-explanatory, the size of the rest of the array
        int* leftArr = &arr[0]; //the left array starts from the beggining of the initial array
        int* rightArr = &arr[size/2]; //the right array starts from index = size/2. If the array is of size 5, and left has size 2 (ends at index 1), right should start at index 2.
        
        mergeSort(leftArr, leftSize, compCount, moveCount);
        
        mergeSort(rightArr, rightSize, compCount, moveCount);
        
        merge(arr, leftArr, rightArr, leftSize, rightSize, compCount, moveCount);
        
        
    }
    
    
    
}

/*
 Again, this was challenging since we dont have simple int values, but it is not much different from the actual implementation. It takes all array values and sizes, compares elements and creates a temporary sorted array. This temp array is then copied onto the actual array. Hence the array is sorted.
 */
void sorting::merge( int* arr, int* leftArr, int* rightArr, int leftSize, int rightSize, int& compCount, int& moveCount) {
    
    int* temp = new int[leftSize + rightSize]; //create temp array with the size of the big array (arr)
    
    int index = 0, leftIndex = 0, rightIndex = 0; //different from the textbook implementation, since I used pointers, all of                                           them start with the index zero
    
    //all loops below (except for the last one) compares elements and places them to the correct position on the
    //temp array
    while (leftIndex < leftSize && rightIndex < rightSize) {
        
        if (leftArr[leftIndex] < rightArr[rightIndex]) {
            
            temp[index] = leftArr[leftIndex];
            leftIndex++;
            
        }
        
        else {
            temp[index] = rightArr[rightIndex];
            rightIndex++;
        }
        
        index++;
        
        moveCount++;
        compCount++;
    }
    
    //if any elements are left are compared and positioned
    while (leftIndex < leftSize) {
        temp[index] = leftArr[leftIndex];
        leftIndex++;
        index++;
        
        moveCount++;
        compCount++;
    }
    
    //if any elements are left are compared and positioned
    while (rightIndex < rightSize) {
        temp[index] = rightArr[rightIndex];
        rightIndex++;
        index++;
        
        moveCount++;
        compCount++;
    }
    
    compCount += 3;
    
    //the temp array elements are copied into the
    for (index = 0; index < (leftSize + rightSize); index++) {
        arr[index] = temp[index];
        moveCount++;
    }
    
    //we dont want any memory leaks
    delete [] temp;
    
}


/*
 Again, similar to the obstacle we had in mergesort, I am only given one int variable. So again, pointers are in use. The difference between quick and merge sort is that quick sort makes comparisons first. So the array is "divided" after the fact. So, I initialize left and right arrays as NULL and sizes as zero. These change accordingly in partition. Also the pivot is chosen as the first element.
 */
void sorting::quickSort( int* arr, const int size, int& compCount, int& moveCount ) {
    
    if (size > 1 && arr != NULL) {
        int leftSize = 0, rightSize = 0; //no need for pivot index since its always 0
        int *leftArr = NULL, *rightArr = NULL;
        
        partition(arr, leftArr, rightArr, size, leftSize, rightSize, compCount, moveCount);
        quickSort(leftArr, leftSize, compCount, moveCount);
        quickSort(rightArr, rightSize, compCount, moveCount);
    }
    
    
}



/*
 Not very different from the version in the slides. The pivot is the first element, then the array is traversed to create the left and right arrays. The left and right arrays are taken as reference to a pointer.
 */
void sorting::partition(int* arr, int*& leftArr, int*& rightArr, int size, int& leftSize, int& rightSize, int& compCount, int& moveCount) {
    
    
    int pivotIndex = 0;
    int leftLast = 0;
    int pivot = arr[pivotIndex];
    
    for (int traverse = leftLast + 1; traverse < size; traverse++) {
        
        if (arr[traverse] < pivot) {
            leftLast++;
            swap(arr[traverse], arr[leftLast]);
            compCount++;
            moveCount += 3;
        }
        compCount++;
    }
    
    swap(arr[pivotIndex], arr[leftLast]);
    moveCount += 3;
    
    leftArr = &arr[0]; //left array starts at the beggining of the partitioned array
    rightArr = &arr[leftLast + 1]; //right array starts AFTER the pivot index
    leftSize = leftLast; //similar to the reasoning in merge function, pivot is in leftLast index
    rightSize = size - leftSize - 1; // -1 takes out the pivot
    
}

/*
 Simple swap method. I didnt want to risk using the std version so I manually wrote this one
 */
void sorting::swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

