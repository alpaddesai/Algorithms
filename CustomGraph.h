/*
 * CustomGraph.h
 *
 *  Created on: May 7, 2020
 *      Author: AD
 */
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;
using std::chrono::system_clock;

using duration = std::chrono::duration<double>;
using time_point = std::chrono::time_point<system_clock>;

#include "ComponentPin.h"
#include "RoutingGraph.h"
#include "FunctionHeaderFile.h"
int HeapSort(vector<int>&);



#ifndef CUSTOMGRAPH_H   /* CUSTOMGRAPH_H */
#define CUSTOMGRAPH_H
using namespace CustomAlgorithms_AD;

//**********************************************
namespace CustomAlgorithms_AD
{

	template<typename  PinDataType>class PinComponent;
	template<typename  PinDataType>class RoutingGraph;

	template <typename PinDataType>
	class CustomGraph
	{
		friend class RoutingGraph<PinDataType>;
		friend class PinComponent<PinDataType>;

	public:
		CustomGraph(int);
		~CustomGraph();
		int BuildGraph(int, PinDataType, int, int);
		int printGraph();
		int PrimAlgorithm();
		int DijkstraAlgorithm();
		static int VerifyMethods();
		static int minimumPinRLCNotVisitedMST(int[], bool[], int);
		static int minimumDistanceSPST(int[], bool[], int);
		static int extractMin(vector<int> heapArray,bool[]);

		int numPins = 144;
		string iteration = "benchmark";
	//	string iteration = "Multiple2";


	private:
		RoutingGraph<PinDataType> simpleGraph[144];  // must initialize the size of the graph
		int HeapifyArray[9][9];

	};

	//*************************************************************/
	template <typename PinDataType>
	CustomGraph<PinDataType>::CustomGraph(int numberofNodes)
	{
		this->numPins = numberofNodes;
	}
	//*************************************************************/
	template <typename PinDataType>
	CustomGraph<PinDataType>::~CustomGraph()
	{

	}
	//*************************************************************/
	template <typename PinDataType>
	int CustomGraph<PinDataType>::BuildGraph(int index, PinDataType pinInfo, int data, int pinIndex)
	{
		simpleGraph[index].AddComponentPinBackofLine(pinInfo, data);
		//this->HeapifyArray[index][pinIndex] = data;
		return 0;
	}


