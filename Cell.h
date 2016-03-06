#ifndef graph_h
#define graph_h

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::istringstream;

enum phase {scan, execute};
enum status {dead, alive};

struct vertexStruct{
	int vertex;
	int xCoord;
	int yCoord;
	vector <int> neighborDistance;
};

class graph
{
private:
	vector <vertexStruct*> vertexGraph;

public:

	graph();

	void createGraph(string inputFile);

	int getSize();

	};


#endif
