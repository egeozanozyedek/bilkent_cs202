/*
* Title: Algorithm Efficiency and Sorting
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 1
* Description: The header file for all sort algorithms and their needed functions
*/

#ifndef sorting_h
#define sorting_h

class sorting {
    
public:
    
    void insertionSort( int* arr, const int size, int& compCount, int& moveCount );
    void mergeSort( int* arr, const int size, int& compCount, int& moveCount );
    void quickSort( int* arr, const int size, int& compCount, int& moveCount );
    
private:
    
    void merge( int* arr, int* leftArr, int* rightArr, int leftSize, int rightSize, int& compCount, int& moveCount);
    
    void partition(int* arr, int*& leftArr, int*& rightArr, int size, int& leftSize, int& rightSize, int& compCount, int& moveCount);
    
    void swap(int &x, int &y);
    
};

#endif /* sorting_h */
