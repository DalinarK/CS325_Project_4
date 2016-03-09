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
#include <functional> 
#include <cctype>
#include <locale>

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

	// get
	int getSize();

	//added rounding method in standard C++ library.
	int round(double d);

	void writeTourFile(string fileName);
	void calculateFinalTourDistance();

	void sortDistances();

	int createmstEdgeList(std::map<vertexStruct*,vector<vertexStruct*>> minSpanningTree);

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
