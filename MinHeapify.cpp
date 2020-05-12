
/*
 *  MinHeapify.cpp
 *
 *  Created on: May 11, 2020
 *      Author: AD
 */


#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "ComponentPin.h"
#include "RoutingGraph.h"
#include "CustomGraph.h"
#include "FunctionHeaderFile.h"

using std::cout;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::ios;
using std::cerr;
using namespace CustomAlgorithms_AD;

int HeapSort(vector<int> &HeapSortArray)
{
	cout << "\n Execute Print Algorithm Prior to Heap Sort " << endl;
	ExecutePrintAlgorithm(HeapSortArray);
	ExecuteHeapSortAlgorithm(HeapSortArray);
	cout << "\n Execute Print Algorithm After Heap Sort " << endl;
	ExecutePrintAlgorithm(HeapSortArray);


	int sizeHeap = HeapSortArray.size();
	return HeapSortArray[sizeHeap-1];
}


int ExecuteHeapSortAlgorithm(vector<int> &arrayHeap)
{
		int heapsize = arrayHeap.size();

	for (int i = heapsize / 2 - 1; i >= 0; i--)
		MinHeapify(arrayHeap, heapsize, i);

	for (int i = heapsize - 1; i >= 0; i--)
	{
			
		int temp = arrayHeap.at(i);
		arrayHeap.at(i) = arrayHeap.at(0);
		arrayHeap.at(0) = temp;

		MinHeapify(arrayHeap, i, 0);
	}

	return 0;
}

//*******************************************************//
int MinHeapify(vector<int> &arrayHeap, int heapsize, int index)
{
	int indexWithSmallestValue = index;
	int leftindex = 2 * index + 1;
	int rightindex = 2 * index + 2;

	if (comparisonLessThanFunction(leftindex, heapsize) && comparisonLessThanFunction(arrayHeap[leftindex], arrayHeap[indexWithSmallestValue]))
		indexWithSmallestValue = leftindex;

	if (comparisonLessThanFunction(rightindex, heapsize) && comparisonLessThanFunction(arrayHeap[rightindex], arrayHeap[indexWithSmallestValue]))
		indexWithSmallestValue = rightindex;

	if (indexWithSmallestValue != index)       // index with largest value != index
	{
		int temp = arrayHeap.at(indexWithSmallestValue);
		arrayHeap.at(indexWithSmallestValue) = arrayHeap.at(index);
		arrayHeap.at(index) = temp;

		MinHeapify(arrayHeap, heapsize, indexWithSmallestValue);
	}

	return 0;
}

//*******************************************************//
bool comparisonLessThanFunction(int value1, int value2)
{
	if (value1 < value2)
		return true;
	else
		return false;
}

//*******************************************************//
int ExecutePrintAlgorithm(const vector<int> &arrayHeap)
{
	for (int k = 0; k < arrayHeap.size(); k++)
	{
		cout << arrayHeap.at(k) << "\n";
	}
	cout << "\n \n ";
	return 0;
}
//*******************************************************//