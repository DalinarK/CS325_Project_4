#include <vector>
using std::vector;


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
