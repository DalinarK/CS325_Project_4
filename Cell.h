#ifndef Cell_h
#define Cell_h

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

enum phase {scan, execute};
enum status {dead, alive};

struct vertexStruct{
	int vertex;
	int xCoord;
	int yCoord;
	vector <int> neighborDistance;
};

class Cell
{
private:
	vector <vertexStruct> vertexGraph;

public:

	Cell();

	void createGraph(string inputFile);

	};


#endif
