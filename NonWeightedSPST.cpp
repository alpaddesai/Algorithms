
/*
 * NonWeightedSPST.cpp
 *
 *  Created on: May 11, 2020
 *      Author: AD
 */

#include "FunctionHeaderFile.h"

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <queue>

using std::list;
using std::queue;
using std::endl;
using std::cout;
using std::vector;

int NonWeightedSPST()
{
    cout << endl << endl << endl;

    cout << "\n ***************** Non Weighted SPST Algorithm *************** " << endl << endl;


    int MatrixGraph[5][5] = { {0,1,0,0,1}, {1,0,1,1,1}, {0,1,0,1,0}, {0,1,1,0,1}, {1,1,0,1,0} }; // matrix graph
    vector<int> AdjList[5]; // array of string

    AdjList[0].push_back(1);
    AdjList[0].push_back(4);
    AdjList[4].push_back(0);

    AdjList[1].push_back(2);
    AdjList[1].push_back(3);
    AdjList[1].push_back(4);

    AdjList[2].push_back(1);
    AdjList[3].push_back(1);
    AdjList[4].push_back(1);

    AdjList[2].push_back(3);
    AdjList[3].push_back(2);

    AdjList[3].push_back(4);
    AdjList[4].push_back(3);

    cout << "\n ** Print Adj List Graph ************* " << endl << endl;

    printGraph(AdjList, MatrixGraph);
    // algorithms Depth First Search Algorithm
    cout << "\n **  Breadth First Search ************* " << endl << endl;

    BreadthFirstSearch(AdjList, MatrixGraph, 0);
    BreadthFirstSearch(AdjList, MatrixGraph, 2);
    BreadthFirstSearch(AdjList, MatrixGraph, 1);
    BreadthFirstSearch(AdjList, MatrixGraph, 3);

    return 0;

}
//**************************************************************************
int printGraph(vector<int> graphB[5], int MatrixGraph[5][5])
{
    cout << endl << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << " Adj List Graph " << i << endl;

        for (auto x : graphB[i])
            cout << "-> " << x;

        cout << endl;
    }

    cout << "***** Graph Matrix Node **** " << endl;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << MatrixGraph[i][j];

        cout << endl;
    }

    return 0;
}
//**************************************************************
int BreadthFirstSearch(vector<int> graphB[5], int matrixgraph[5][5], int currentNode)
{
    bool* visited = new bool[5];
    for (int i = 0; i < 5; i++)
        visited[i] = false;

    // Create a queue for BFS 
    list<int> queue;

    // Mark the current node as visited and enqueue it 
    visited[currentNode] = true;
    queue.push_back(currentNode);

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it 
        currentNode = queue.front();
        cout << currentNode << " ";
        queue.pop_front();

        cout << " Graph Array Node  " << currentNode << endl;

        for (auto x : graphB[currentNode])
            cout << "-> " << x;

        cout << endl;
    }

    return 0;
}


//**************************************************************************