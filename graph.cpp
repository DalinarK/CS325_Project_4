#include "graph.h"


graph::graph()
{
	vector <vertexStruct*> vertexGraph;
	totalDistanceTraveled = 0;
}

// Returns true if lhs distance is < rhs distance.
static bool sortByDistance(const neighbors *lhs, const neighbors *rhs)
{return lhs->distance < rhs->distance; }

// This function takes in the name of a file to open and then reads the files and creates a graph out of the
// coordinates in the file.
void graph::createGraph(string inputFile)
{
	cout << "opening " << inputFile << endl;

	string readLine;

	ifstream inputStream;
	inputStream.open(inputFile);

	vertexStruct *newStruct;

	if(!inputStream.is_open())
    {
        cout << "The file could not be opened." << std::endl;
        inputStream.close();
        exit(1);
    }

    // got from http://www.cplusplus.com/forum/general/17771/
    while(getline(inputStream, readLine))
    {
    	newStruct = new vertexStruct;
    	// used to hold the name, xcoord and ycoord of each line.
    	vector <int> temporaryStore;

    	// Reads the line and parses it based on the space delimiter and puts the values into an int vector
    	istringstream ss(readLine);
    	while (ss)
    	{
    		string s;
    		int sConverted;
    		if (!getline( ss, s, ' ' )) 
    			break;			
			istringstream fStream(s);			
    		fStream >> sConverted;
    		temporaryStore.push_back(sConverted);
    	}
    	newStruct->vertexName = temporaryStore[0];
    	newStruct->xCoord = temporaryStore[1];
    	newStruct->yCoord = temporaryStore[2];	

    	// cout << "Pushing " <<  newStruct->vertex << " " << newStruct->xCoord << " " << newStruct->yCoord << endl;
    	vertexGraph.push_back(newStruct);	
    }
}

//calculates the distances from each vertex to all its neighbors *NOT INCLUDING ITSELF*
void graph::calculateDistances()
{
	neighbors *neighborPTR;

	int graphSize = vertexGraph.size();
	cout << "graph size is " << graphSize << endl;
	// For each vertex, this function will iterate through all the other vertexes
	for (int g = 0; g < graphSize; g++)
	{
		for (int i = 0; i < graphSize; i++)
		{
			neighborPTR = new neighbors;
			// Prevents the calculation of the vertexes distance from itself - which would be 0

				int xDiff = vertexGraph[g]->xCoord - vertexGraph[i]->xCoord;
				// cout << "xDiff is " << xDiff << endl;
				int yDiff = vertexGraph[g]->yCoord - vertexGraph[i]->yCoord;
				// cout<< "yDiff is " << yDiff << endl;
				int distance = round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
				// printf("Distance is %d \n", distance);
				if (distance != 0)
				{
					neighborPTR->neighborName = vertexGraph[i]->vertexName;
					neighborPTR->distance = distance;
					neighborPTR->neighborAddress = vertexGraph[i];
					// cout << "neighbor name is " << neighborPTR->neighborAddress->vertexName << endl;
					vertexGraph[g]->neighborDistance.push_back(neighborPTR);
					// cout << "distance from " << vertexGraph[g]->vertexName << " to " << vertexGraph[g]->neighborDistance[i]->neighborName << ": " << vertexGraph[g]->neighborDistance.back()->distance << endl;		
				}				 
		}
	} 

	// int graphElement = 40;
	// cout << "coord for: " << vertexGraph[graphElement]->vertexName << " " << vertexGraph[graphElement]->xCoord << ", " << vertexGraph[graphElement]->yCoord << endl;
	// for (int i = 0; i < vertexGraph[graphElement]->neighborDistance.size(); i++)
	// {
	// 	cout << "distance from " << vertexGraph[graphElement]->vertexName << " to " << vertexGraph[graphElement]->neighborDistance[i]->neighborName << ": " << vertexGraph[graphElement]->neighborDistance[i]->distance << endl;		

	// }

}


//will round to the nearest integer
int graph::round(double d)
{
	if(d > 0){
		return (int)floor(d + 0.5);
	}else{
		return (int)ceil(d - 0.5);
	}
}

int graph::getSize()
{

	return vertexGraph.size();
}

// Sorts the neighbor by using stl
void graph::sortDistances()
{
	int g = 0;

	for (int g = 0; g < vertexGraph.size(); g++)
	{
		cout << "Vertex:" << vertexGraph[g]->vertexName << " is now sorted" << endl;
		sort(vertexGraph[g]->neighborDistance.begin(), vertexGraph[g]->neighborDistance.end(), sortByDistance);
		
		//for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++){
		//	cout << "Neighbor name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " distance: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
		//}	
	}
}


