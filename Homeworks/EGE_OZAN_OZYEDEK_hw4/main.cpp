/**
 * Title: AVL Trees
 * Author: Ege Ozan Özyedek
 * ID: 21703374
 * Assignment: 4
 * Description: the main function which uses the AVLFreq class and tests out its functions
 */

#include "avlfreq.h"

int main(int argc, const char * argv[]) {
    
    string input(argv[1]);
    //    string input = "jamesJoyceDubliners.txt"; //for testing
    string wordfreqFile = "wordfreq";
    string statisticsFile = "statistics";
    
    ofstream wordfreq(wordfreqFile), statistics(statisticsFile);
    
    AVLFreq avl;
    
    //generate tree
    avl.generateTree(input);
    
    //print words and stats
    avl.printWordFrequencies(wordfreq);
    
    //print stats
    avl.printTotalWordCount(statistics);
    avl.printHeight(statistics);
    avl.printMostFrequent(statistics);
    avl.printLeastFrequent(statistics);
    avl.printStandartDeviation(statistics);
    
    
    wordfreq.close();
    statistics.close();
    
    return 0;
}
