//
//  main.cpp
//  BKTree
//
//  Created by Kyle Bludworth on 12/7/15.
//  Copyright © 2015 Kyle Bludworth. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include "BKTree.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

int main(int argc, const char * argv[]) {
    
    BKTree* tree = new BKTree();
    
    string line;
    
    ifstream myFile("words.txt"); // 154,937 English words
    clock_t start;
    clock_t end;
    double elapsed_secs;
    
    if (myFile.is_open())
    {
        cout << "Building structure... " << endl;
        
        while (getline(myFile, line))
            tree->add(line);
        
        myFile.close();
    }
    cout << "Done." << endl << endl;
    int count = 0;
    while (count < 5)
    {
        string word;
        cout << "Enter word: ";
        cin >> word;
        
        tree->cleanString(word);
        
        start = clock();
        tree->search(word, 1);
        end = clock();
        
        elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
        cout << "Results found in "<< elapsed_secs << "s" << endl << endl;
        
        count++;
    }
    return 0;
}