// Sorts the neighbors by distance
void graph::mergeSortDistances()
{
	cout << "sorted distance: " << endl;

	// cout << "coord for: " << vertexGraph[g]->vertexName << " " << vertexGraph[g]->xCoord << ", " << vertexGraph[g]->yCoord << endl;
	// for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++)
	// {
	// 	cout << "distance from " << vertexGraph[g]->vertexName << " to " << vertexGraph[g]->neighborDistance[i]->neighborName << ": " << vertexGraph[g]->neighborDistance[i]->distance << endl;		

	// }

	// for every vertex, sort the neighbors list by distance
	for (int g = 0; g < vertexGraph.size(); g++)
	{
		int end = vertexGraph[g]->neighborDistance.size() -1;
		mergesort(vertexGraph[g]->neighborDistance, 0, end);
	}

	int g = 0;
	// for (int g = 0; g < vertexGraph.size(); g++)
	// {
	// 	cout << "base vertex" << vertexGraph[g]->vertexName << endl;
		for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++)
		{
			cout << "name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " value: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
		}
	// }

}
// got from https://www.hackerrank.com/ by searching for "mergesort c++"
void graph::mergesort(vector <neighbors *>& neighborvector, int start, int end)
{
	int mid = 0;
	if(start < end)
	{
		mid = (start + end)/2;
		mergesort(neighborvector, start, mid);
		mergesort(neighborvector, mid+1, end);
		merge(neighborvector, start, mid, end);
	}

}

void graph::merge(vector <neighbors *>& neighborvector, int start, int mid, int end) 
{
        vector <neighbors *> tempVector;
        tempVector.resize(vertexGraph[0]->neighborDistance.size());

        int l=start;
        int r=end;
        int m=mid+1;
        int k=l;

        while(l<=mid && m<=r)
        {
            if(neighborvector[l]->distance <= neighborvector[m]->distance)
            {
                tempVector[k++] = neighborvector[l++];
            }
            else
            {
                tempVector[k++] = neighborvector[m++];    
            }  
        }

       	while(l<=mid){
       		 tempVector[k++]=neighborvector[l++];
       	}        
        while(m<=r){
            tempVector[k++]=neighborvector[m++];         
        }

        for(int i1=start;i1<=end;i1++){
            neighborvector[i1]=tempVector[i1];
            // cout << neighborvector[i1]->distance << " ";
        }
    
}

void graph::test()
{
	cout << "test" << endl;
}

// Calculates the distance between two vertexes
void graph::calculateFinalTourDistance()
{
	for (int i = 1; i < finalTour.size(); i++)
	{
		int xDiff = finalTour[i-1]->xCoord - finalTour[i]->xCoord;
		// cout << "xDiff is " << xDiff << endl;
		int yDiff = finalTour[i-1]->yCoord - finalTour[i]->yCoord;
		// cout<< "yDiff is " << yDiff << endl;
		totalDistanceTraveled += round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	}
	cout << "total distance toured is " << totalDistanceTraveled << endl;	
}

// Saves the final tour to file
void graph::writeTourFile(string fileName)
{
	// creating the output file name
	cout << "writing to file ";
	string outputfileName = fileName.append(".tour");
	cout << outputfileName << endl;

	// http://www.cplusplus.com/doc/tutorial/files/
	ofstream myfile;
	myfile.open(outputfileName);
	myfile << totalDistanceTraveled << "\n";
	for(int i = 0; i < finalTour.size(); ++i){
		myfile << finalTour.at(i)->vertexName << "\n";
	}

}


/**********************************************************************
 *Method will calculate and return a list of vertices representing
 *the minimum spanning tree.
 **********************************************************************/
vertexStruct* graph::getVertex(int index){
	if(index >= 0 && index < vertexGraph.size()){
		return vertexGraph.at(index);
	}else{
		return NULL;
	}
}

/**********************************************************************
 *Method will calculate and return a list of vertices representing
 *the minimum spanning tree.
 *for Map reference https://cs50.harvard.edu/resources/cppreference.com/cppmap/all.html
 *Postconditions: Need to deallocate the memory returned in the min spanning tree
 **********************************************************************/
