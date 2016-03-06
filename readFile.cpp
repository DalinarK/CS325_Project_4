#include "fileIO.h"

struct vertexStruct{
	int vertex;
	int xCoord;
	int yCoord;
	vector <int> neighborDistance;
};

fileIO::fileIO()
{
	vector <vertexStruct> vertexGraph;
}

fileIO::~fileIO()


vector <vertexStruct createGraph(string fileName)
{
	printf("Reading filename %s \n", fileName);
}