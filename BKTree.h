/*******************************************************************************
 Spell Checker using BK-Tree
 
 This program is an implementation of a spell checker for English text. The
 spell checker incorporares a database of known words, which is built from a
 simple word list. The Burkhard-Keller Tree (BK-Tree for short) organizes the
 word list for efficient searching.
 
 BK-Tree implementation is based of the description in this article:
 http://blog.notdot.net/2007/4/Damn-Cool-Algorithms-Part-1-BK-Trees
 
 OTHER RESOURCES:
 https://en.wikipedia.org/wiki/Levenshtein_distance
 http://people.cs.vt.edu/shaffer/Book/C++3elatest.pdf (pg. 215 Sec. 6.3.2)
 
 Created by Kyle Bludworth on 11/30/15.
 Copyright © 2015 Kyle Bludworth. All rights reserved.
*******************************************************************************/

#ifndef BKTree_h
#define BKTree_h

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::basic_string;

struct Node
{
    string word;
    size_t distance;
    Node* leftChild;
    Node* rightSibling;
};

class BKTree
{
private:
    Node* root;
    Node* createNode(string w, size_t d);
    int min(int a, int b, int c);
    size_t levenshteinDistance(string w1, string w2);
    void recursiveSearch(Node* node, vector<string>& suggestions, string w,
                         size_t t, bool& wordFound);
    bool inRange(size_t curDist, size_t minDist, size_t maxDist);
    void printSuggestions(vector<string>& suggestions, bool wordFound);
public:
    BKTree();
    ~BKTree();
    void add(string w);
    void cleanString(basic_string<char>& s);
    void search(string w, int t);
};

#endif /* BKTree_h */
