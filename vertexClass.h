#ifndef vertexClass_h
#define vertexClass_h

#include <vector>

using std::vector;


class vertexClass
{
private:
	int vertex;
	int xCoord;
	int yCoord;
	vector <int> neighborDistance;

public:
	~vertexClass();
	vertexClass();
	
};

#endif