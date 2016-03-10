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

	//calculates final tour distance and sets instance variable totalDistanceTraveled
	void calculateFinalTourDistance();

	void sortDistances();

	//returns a min spanning tree using Prims alogrithm E log(V) runtime
	std::map<vertexStruct*,vector<vertexStruct*>> getMinSpanningTree(vertexStruct *start);
	
	//return a vertex at the index
	vertexStruct* getVertex(int index);

	//generate a tour of the graph using preorder traversal of the minspanning tree
	void makeNaiveTour(int startVertex);
	
	//returns a pointer to the final tour
	vector <vertexStruct*>* getTour();	

	//calculate tour distance
	int getTourDistance();

	//run a 3-opt optimization on the final graph
	void performBruteThreeOpt();

	//run a heuristic 3-opt optimization on the final graph
	int performHeuristicThreeOpt();

	//run a heuristic 3-opt optimization on the final graph
	int performHeuristic1ThreeOpt();

	//run a heuristic 2-opt optimization on the final graph
	int performTwoOpt();

	//calculates distance between two vertices
	int distBetweenTwoVertexes(vertexStruct * first, vertexStruct * second);

	int calculateTDistance(vector<vertexStruct*> finalTour);
	bool verticeNotEqual(vertexStruct *a, vertexStruct *b, vertexStruct *c, vertexStruct *d, vertexStruct *e, vertexStruct *f);

};


#endif
