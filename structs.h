
#ifndef STRUCTS_h
#define STRUCTS_h

#include <vector>
#include <memory>

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
	int primComp;
	vertexStruct *parent;
	vector <neighbors *> neighborDistance;

	/*Used in graph class to compare vertex structs
** taken from http://stackoverflow.com/questions/9178083/priority-queue-for-user-defined-types
** and http://stackoverflow.com/questions/1517854/priority-queue-comparison-for-pointers
*/
    friend bool operator<(const std::shared_ptr<vertexStruct> a, const std::shared_ptr<vertexStruct> b) {
        // return "true" if "p1" is ordered before "p2", for example:
        return a->primComp > b->primComp;
    }			
};

struct Person
{
    // Left out making a constructor for simplicity's sake.
    int name;
};


/*Used in graph class to store vertex struct edges*/
struct MinSpanEdge{
	vertexStruct *start;
	vertexStruct *end;

	MinSpanEdge(vertexStruct *s, vertexStruct *e){
		start = s;
		end = e;
	}
};





#endif