	//*************************************************************/
	template <typename PinDataType>
	int CustomGraph<PinDataType>::PrimAlgorithm()
	{
		cout << " \n \n *********** Prim Algorithm ************" << endl;

		int* MST = new int[this->numPins];
		int* Key = new int[this->numPins];
		bool* MstSetVisited = new bool[this->numPins];

		for (int i = 0; i < this->numPins; i++)
		{
			Key[i] = 100;
			MstSetVisited[i] = false;

		}

		Key[0] = 0;
		MST[0] = -1;

		for (int count = 0; count < this->numPins - 1; count++)  // unnecessary iterations due to the VxV matrix. Using a linked list doesn't necessary help you have to iterate through the nodes to find the connected node.
		{
			int minimumKeyVertex = CustomGraph::minimumPinRLCNotVisitedMST(Key, MstSetVisited, numPins); // visits every node connected, starting with the least weight one first.
			MstSetVisited[minimumKeyVertex] = true;

			for (int pinIndex = 0; pinIndex < this->numPins; pinIndex++)
			{
				PinDataType name;
				int comparisonData;
				simpleGraph[minimumKeyVertex].DataAtPinIndexStartingZero(pinIndex, &name, &comparisonData);

				if (comparisonData != 0)
				{
					if (MstSetVisited[pinIndex] == false && comparisonData < Key[pinIndex])
					{
						Key[pinIndex] = comparisonData;
						MST[pinIndex] = minimumKeyVertex;
					}
				}
			}
		}

		cout << "\n Edge included in MST RLC of the edge \n" << endl;

		int ValidateMST9NodesArray[9] = { 4,4,7,9,2,1,8,2 };
		int ValidateMST9NodesMultiple2Array[9] = {8,8,14,18,4,2,16,4};

		for (int i = 1; i < this->numPins; i++)
		{
			PinDataType name;
			int RLCparasitics = 0;

			simpleGraph[i].DataAtPinIndexStartingZero(MST[i], &name, &RLCparasitics);
			cout << MST[i] << "-" << i << "\t \t \t" << RLCparasitics << endl;



			if (this->numPins == 9)
			{
				if (iteration == "benchmark")
				{
					if (RLCparasitics != ValidateMST9NodesArray[i - 1])
						cout << " RLC MST PARASITICS ERROR in index " << i << endl;
				}
				else if (iteration == "Multiple2")
				{
					if (RLCparasitics != ValidateMST9NodesMultiple2Array[i - 1])
						cout << " RLC MST PARASITICS ERROR in index " << i << endl;
				}
			}

		}

		cout << " *********************************** " << endl;
		return 0;
	}
	//*************************************************************/
	template <typename PinDataType>
	int CustomGraph<PinDataType>::minimumPinRLCNotVisitedMST(int Key[], bool MstSet[], int numberPins)
	{
		int minimumRLCParasitic = 100;
		int minimumIndex = 0;

		for (int pin = 0; pin < numberPins; pin++)
		{
			if (MstSet[pin] == false && Key[pin] <= minimumRLCParasitic)
			{
				minimumRLCParasitic = Key[pin];
				minimumIndex = pin;
			}
		}
		return minimumIndex;
	}
	//*************************************************************/

	template <typename PinDataType>
	int CustomGraph<PinDataType>::minimumDistanceSPST(int Distance[], bool SptSet[], int numberPins)
	{
		int minimumDistance = 100;
		int minimumIndex = 0;

		for (int pin = 0; pin < numberPins; pin++)
		{
			if (SptSet[pin] == false && Distance[pin] <= minimumDistance)
			{
				minimumDistance = Distance[pin];
				minimumIndex = pin;
			}
		}
		return minimumIndex;
	}

