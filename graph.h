#ifndef graph_h
#define graph_h

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <list>
#include <numeric>
#include <random>
#include <algorithm>
#include <queue>
#include <limits>
#include <map>
#include <utility> 

//#include "mergesort.h"
#include "structs.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::ofstream;

enum phase {scan, execute};
enum status {dead, alive};


class graph
{
private:
	vector <vertexStruct*> vertexGraph;
	vector <vertexStruct*> finalTour;
	int totalDistanceTraveled;	

public:
	void test();

	graph();

	// reads in a text file and converts it to a graph
	void createGraph(string inputFile);

	// calculates the distances to all the neighbors.
	void calculateDistances();

	// Sorts the neighbors by distance
	void mergeSortDistances();

	// get
	int getSize();

	//added rounding method in standard C++ library.
	int round(double d);

	// uses custom implementation of mergesort to order the distances between a vertex and all it's neighbors
	void mergesort(vector <neighbors *>& neighborvector, int start, int end);
	void merge(vector <neighbors *>& neighborvector, int start, int mid, int end);

	void writeTourFile(string fileName);
	void calculateFinalTourDistance();

	void sortDistances();

	//returns a min spanning tree using Prims alogrithm E log(V) runtime
	std::map<vertexStruct*,vector<vertexStruct*>> getMinSpanningTree(vertexStruct *start);
	
	//return a vertex at the index
	vertexStruct* getVertex(int index);

	//generate a tour of the graph using preorder travesal of the minspanning tree
	void makeNaiveTour(int startVertex);
	
	//returns a pointer to the final tour
	vector <vertexStruct*>* getTour();	

	//calculate tour distance
	int getTourDistance();
};


#endif
