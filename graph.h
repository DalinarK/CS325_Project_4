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

#include "mergesort.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::istringstream;

enum phase {scan, execute};
enum status {dead, alive};


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

	void mergesort(vector <neighbors *>& neighborvector, int start, int end);
	void merge(vector <neighbors *>& neighborvector, int start, int mid, int end);

	void sort();
	bool sortByDistance(const neighbors *lhs, const neighbors *rhs);
	bool sortTest(int &i, int &j);

	};


#endif
