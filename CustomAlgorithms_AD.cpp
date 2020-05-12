
/*
 * Custom Algorithms_AD
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


	//**************************************************
	int main()
	{
		cout << "*********************** CUSTOM ALGORITHMS BY ALPA D. DESAI ********************* " << endl;

		OptimalMSTAlgorithms();
		OptimalSPSTAlgorithms();
		NonWeightedSPST();
		huffmancodingalgorithmexample();     

		return 0;
	}

	//************************************************
