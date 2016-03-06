#ifndef graph_h
#define graph_h

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::istringstream;

enum phase {scan, execute};
enum status {dead, alive};

struct neighbors{
	int neighborName;
	int distance;
};

struct vertexStruct{
	int vertexName;
	int xCoord;
	int yCoord;
	vector <neighbors *> neighborDistance;
};


class graph
{
private:
	vector <vertexStruct*> vertexGraph;

public:

	graph();

	// reads in a text file and converts it to a graph
	void createGraph(string inputFile);

	// calculates the distances to all the neighbors.
	void calculateDistances();

	// get
	int getSize();

	};


#endif