	//*************************************************************/
	template <typename PinDataType>
	int CustomGraph<PinDataType>::DijkstraAlgorithm()   // This finds the shortest spanning tree which is different from the minimum spanning tree
	{
		cout << " \n \n *********** Dijkstra Algorithm ************" << endl;

		int* MinimumDistanceArray = new int[this->numPins];
		bool* SPTSetVisited = new bool[this->numPins];
		int* SPST = new int[this->numPins];

		for (int i = 0; i < this->numPins; i++)
		{
			MinimumDistanceArray[i] = 100;
			SPTSetVisited[i] = false;
		}

		SPST[0] = -1;
		MinimumDistanceArray[0] = 0;  // source is a specific node

		for (int count = 0; count < this->numPins - 1; count++)  // array index 0... 9
		{
			int IndexOfMinimumDistancePath = CustomGraph::minimumDistanceSPST(MinimumDistanceArray, SPTSetVisited, numPins);  // starting with 0
			SPTSetVisited[IndexOfMinimumDistancePath] = true;

			for (int pinIndex = 0; pinIndex < this->numPins; pinIndex++)  // within the array index pin index 0...9
			{
				PinDataType name;
				int comparisonData;
				simpleGraph[IndexOfMinimumDistancePath].DataAtPinIndexStartingZero(pinIndex, &name, &comparisonData);

				if ((comparisonData != 0) && (MinimumDistanceArray[IndexOfMinimumDistancePath] != 100))
				{
					if (SPTSetVisited[pinIndex] == false && (MinimumDistanceArray[IndexOfMinimumDistancePath] + comparisonData < MinimumDistanceArray[pinIndex]))
					{
						MinimumDistanceArray[pinIndex] = MinimumDistanceArray[IndexOfMinimumDistancePath] + comparisonData;
						SPST[pinIndex] = IndexOfMinimumDistancePath;
					}
				}
			}
		}

		cout << " Shortest Spanning Tree " << endl << endl << endl;
		cout << " Vertex \t Distance from Vertex \n" << endl;

		int ValidateMinimumDistance9NodesArray[9] = { 0,4,12,19,21,11,9,8,14 };
		int ValidateMinimumDistance9Nodes2MultiplesArray[9] = { 0,8,24,38,42,22,18,16,28 };


		for (int i = 0; i < this->numPins; i++)
		{
			cout << "  " << i << " \t \t " << MinimumDistanceArray[i] << endl;

			if (this->numPins == 9)
			{
				if (iteration == "benchmark")
				{
					if (MinimumDistanceArray[i] != ValidateMinimumDistance9NodesArray[i])
						cout << " SPST MINIMUM DISTANCE ERROR in index " << i << endl;
				}
				else if (iteration == "Multiple2")
				{
					if (MinimumDistanceArray[i] != ValidateMinimumDistance9Nodes2MultiplesArray[i])
						cout << " SPST MINIMUM DISTANCE ERROR in index " << i << endl;
				}
			}
		}


		int ValidateSPST9NodesArray[8] = { 4,8,7,10,2,1,8,2 };
		int ValidateSPST9NodesMultiple2Array[8] = { 8,16,14,20,4,2,16,4 };

		cout << " \n \n Edge included in SPST RLC of the edge \n" << endl;

		for (int i = 1; i < this->numPins; i++)
		{
			PinDataType name;
			int RLCparasitics = 0;

			simpleGraph[i].DataAtPinIndexStartingZero(SPST[i], &name, &RLCparasitics);
			cout << SPST[i] << "-" << i << "\t \t \t" << RLCparasitics << endl;

			if (this->numPins == 9)
			{
				if (iteration == "benchmark")
				{
					if (RLCparasitics != ValidateSPST9NodesArray[i - 1])
						cout << " RLC SPST PARASITICS ERROR in index " << i << endl;
				}
				else if (iteration == "Multiple2")
				{
					if (RLCparasitics != ValidateSPST9NodesMultiple2Array[i - 1])
						cout << " RLC SPST PARASITICS ERROR in index " << i << endl;
				}

			}

		}
		
	
		cout << " ******************************************************************** " << endl;
		return 0;
	}

	//*************************************************************/
	template <typename PinDataType>
	int CustomGraph<PinDataType>::printGraph()
	{
		for (int i = 0; i < this->numPins; i++)
		{
			cout << " Pin Index " << i << endl;
			simpleGraph[i].printWireList();
			cout << endl;
		}
		return 0;
	}


