/*
 * RoutingGraph.h
 *
 *  Created on: May 7, 2020
 *      Author: AD
 */
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
#include "ComponentPin.h"
#include "FunctionHeaderFile.h"


#ifndef ROUTINGGRAPH_H   /* ROUTINGGRAPH_H */
#define ROUTINGGRAPH_H
using namespace CustomAlgorithms_AD;
//**********************************************
namespace CustomAlgorithms_AD
{
	template<typename  PinDataType>class PinComponent;
	template<typename PinDataType>class CustomGraph;

	template <typename PinDataType>
	class RoutingGraph
	{
		friend class PinComponent<PinDataType>;
		friend class CustomGraph<PinDataType>;

	public:
		RoutingGraph();
		~RoutingGraph();

		int AddComponentPinFrontofLine(PinDataType, int);
		int AddComponentPinBackofLine(PinDataType, int);

		bool removeFromFront(PinDataType*, int*);
		bool removeFromBack(PinDataType*, int*);

		bool isEmpty() const;
		void printWireList() const;
		void printWireListReverseDirection() const;
		int DataAtPinIndexStartingZero(int, PinDataType*, int*);
		int SortList(int);


	private:
		PinComponent<PinDataType>* firstPtr;
		PinComponent<PinDataType>* lastPtr;
		PinComponent<PinDataType>* getNewPinNode(PinDataType, int);
	};

	//**********************************************
	template <typename PinDataType>
	RoutingGraph<PinDataType>::RoutingGraph() :firstPtr(0), lastPtr(0)
	{
		// empty body, end list constructor
	}
	//**********************************************
	template <typename PinDataType>
	RoutingGraph<PinDataType>::~RoutingGraph()
	{
		// empty body, end list constructor
	}
	//**********************************************
	template <typename PinDataType>
	int RoutingGraph<PinDataType>::AddComponentPinFrontofLine(PinDataType pinName, int data)
	{
		PinComponent<PinDataType>* newpinptr = getNewPinNode(pinName, data);

		if (isEmpty())
			this->firstPtr = this->lastPtr = newpinptr;
		else
		{
			newpinptr->nextPtr = this->firstPtr;
			this->firstPtr = newpinptr;  // curent pointer
		}
		return 0;
	}
	//**********************************************
	template <typename PinDataType>
	int RoutingGraph<PinDataType>::AddComponentPinBackofLine(PinDataType pinName, int data)
	{
		PinComponent<PinDataType>* newpinptr = getNewPinNode(pinName, data);

		if (isEmpty())
			this->firstPtr = this->lastPtr = newpinptr;
		else
		{
			newpinptr->previousPtr = this->lastPtr;
			this->lastPtr->nextPtr = newpinptr;  // curent pointer
			this->lastPtr = newpinptr;
		}

		return 0;
	}
	//**********************************************
	template <typename PinDataType>
	bool RoutingGraph<PinDataType>::removeFromFront(PinDataType* pinNameVariable, int* weight)
	{
		PinComponent<PinDataType>* removePtr;
		removePtr = this->firstPtr;

		if (isEmpty())
			return false;
		else if (this->firstPtr == this->lastPtr)
		{
			this->firstPtr = this->lastPtr = 0;
		}
		else
		{
			this->firstPtr->previousPtr = this->firstPtr;
			this->firstPtr = this->firstPtr->nextPtr;
		}
		*pinNameVariable = removePtr->pinInformation;
		*weight = removePtr->pinDataVariable;
		delete removePtr;
		return true;
	}
	//**********************************************
	template <typename PinDataType>
	bool RoutingGraph<PinDataType>::removeFromBack(PinDataType* pinNameVariable, int* weight)
	{
		PinComponent<PinDataType>* removePtr;
		removePtr = this->lastPtr;

		if (isEmpty())
			return false;
		else if (this->firstPtr == this->lastPtr)
		{
			this->firstPtr = this->lastPtr = 0;
		}
		else
		{
			PinComponent<PinDataType>* currentPtr;
			currentPtr = this->firstPtr;

			while (currentPtr->nextPtr != this->lastPtr)
			{
				if (currentPtr == this->lastPtr)
					currentPtr->previousPtr = currentPtr;

				currentPtr = currentPtr->nextPtr;
			}

			this->lastPtr = currentPtr;
			currentPtr->nextPtr = 0;

		}
		*pinNameVariable = removePtr->pinInformation;
		*weight = removePtr->pinDataVariable;
		delete removePtr;
		return true;
	}
	//**********************************************
	template <typename PinDataType>
	bool RoutingGraph<PinDataType>::isEmpty() const
	{
		if (this->firstPtr == 0)
			return true;
		else
			return false;
	}
	//**********************************************
	template <typename PinDataType>
	void RoutingGraph<PinDataType>::printWireList() const
	{
		if (isEmpty())
			cout << " \n List is empty " << endl;

		PinComponent<PinDataType>* currentPtr;
		currentPtr = this->firstPtr;
		while (currentPtr != this->lastPtr->nextPtr)
		{
			cout << " Pin Name is " << currentPtr->pinInformation << " pin Data is " << currentPtr->pinDataVariable << endl;
			currentPtr = currentPtr->nextPtr;
	    }
	}
	//**********************************************
	template <typename PinDataType>
	void RoutingGraph<PinDataType>::printWireListReverseDirection() const
	{
		if (isEmpty())
			cout << " \n List is empty " << endl;

		PinComponent<PinDataType>* currentPtr;
		currentPtr = this->lastPtr;
		while (currentPtr!= 0)
		{
	
			cout << " Pin Name is " << currentPtr->pinInformation << " pin Data is " << currentPtr->pinDataVariable << endl;
			currentPtr = currentPtr->previousPtr;
		}
	}
	//**********************************************
	template <typename PinDataType>
	int RoutingGraph<PinDataType>::DataAtPinIndexStartingZero(int index, PinDataType* pinName, int* data)
	{
		int iterator = 0;

		PinComponent<PinDataType>* currentPtr;
		currentPtr = this->firstPtr;

		if (index == 0)
		{
			*pinName = currentPtr->pinInformation;
			*data = currentPtr->pinDataVariable;
		}
		else
		{
			while (iterator != index) // start at 0
			{
				currentPtr = currentPtr->nextPtr;
				iterator++;
			}
			*pinName = currentPtr->pinInformation;
			*data = currentPtr->pinDataVariable;
		}
		return 0;
	}

