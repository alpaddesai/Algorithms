
/*
 * Huffman_Coding_Algorithm, most of this algorithm is referenced by an online source.
 *
 *  Created on: May 11, 2020
 *     
 */
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "FunctionHeaderFile.h"

using std::vector;
using std::iostream;
using std::string;
using std::unordered_map;
using std::priority_queue;
using std::endl;
using std::cout;
 

// *********************** A  Node ********************************************
struct NodeHuffman
{
    char Letter;
    int frequency;
    NodeHuffman* leftpointer, * rightpointer;
};

// *********************** Comparison ********************************************

struct comparison								
{
    bool operator()(NodeHuffman* left, NodeHuffman* right)
    {
        return left->frequency > right->frequency;         
    }
};

NodeHuffman* getNode(char, int, NodeHuffman*, NodeHuffman*);
int EncodeRecursive(NodeHuffman*, string, unordered_map<char, string>&);
int DecodeRecursive(NodeHuffman*, int&, string);

//*************************************************************************
int huffmancodingalgorithmexample()   
{
	cout << "************* Huffman Coding Algorithm **************" << endl; 
    string  HuffManCodeText = "Huffman coding is a data compression algorithm.";
    priority_queue < NodeHuffman*, vector<NodeHuffman*>, comparison> pQueue;  

    pQueue.push(getNode('Z', 2, nullptr, nullptr));
    pQueue.push(getNode('K', 7, nullptr, nullptr));
    pQueue.push(getNode('M', 24, nullptr, nullptr));
    pQueue.push(getNode('C', 32, nullptr, nullptr));
    pQueue.push(getNode('U', 37, nullptr, nullptr));
    pQueue.push(getNode('D', 42, nullptr, nullptr));
    pQueue.push(getNode('L', 42, nullptr, nullptr));
    pQueue.push(getNode('E', 120, nullptr, nullptr));

	while (pQueue.size() != 1)     
	{
		NodeHuffman* leftValue = pQueue.top();

		pQueue.pop();      

		NodeHuffman* rightValue = pQueue.top();

		pQueue.pop();      

		int sumValue = leftValue->frequency + rightValue->frequency;

		pQueue.push(getNode('\0', sumValue, leftValue, rightValue));   
	} 

	NodeHuffman* rootTreeNode = pQueue.top();

	unordered_map<char, string> huffmancode;

	EncodeRecursive(rootTreeNode, " ", huffmancode);

	cout << " Huffman codes are :\n " << '\n';

	for (auto element : huffmancode)
		cout << element.first << " " << element.second << '\n';

	cout << "\n original string was : \n " << HuffManCodeText << '\n';


	return 0;

}
//*********************************************************************************
//function to allocate a new tree node 
NodeHuffman* getNode(char Letter, int frequency, NodeHuffman* leftpointer, NodeHuffman* rightpointer)
{
	NodeHuffman* huffmantreenode = new NodeHuffman();

	huffmantreenode->Letter = Letter;             
	huffmantreenode->frequency = frequency;       
	huffmantreenode->leftpointer = leftpointer;   
	huffmantreenode->rightpointer = rightpointer; 

	return huffmantreenode;                       
}
//*********************************************************************************
int EncodeRecursive(NodeHuffman* treerootnode, string encodestring, unordered_map <char, string>& huffmancode)
{
	if (treerootnode == nullptr)
		return -1;

	
	if (!treerootnode->leftpointer && !treerootnode->rightpointer)  
		huffmancode[treerootnode->Letter] = encodestring;                  

	EncodeRecursive(treerootnode->leftpointer, encodestring + "0", huffmancode);
	EncodeRecursive(treerootnode->rightpointer, encodestring + "1", huffmancode);

	return 0;
}

//*********************************************************************************
int DecodeRecursive(NodeHuffman* treerootnode, int& index, string decodestring)   
{
	if (treerootnode == nullptr)      
		return 0;

	if (!treerootnode->leftpointer && !treerootnode->rightpointer)  
	{
		cout << treerootnode->Letter;
		return 0;
	}

	index++;

	if (decodestring[index] == '0')   
		DecodeRecursive(treerootnode->leftpointer, index, decodestring);    
	else
		DecodeRecursive(treerootnode->rightpointer, index, decodestring);    

	return 0;
}
//*********************************************************************************