	//*************************************************************/
	template <typename PinDataType>
	int  CustomGraph<PinDataType>::VerifyMethods()
	{
		cout << "**************************************************************" << endl;

		cout << "\n Execute demo string " << endl;
		RoutingGraph<string> RoutingListA;

		RoutingListA.AddComponentPinBackofLine("PinO", 10);
		RoutingListA.AddComponentPinBackofLine("PinA", 10);
		RoutingListA.AddComponentPinBackofLine("PinB", 20);
		RoutingListA.AddComponentPinBackofLine("PinG", 70);
		RoutingListA.AddComponentPinBackofLine("PinE", 50);
		RoutingListA.AddComponentPinBackofLine("PinC", 30);
		RoutingListA.AddComponentPinBackofLine("PinD", 40);
		RoutingListA.AddComponentPinBackofLine("PinS", 60);
		RoutingListA.AddComponentPinBackofLine("PinH", 80);
		RoutingListA.AddComponentPinBackofLine("PinI", 10);

		RoutingListA.printWireList();

		cout << "\n Print  List reverse direction " << endl;
		RoutingListA.printWireListReverseDirection();

		cout << "\n SortList O(n^2)" << endl;
		RoutingListA.SortList(10);
		RoutingListA.printWireList();

		string pinName5;
		int data;
		RoutingListA.DataAtPinIndexStartingZero(5, &pinName5, &data);
		cout << "\n Pin name  at index 5 " << pinName5 << " Date value " << data << endl;

		string RemovePin;
		int dataRemovePin;

		for (int i = 0; i < 3; i++)
		{
			RoutingListA.removeFromFront(&RemovePin, &dataRemovePin);
			cout << " Pin name removed " << RemovePin << " Date value " << dataRemovePin << endl;
		}

		cout << " \n Print list after removing first 3 nodes from list \n" << endl;
		RoutingListA.printWireList();


		for (int i = 0; i < 3; i++)
		{
			RoutingListA.removeFromBack(&RemovePin, &dataRemovePin);
			cout << " Pin name removed " << RemovePin << " Date value " << dataRemovePin << endl;
		}

		cout << " \n Print list after removing last 3 nodes from list \n" << endl;
		RoutingListA.printWireList();

		cout << endl << endl;

		cout << "**************************************************************" << endl;
		RoutingGraph<double> RoutingListB;

		RoutingListB.AddComponentPinBackofLine(0.01, 10);
		RoutingListB.AddComponentPinBackofLine(0.02, 10);
		RoutingListB.AddComponentPinBackofLine(0.03, 20);
		RoutingListB.AddComponentPinBackofLine(0.04, 70);
		RoutingListB.AddComponentPinBackofLine(0.05, 50);
		RoutingListB.AddComponentPinBackofLine(0.06, 30);
		RoutingListB.AddComponentPinBackofLine(0.07, 40);
		RoutingListB.AddComponentPinBackofLine(0.08, 60);
		RoutingListB.AddComponentPinBackofLine(0.09, 80);
		RoutingListB.AddComponentPinBackofLine(0.10, 90);

		RoutingListB.printWireList();

		cout << "\n Print  List reverse direction " << endl;
		RoutingListB.printWireListReverseDirection();

		cout << "\n SortList" << endl;
		RoutingListB.SortList(10);
		RoutingListB.printWireList();


		double pinNamenode5;
		int data5;
		RoutingListB.DataAtPinIndexStartingZero(5, &pinNamenode5, &data5);
		cout << "\n Pin name  at index 5 " << pinNamenode5 << " Date value " << data5 << endl;

		double RemovePindoubledatatype;
		int dataRemovePindoubledatatype;

		for (int i = 0; i < 3; i++)
		{
			RoutingListB.removeFromFront(&RemovePindoubledatatype, &dataRemovePindoubledatatype);
			cout << " Pin name removed " << RemovePindoubledatatype << " Date value " << dataRemovePindoubledatatype << endl;
		}

		cout << " \n Print list after removing first 3 nodes from list \n" << endl;
		RoutingListB.printWireList();


		for (int i = 0; i < 3; i++)
		{
			RoutingListB.removeFromBack(&RemovePindoubledatatype, &dataRemovePindoubledatatype);
			cout << " Pin name removed " << RemovePindoubledatatype << " Date value " << dataRemovePindoubledatatype << endl;
		}

		cout << " \n Print list after removing last 3 nodes from list \n" << endl;
		RoutingListB.printWireList();

		
		cout << " \n ***************************************************** \n " << endl;
		cout << "\n Minimum Heapify O(nlogn) " << endl;
		vector<int> HeapSortArray{ 10,10,20,70,50,30,40,60,80,10 };
		HeapSort(HeapSortArray);
		cout << " \n ***************************************************** \n " << endl;

		return 0;
	}
	//*************************************************************/


	template <typename PinDataType>
	int CustomGraph<PinDataType>::extractMin(vector<int> HeapSortArray, bool[])
	{

			int minimumValue = HeapSort(HeapSortArray);

		return minimumValue;
	}


	//*************************************************************/


}

#endif  /* CUSTOMGRAPH_H */