std::map<vertexStruct*,vector<vertexStruct*>> graph::getMinSpanningTree(vertexStruct *start)
{
	std::priority_queue<vertexStruct*, vector<vertexStruct*>> pq;
	cout << "Size of Vertex graph = " << vertexGraph.size() << endl;
	int unmarkedVertices = vertexGraph.size();
	std::map<vertexStruct*,vector<vertexStruct*>> minSpanTree;

	vertexStruct *temp;
	vertexStruct *cur;

	//intialize start vertex
	temp = cur =start;
	temp->primComp = std::numeric_limits<int>::max();

	//add the start vertex to the map
	vector<vertexStruct*> edgeList;
	minSpanTree.insert(make_pair(cur, edgeList));
	
	//set visted to false for all vertices
	//set primComp to the distance from the start vertex
	//add start neighbours to the priority queue
	for(int i = 0; i < start->neighborDistance.size(); ++i){
		temp = start->neighborDistance.at(i)->neighborAddress;			
		temp->visted = false;
		temp->primComp = start->neighborDistance.at(i)->distance;
		temp->parent = start;
		pq.push(temp);

		//add all vertices to the map
		vector<vertexStruct*> edgeList;
		minSpanTree.insert(make_pair(temp, edgeList));
	}

	//mark the start vertex		
	start->visted = true;
	start->parent = 0;
	start->primComp = 0;
	--unmarkedVertices;
	temp = start;

	//walk through all vertices and add them to the tree according to Prims
	//algorithm	
	while(unmarkedVertices > 0){	
		if(!pq.top()->visted){
			cur = temp = pq.top();
			pq.pop();
			cur->visted = true;								
			
			//add the edge to the parents edge list in the map		
			minSpanTree[cur->parent].push_back(cur);		
			
			--unmarkedVertices;	

			//need to look at curs neighbours and update the priority queue
			//if distance from temp to neighbour is smaller than current primComp then found a closer neighbour
			//so update primComp and parent and then push onto priority queue
			for(int i = 0; i < cur->neighborDistance.size(); ++i){
				temp = cur->neighborDistance.at(i)->neighborAddress;
				if(!temp->visted){					
					if(cur->neighborDistance.at(i)->distance < temp->primComp){
						temp->primComp = cur->neighborDistance.at(i)->distance;			
						temp->parent = cur;
						pq.push(temp);
					}
				}
			}
		}else{
			pq.pop();
		}
	}
	
	return minSpanTree;
}

/*********************************************************************************
**Return a reference to the final tour.
**********************************************************************************/
vector <vertexStruct*>* graph::getTour(){	
	return &finalTour;
}

/*********************************************************************************
**Method will use a depth first traversal to generate a final tour
**Once all vertices have been visited the last vertex will go 
**directly back to the start vertex.
*********************************************************************************/
void graph::makeNaiveTour(int startVertex){

	//make sure vertex graph is empty
	vertexGraph.empty();	

	vertexStruct *temp, *cur;
	temp = cur = getVertex(startVertex);

	//start at one to include the start vertex as umarked
	int unmarkedVertices = 1;
	cur->visted = false;

	std::map<vertexStruct*,vector<vertexStruct*>> minSpanningTree = getMinSpanningTree(cur);

	vector<vertexStruct*> vertexStack;

	//mark all vertices unvisited
	for(int i = 0; i < cur->neighborDistance.size(); ++i){
		temp = cur->neighborDistance.at(i)->neighborAddress;			
		temp->visted = false;
		++unmarkedVertices;
	}
	
	//add the start vertex to the vertex graph
	//mark cur as visited then push cur's edge list onto stack
	finalTour.push_back(cur);
	cur->visted = true;
	--unmarkedVertices;
	for(int i = 0; i < minSpanningTree[cur].size(); ++i){
		vertexStack.push_back(minSpanningTree[cur].at(i));
	}

	while(!vertexStack.empty()){
		//get first item in stack and then remove it
		temp = vertexStack.back();
		vertexStack.pop_back();

		//if temp has not been visited push it into the solution tour
		//mark it as visited and then push all of its unmarked edges
		//onto the stack
		if(!temp->visted){
			finalTour.push_back(temp);
			temp->visted = true;
			--unmarkedVertices;

			//now push all temps unmarked vertice onto stack
			for(int i = 0; i < minSpanningTree[temp].size(); ++i){
				if(!minSpanningTree[temp].at(i)->visted){
					vertexStack.push_back(minSpanningTree[temp].at(i));
				}
			}
		}
	}
}


/*********************************************************************************
**Method will calculate the distance traversed in the tour
*********************************************************************************/
int graph::getTourDistance(){

	int distance = 0;
	int yDiff, xDiff;

	for(int i = 0; i < finalTour.size() - 1; ++ i){
		xDiff = finalTour[i]->xCoord - finalTour[i + 1]->xCoord;
		
		yDiff = finalTour[i]->yCoord - finalTour[i + 1]->yCoord;
		
		distance += round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	}

	//now add the distance from last edge back to the start
	xDiff = finalTour[finalTour.size() - 1]->xCoord - finalTour[0]->xCoord;
		
	yDiff = finalTour[finalTour.size() - 1]->yCoord - finalTour[0]->yCoord;
		
	distance += round(sqrt(pow(xDiff,2) + pow(yDiff,2)));

	return distance;
}