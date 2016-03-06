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

	vector<int> merge(vector<int> &vec,const vector<int>& left, const vector<int>& right);
	vector<int> merge_sort(vector<int>& vec);

	};


#endif
