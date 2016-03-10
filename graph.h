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

	// this is an intermediate vector holding the created MST used for the christofides
	vector <vertexStruct*> MST;

	// this is the subgraph of that only contains vertices odd degree
	vector <vertexStruct*> oddSubGraph;
	//This is the subgraph of the minimum weight matching tree
	vector <vertexStruct*> minimumWeight;

	// this is the combined subgraph and MST;
	vector <vertexStruct*> eulerTour;
	long int  totalDistanceTraveled;	

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

	//Calculates the distance between two vertices
	int distBetweenTwoVertexes(vertexStruct * first, vertexStruct * second);

	//returns a min spanning tree using Prims alogrithm E log(V) runtime
	std::map<vertexStruct*,vector<vertexStruct*>> getMinSpanningTree(vertexStruct *start);

	// converts the minSpanning tree created by getMinSpanningTree into a vector <vectorStruct*>
	void createEdgelist();

	// Creates the subraph of that only contains vertices odd degree
	void createOddDegreeSubGraph();

	// Creates a minimum-weight perfect matching subgraph of OddSubGraph
	void createMinMatching();

	// Combines the min-weight perfect matching graph with the MST 
	void combineMSTandMinMatch();
	
	// Calculates the euler tour
	void calculateEulerTour(int startVertex);
	//return a vertex at the index
	vertexStruct* getVertex(int index);

	//generate a tour of the graph using preorder travesal of the minspanning tree
	void makeNaiveTour(int startVertex, string graphName);
	
	//returns a pointer to the final tour
	vector <vertexStruct*>* getTour();	
	vector <vertexStruct*> getEulerTour(){return eulerTour;}

	//calculate tour distance
	int getTourDistance();
};


#endif