	//*********************************************
	template <typename PinDataType>
	PinComponent<PinDataType>* RoutingGraph<PinDataType>::getNewPinNode(PinDataType pinName, int data)
	{
		PinComponent<PinDataType>* pin = new PinComponent<PinDataType>(pinName, data);

		return pin;
	}

	//*********************************************

	template <typename PinDataType>
	int RoutingGraph<PinDataType>::SortList(int numberPins)
	{
		int temporarykey;
		PinDataType tempKeypininformation;

		PinComponent<PinDataType>* IPtr;
		IPtr = this->firstPtr;

		PinComponent<PinDataType>* JPtr;
		JPtr = this->firstPtr->nextPtr;

			for (int j = 1; j < numberPins; j++)
				{
					temporarykey = JPtr->pinDataVariable;
					tempKeypininformation = JPtr->pinInformation;

					IPtr = JPtr->previousPtr;
		
					while (IPtr!=0 && IPtr->pinDataVariable > temporarykey)
					{	
						JPtr->pinDataVariable = IPtr->pinDataVariable;
						JPtr->pinInformation = IPtr->pinInformation;

						if(IPtr->previousPtr!=0)
						IPtr = IPtr->previousPtr;
					}
					IPtr->nextPtr->pinDataVariable = temporarykey;
					IPtr->nextPtr->pinInformation = tempKeypininformation;

					if(JPtr->nextPtr!=0)
					JPtr = JPtr->nextPtr;
				}		


		return 0;
   }
 } 
	//*********************************************
#endif  /* ROUTINGGRAPH_H */