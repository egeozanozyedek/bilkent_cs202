/*
* Title: Algorithm Efficiency and Sorting
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 1
* Description: description of your code
*/

#include <iostream>
#include <chrono>
#include <fstream>
#include "sorting.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    ofstream timeFile("timedata.txt"), moveFile("movedata.txt"), compFile("compdata.txt");
    sorting s;
    
    
    //size amounts
    int size[] = {20000, 30000, 40000, 50000, 60000, 120000, 140000, 160000, 180000, 200000};
    int X = 5; //the size of the above array
    
    //create 2D arrays for data
    
    int** moves = new int*[X];
    int** comparisons = new int*[X];
    double** time = new double*[X];
    
    for (int i = 0; i < X; i++) {
        
        moves[i] = new int[3];
        comparisons[i] = new int[3];
        time[i] = new double[3];
        
    }
    
    //initialize move, comp and time to zero
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < 3; j++) {
            moves[i][j] = 0;
            comparisons[i][j] = 0;
            time[i][j] = 0;
        }
    }
    
    for (int i = 0; i < X; i++) {
        
        int* insertArr = new int[size[i]];
        int* mergeArr = new int[size[i]];
        int* quickArr = new int[size[i]];
        
        //ASSIGN ARRAY - I changed this part for 3 experiments
        for (int j = 0; j < size[i]; j++) {
            
            insertArr[j] = j;
            mergeArr[j] = insertArr[j];
            quickArr[j] = insertArr[j];
        }
        
        std::chrono::steady_clock::time_point begin0 = std::chrono::steady_clock::now();
        s.insertionSort(insertArr, size[i], comparisons[i][0], moves[i][0]);
        std::chrono::steady_clock::time_point end0 = std::chrono::steady_clock::now();
        
        
        
        std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
        s.mergeSort(mergeArr, size[i], comparisons[i][1], moves[i][1]);
        std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
        
        std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
        s.quickSort(quickArr, size[i], comparisons[i][2], moves[i][2]);
        std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
        
        time[i][0] = std::chrono::duration_cast<std::chrono::microseconds>(end0 - begin0).count()/ double(1000000);
        
        time[i][1] = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count()/ double(1000000);
        
        time[i][2] = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count()/ double(1000000);
        
        
 
        delete [] insertArr;
        delete [] mergeArr;
        delete [] quickArr;
        
        
    }
    
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < 3; j++) {
            moveFile << moves[i][j];
            compFile << comparisons[i][j];
            timeFile << time[i][j];
            
            if (j < 2) {
                
                moveFile << "\t";
                compFile << "\t";
                timeFile << "\t";
            }
            
            
        }
        moveFile << "\n";
        compFile << "\n";
        timeFile << "\n";
        
    }
    
    
    moveFile.close();
    timeFile.close();
    compFile.close();
    
    
    //stream here
    
    
    for ( int i = 0; i < X; i++ ) {
        delete [] moves[i];
        delete [] comparisons[i];
        delete [] time[i];
    }
    
    return 0;
}


