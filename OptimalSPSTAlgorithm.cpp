
/*
 * OptimalSPSTAlgorithm.cpp
 *
 *  Created on: May 11, 2020
 *      Author: AD
 */

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

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
using std::ios;
using std::cerr;
using std::rand;
using std::exit;
using namespace CustomAlgorithms_AD;

//****************************************************************

int OptimalSPSTAlgorithms()
{
	cout << " ***************** Optimal SPST Algorithms *************** " << endl << endl;

	int numPins = 144;  //must update size of graph

	InputGraphData();

	CustomGraph<string> SimpleProjectGraph(numPins);

	ifstream netlistFile("netlistwrite.txt", ios::in);

	if (!netlistFile)
	{
		cerr << "File could not be opened" << endl;
		exit(1);
	}

	string pinName;
	int pinCLparasitics;
	int index;
	int pinIndex;

	while (netlistFile >> index >> pinName >> pinCLparasitics >> pinIndex)
	{
		SimpleProjectGraph.BuildGraph(index, pinName, pinCLparasitics, pinIndex);
	}
	cout << " *** GRAPH PRINT OUT CONNECTED PINS WITH RLC VALUES ***** " << endl;
//	SimpleProjectGraph.printGraph();
	cout << " ******************************************************* " << endl;

	cout << " *** TEST FUNCTIONS ***** " << endl;
	SimpleProjectGraph.VerifyMethods();
	cout << " ******************************************************* " << endl;

	time_point startTimer3 = system_clock::now();
	SimpleProjectGraph.DijkstraAlgorithm();
	time_point endTimer3 = system_clock::now();
	duration DijkstraAlgorithmTime = endTimer3 - startTimer3;
	cout << "Duration of Dijkstra Algorithm Time for " << numPins << " pins is " << DijkstraAlgorithmTime.count() << endl;
	cout << " Run time is O[V^2] " << endl;

	cout << " ******************************************************* " << endl;

	return 0; 
}

//***************************************************************************************************************************