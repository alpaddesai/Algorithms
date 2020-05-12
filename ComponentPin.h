/*
 * ComponentPin.h
 *
 *  Created on: May 7, 2020
 *      Author: AD
 */
#include <iostream>
#include <string>
using std::ostream;
using std::endl;


#ifndef COMPONENTPIN_H_
#define COMPONENTPIN_H_

namespace CustomAlgorithms_AD
{
	//*************************************************************/
	template<typename  PinDataType>class RoutingGraph;  
	
	template<typename  PinDataType>
   class PinComponent
	{
	   friend ostream &operator<<(ostream &, const PinComponent<PinDataType> &);
	   friend class RoutingGraph<PinDataType>;          

	protected:
		PinComponent<PinDataType>(const PinDataType&, int);  
		PinDataType getPinData() const;              
		~PinComponent();                            

	private:
		PinComponent<PinDataType>* nextPtr;        
		PinComponent<PinDataType>* previousPtr;
		PinDataType pinInformation;
		int pinDataVariable;
	};

	//*************************************************************/
	template<typename PinDataType>			         
	PinComponent<PinDataType>::PinComponent(const PinDataType &pinInformation, int data)   
	{
		this->pinDataVariable = data;
		this->nextPtr = 0;
		this->previousPtr = 0;
		this->pinInformation = pinInformation;
	}

	//*************************************************************/
	template<typename PinDataType>			          	
	PinComponent<PinDataType>::~PinComponent()
	{

	}
	//*************************************************************/
	template<typename PinDataType>						    
	PinDataType PinComponent<PinDataType>::getPinData() const  
	{
		return this->pinDataVariable;
	}
	//*************************************************************
	template<typename PinDataType>						   
	ostream& operator <<(ostream& output, const PinComponent<PinDataType> &pinComponentObject)
	{
		output << " Pin Information " << pinComponentObject.pinInformation << " Parasitic Value " << pinComponentObject.pinDataVariable <<endl;
		return output;
	}
	//*************************************************************/
}

#endif /* COMPONENTPIN_H_ */
