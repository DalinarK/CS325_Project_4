
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

	//used to store the nearest vertex distance found so far in the
	//get minSpanningTree algorithm
	//primComp is also set in the makeNaiveTour method and stores the
	//indexes the struct is stored at
	//primComp is used in the performHeuristicThreeOpt method
	int primComp;

	//used to store the nearest vertex pointer found so far in the
	//get minSpanningTree algorithm
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


#endif