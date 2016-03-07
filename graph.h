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

#include "structs.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::istringstream;

enum phase {scan, execute};
enum status {dead, alive};
static bool sortByDistance(const neighbors *lhs, const neighbors *rhs);

class graph
{
private:
	vector <vertexStruct*> vertexGraph;

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

<<<<<<< HEAD
	//added rounding method in standard C++ library.
	int graph::round(double d);

=======
	// uses custom implementation of mergesort to order the distances between a vertex and all it's neighbors
>>>>>>> origin/master
	void mergesort(vector <neighbors *>& neighborvector, int start, int end);
	void merge(vector <neighbors *>& neighborvector, int start, int mid, int end);

	// uses stl sort to order the distances between a vertex and all it's neighbors
	void sortDistances();
};


#endif
