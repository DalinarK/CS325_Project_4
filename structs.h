#include <vector>
using std::vector;


struct neighbors{
	int neighborName;
	int distance;
	struct vertexStruct *neighborAddress;
};

struct vertexStruct{
	int vertexName;
	int xCoord;
	int yCoord;
	bool visted;
	vector <neighbors *> neighborDistance;
};
