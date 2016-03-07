#include <vector>
using std::vector;

struct vertexStruct;

struct neighbors{
	int neighborName;
	int distance;
	vertexStruct *neighborAddress;
};

struct vertexStruct{
	int vertexName;
	int xCoord;
	int yCoord;
	bool visited;
	vector <neighbors *> neighborDistance;

};

// Used to hold mergesort places
struct MergePosInfo
{
    int left;
    int mid;
    int right;
};

