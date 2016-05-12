/*******************************************************************************
 Spell Checker using BK-Tree
 
 This program is an implementation of a spell checker for English text. The
 spell checker incorporates a database of known words, which is built from a
 simple word list. The Burkhard-Keller Tree (BK-Tree for short) organizes the
 word list for efficient searching.
 
 BK-Tree implementation is based of the description in this article:
 http://blog.notdot.net/2007/4/Damn-Cool-Algorithms-Part-1-BK-Trees
 
 OTHER RESOURCES:
 https://en.wikipedia.org/wiki/Levenshtein_distance
 http://people.cs.vt.edu/shaffer/Book/C++3elatest.pdf (pg. 215 Sec. 6.3.2)
 https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s13
 
 Created by Kyle Bludworth on 11/30/15.
 Copyright © 2015 Kyle Bludworth. All rights reserved.
*******************************************************************************/

#include "BKTree.h"

using std::cout;
using std::endl;
using std::string;
using std::basic_string;
using std::vector;

BKTree::BKTree() { root = NULL; }
BKTree::~BKTree() { delete root; }

Node* BKTree::createNode(string w, size_t d)
{
    Node* node = new Node();
    
    node->word = w;
    node->distance = d;
    node->leftChild = NULL;
    node->rightSibling = NULL;
    
    return node;
}

void BKTree::add(string w)
{
    if (root == NULL)
    {
        root = createNode(w, -1);
        return;
    }
    
    Node* curNode = root;
    Node* child;
    Node* newChild;
    size_t dist;
    
    while (1) {
        dist = levenshteinDistance(curNode->word, w);
        if (!dist)
            return;
        child = curNode->leftChild;
        while (child)
        {
            if (child->distance == dist)
            {
                curNode = child;
                break;
            }
            child = child->rightSibling;
        }
        if (!child)
        {
            newChild = createNode(w, dist);
            newChild->rightSibling = curNode->leftChild;
            curNode->leftChild = newChild;
            break;
        }
    }
}

void BKTree::search(string w, int t)
{
    vector<string> suggestions;
    bool wordFound = false;
    
    recursiveSearch(root, suggestions, w, t, wordFound);
    
    printSuggestions(suggestions, wordFound);
}

void BKTree::recursiveSearch(Node* curNode, vector<string>& suggestions, string w,
                             size_t t, bool& wordFound)
{
    size_t curDist = levenshteinDistance(curNode->word, w);
    size_t minDist = curDist - t;
    size_t maxDist = curDist + t;
    
    if (!curDist) {
        wordFound = true;
        return;
    }
    if (curDist <= t)
        suggestions.push_back(curNode->word);
    
    Node* child = curNode->leftChild;
    if (!child) return;
    
    while (child)
    {
        if (inRange(child->distance, minDist, maxDist))
            recursiveSearch(child, suggestions, w, t, wordFound);
        
        child = child->rightSibling;
    }
    
}

bool BKTree::inRange(size_t curDist, size_t minDist, size_t maxDist)
{
    return (minDist <= curDist && curDist <= maxDist);
}

void BKTree::printSuggestions(vector<string>& suggestions, bool wordFound)
{
    if (wordFound)
    {
        cout << "Word is spelled correctly." << endl;
    }
    else if (suggestions.empty())
    {
        cout << "No suggestions found." << endl;
    }
    else
    {
        cout << "Did you mean: ";
        for (int i = 0; i < suggestions.size() - 1; i++)
        {
            cout << suggestions[i] << ", ";
        }
        cout << suggestions[suggestions.size() - 1] << "?" << endl;
    }
}

//https://en.wikipedia.org/wiki/Levenshtein_distance
size_t BKTree::levenshteinDistance(string w1, string w2)
{
    if (w1.length() == 0)
        return w2.length();
    if (w2.length() == 0)
        return w1.length();
    
    size_t n_w1 = w1.length();
    size_t n_w2 = w2.length();
    int cost;
    
    int d[n_w1 + 1][n_w2 + 1];
    
    for (int i = 0; i <= n_w1; i++)
        d[i][0] = i;
    for (int i = 0; i <= n_w2; i++)
        d[0][i] = i;
    
    for (int i = 1; i <= n_w1; i++)
    {
        for (int j = 1; j <= n_w2; j++)
        {
            
            cost = (w1[i - 1] == w2[j - 1]) ? 0 : 1;
            
            d[i][j] = min(d[i - 1][j] + 1,
                          d[i][j - 1] + 1,
                          d[i - 1][j - 1] + cost);
        }
    }
    
    return d[n_w1][n_w2];
}

int BKTree::min(int a, int b, int c)
{
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    
    return min;
}

void BKTree::cleanString(basic_string<char>& s)
{
    for (basic_string<char>::iterator p = s.begin();
         p != s.end(); ++p)
    {
        *p = tolower(*p);
    }
}