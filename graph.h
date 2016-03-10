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

	//this is the first part of the christofide conversion. 
	vector <vertexStruct*> MSTVector;

	// this is an intermediate vector holding the created MST used for the christofides.
	// The difference between MST and MSTHolder is that if MST vertex A and B share an edge, both
	// list each other as neighbors while MSTVector does not.
	vector <vertexStruct*> MST;

	// this is the subgraph of that only contains vertices odd degree
	vector <vertexStruct*> oddSubGraph;
	//This is the subgraph of the minimum weight matching tree
	vector <vertexStruct*> minimumWeight;

	// this is the combined minimum weight matching and MST;
	vector <vertexStruct*> combinedMSTandMinMatch;

	//This is the euler tour of the combined minimum weight matching and MST
	vector <vertexStruct*> Euler;
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

	// converts the minSpanning tree created by getMinSpanningTree into vector form. Vertices are only listed as neighbors on one side
	// example: vertex a and b share an edge. Only vertex a lists b as a neighbor.
	void createMSTVector();
	// converts the minSpanning tree created by getMinSpanningTree into a vector <vectorStruct*>. Vertices are only listed as neighbors on one side
	// example: vertex a and b share an edge. Both vertex b and a list each other as neighbors.
	void createEdgelist();

	// Creates the subraph of that only contains vertices odd degree
	void createOddDegreeSubGraph();

	// Creates a minimum-weight perfect matching subgraph of OddSubGraph
	void createMinMatching();

	// Combines the min-weight perfect matching graph with the MST 
	void combineMSTandMinMatch();

	// Calculates a eulertour from the combined MSTandMinMatch graph
	void calculateEulerTour();
	
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
