#include "graph.h"


graph::graph()
{
	vector <vertexStruct*> vertexGraph;
	vector <vertexStruct*> MST;
	totalDistanceTraveled = 0;
}

// Returns true if lhs distance is < rhs distance.
static bool sortByDistance(const neighbors *lhs, const neighbors *rhs)
{return lhs->distance < rhs->distance; }

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

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
    		// cout << "'" << s << "' ";
    		s = trim(s);
    		// cout << "'" << s << "' ";
    		// cout << " length: " << s.length();
    		if (s.length() > 0)
    		{
				istringstream fStream(s);			
    			fStream >> sConverted;
				temporaryStore.push_back(sConverted);
    		}


    		
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
	long int xDiff;
	long int  yDiff;
	long int  distance;
	neighbors *neighborPTR;

	int graphSize = vertexGraph.size();
	cout << "graph size is: " << graphSize << endl;
	// For each vertex, this function will iterate through all the other vertexes
	for (int g = 0; g < graphSize; g++)
	{
		for (int i = 0; i < graphSize; i++)
		{
			neighborPTR = new neighbors;
			// Prevents the calculation of the vertexes distance from itself - which would be 0

				xDiff = vertexGraph[g]->xCoord - vertexGraph[i]->xCoord;
				// cout << "xDiff is " << xDiff << endl;
				yDiff = vertexGraph[g]->yCoord - vertexGraph[i]->yCoord;
				// cout<< "yDiff is " << yDiff << endl;
				distance = (int) round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
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

	// int graphElement = 2;
	// // cout << "coord for: " << vertexGraph[graphElement]->vertexName << " " << vertexGraph[graphElement]->xCoord << ", " << vertexGraph[graphElement]->yCoord << endl;
	// for (int i = 0; i < vertexGraph[graphElement]->neighborDistance.size(); i++)
	// {
	// 	cout << "distance from " << vertexGraph[graphElement]->vertexName << " to " << vertexGraph[graphElement]->neighborDistance[i]->neighborName << ": " << vertexGraph[graphElement]->neighborDistance[i]->distance << endl;		

	// }

}


//will round to the nearest integer
int graph::round(double d)
{
	return d + .5;
}

int graph::getSize()
{

	return vertexGraph.size();
}

// Sorts the neighbor by using stl
void graph::sortDistances()
{
	// int g = 1;

	for (unsigned int g = 0; g < vertexGraph.size(); g++)
	{
		cout << "Vertex:" << vertexGraph[g]->vertexName << " is now sorted" << endl;
		sort(vertexGraph[g]->neighborDistance.begin(), vertexGraph[g]->neighborDistance.end(), sortByDistance);
		
		// for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++){
		// 	cout << "Neighbor name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " distance: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
		// }	
	}

	cout << "finished sorting " << endl;
}

void graph::test()
{
	cout << "test" << endl;
}

// Calculates the distance between two vertexes
void graph::calculateFinalTourDistance()
{
	long int  yDiff;
	long int  xDiff;
	//calculate the distances between vertexes
	for (unsigned int i = 1; i < eulerTour.size(); i++)
	{
		xDiff = eulerTour[i-1]->xCoord - eulerTour[i]->xCoord;
		// cout << "xDiff is " << xDiff << endl;
		yDiff = eulerTour[i-1]->yCoord - eulerTour[i]->yCoord;
		// cout<< "yDiff is " << yDiff << endl;
		totalDistanceTraveled += round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	}

	int sizeofVector = eulerTour.size() -1;
	// calculate the distance from first to last vertex to complete tour
	xDiff = eulerTour[0]->xCoord - eulerTour[sizeofVector]->xCoord;
	yDiff = eulerTour[0]->yCoord - eulerTour[sizeofVector]->yCoord;
	
		totalDistanceTraveled += (int) round(sqrt(pow(xDiff,2) + pow(yDiff,2)));

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
	for(unsigned int i = 0; i < eulerTour.size(); ++i){
		myfile << eulerTour.at(i)->vertexName << "\n";
	}

}

void graph::createEdgelist()
{
}

void graph::createOddDegreeSubGraph()
{
	minSpanningTree = getMinSpanningTree(getVertex(0));

	// cout << "Initial MST " << endl;
	// for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter ){
	// 	cout << "\nEdge list for: " << map_iter->first->vertexName << endl;
	// 	for( std::size_t i = 0 ; i < map_iter->second.size() ; ++i ){
	// 		cout << "edge " << i << " = " << map_iter->second[i]->vertexName <<endl;
	// 	}
	// }

	for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter ){
		if ( map_iter->second.size()%2 != 0){
			oddSubGraph.push_back(map_iter->first);
		}
	}

}
void graph::createMinMatching()
{
	bool containsVertex;
	// Initialize oddsubgraph and set all visted locations to false
	// create an edgelist.
	// Make map with an edgeList and a vertex struct key
	for (unsigned int i = 0; i < oddSubGraph.size(); i++)
	{
		oddSubGraph[i]->visted = false;
		vector<vertexStruct*> edgeList;
		minimumWeight.insert(make_pair(oddSubGraph[i], edgeList));
	}

	// Loop through every vertex in odd subgraph
	// if a vertex has not been visited
	//  We go through that vertexes edgelist and find the closest neighber that is in the subgraph
	// and push it to the minimum weight edgelist.
	for (unsigned int i = 0; i < oddSubGraph.size(); i++)
	{
		if (!oddSubGraph[i]->visted)
		{ 
			// Iterate through vertex neighbor list.
			for(unsigned int x = 0; x < oddSubGraph[i]->neighborDistance.size(); x++)
			{
				// make sure that the neighbor exists in the oddsubgraph
				for (unsigned int j = 0; j < oddSubGraph.size(); j++)
				{
					if (oddSubGraph[j] == oddSubGraph[i]->neighborDistance[x]->neighborAddress)
					{
						containsVertex = true;
						break;
					}
				}


				if (containsVertex == true)
				{
					minimumWeight[oddSubGraph[i]].push_back(oddSubGraph[i]->neighborDistance.at(0)->neighborAddress);
					minimumWeight[oddSubGraph[i]->neighborDistance.at(0)->neighborAddress].push_back(oddSubGraph[i]);
					oddSubGraph[i]->visted = true;
					oddSubGraph[i]->neighborDistance.at(0)->neighborAddress->visted = true;
					break;
				}
				
			}
			
		}
	}
	// Take our minimum weight edges and push them into minimum weight spanning tree
}

void graph::combineMSTandMinMatch()
{
	// goal is combine the oddsubgraph with with remainingVertices

	// get minimumWeight
	for(auto map_iter = minimumWeight.cbegin() ; map_iter != minimumWeight.cend() ; ++map_iter ){
		// cout << "\nEdge list for: " << map_iter->first->vertexName << endl;
		for( std::size_t i = 0 ; i < map_iter->second.size() ; ++i ){
			minSpanningTree[map_iter->first].push_back(map_iter->second[i]);
			// cout << "edge " << i << " = " << map_iter->second[i]->vertexName <<endl;
		}
	}

		// for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter ){
		// cout << "\nEdge list for: " << map_iter->first->vertexName << endl;
		// for( std::size_t i = 0 ; i < map_iter->second.size() ; ++i ){
		// 	// minSpanningTree[minimumWeight[i]].push_back(map_iter->second[i]);
		// 	cout << "edge " << i << " = " << map_iter->second[i]->vertexName <<endl;
		// }
	// }
	// cout << endl;
}

void graph::calculateEulerTour(int index)
{
		//make sure vertex graph is empty
	eulerTour.clear();	


	
	vertexStruct *temp, *cur;
	temp = cur = vertexGraph.at(index);
	
	//start at one to include the start vertex as umarked
	int unmarkedVertices = minSpanningTree.size();

	cur->visted = false;

	vector<vertexStruct*> vertexStack;
	for(unsigned int i = 0; i < oddSubGraph.size(); ++i){		
		oddSubGraph[i]->visted = false;
	}

	// //mark all vertices unvisited
	for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter )
	{
		for( std::size_t i = 0 ; i < map_iter->second.size() ; ++i ){
			map_iter->second.at(i)->visted = false;
		}
	}

	// //add the start vertex to the vertex graph
	// //mark cur as visited then push cur's edge list onto stack
	eulerTour.push_back(cur);
	cur->visted = true;
	--unmarkedVertices;


	for( std::size_t i = 0 ; i < minSpanningTree[cur].size() ; ++i ){
		vertexStack.push_back(minSpanningTree[cur].at(i));
	}



	while(!vertexStack.empty()){
		//get first item in stack and then remove it
		temp = vertexStack.back();
		// cout << "visted " << temp->vertexName << endl;
		vertexStack.pop_back();

		//if temp has not been visited push it into the solution tour
		//mark it as visited and then push all of its unmarked edges
		//onto the stack		
		if(!temp->visted){
			eulerTour.push_back(temp);
			
			temp->visted = true;
			--unmarkedVertices;

			//now push all temps unmarked vertice onto stack
			for( std::size_t i = 0 ; i < minSpanningTree[temp].size() ; ++i ){
			vertexStack.push_back(minSpanningTree[temp].at(i));
			}

		}
	}
}
int graph::distBetweenTwoVertexes(vertexStruct * first, vertexStruct * second)
{
	
	long int xDiff = first->xCoord - second->xCoord;
	// cout << "xDiff is " << xDiff << endl;
	long int yDiff = first->yCoord - second->yCoord;
	// cout<< "yDiff is " << yDiff << endl;
	long int distance = (int) round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	// cout << "distance: " << distance << endl;
	return distance;
}

/**********************************************************************
 *Method will calculate and return a list of vertices representing
 *the minimum spanning tree.
 **********************************************************************/
vertexStruct* graph::getVertex(int index){
	if(index >= 0 && index < (int) vertexGraph.size()){
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
	for(unsigned int i = 0; i < start->neighborDistance.size(); ++i){
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
			// add the parent to the cur edge list
			minSpanTree[cur].push_back(cur->parent);		
			
			--unmarkedVertices;	

			//need to look at curs neighbours and update the priority queue
			//if distance from temp to neighbour is smaller than current primComp then found a closer neighbour
			//so update primComp and parent and then push onto priority queue
			for(unsigned int i = 0; i < cur->neighborDistance.size(); ++i){
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
void graph::makeNaiveTour(int startVertex, string graphName){

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
	for(unsigned int i = 0; i < cur->neighborDistance.size(); ++i){
		temp = cur->neighborDistance.at(i)->neighborAddress;			
		temp->visted = false;
		++unmarkedVertices;
	}
	
	//add the start vertex to the vertex graph
	//mark cur as visited then push cur's edge list onto stack
	finalTour.push_back(cur);
	cur->visted = true;
	--unmarkedVertices;
	for(unsigned int i = 0; i < minSpanningTree[cur].size(); ++i){
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
			for(unsigned int i = 0; i < minSpanningTree[temp].size(); ++i){
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

	for(unsigned int i = 0; i < eulerTour.size() - 1; ++ i){
		xDiff = eulerTour[i]->xCoord - eulerTour[i + 1]->xCoord;
		
		yDiff = eulerTour[i]->yCoord - eulerTour[i + 1]->yCoord;
		
		distance += round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	}

	//now add the distance from last edge back to the start
	xDiff = eulerTour[eulerTour.size() - 1]->xCoord - eulerTour[0]->xCoord;
		
	yDiff = eulerTour[eulerTour.size() - 1]->yCoord - eulerTour[0]->yCoord;
		
	distance += round(sqrt(pow(xDiff,2) + pow(yDiff,2)));

	totalDistanceTraveled = distance;
	return distance;
}
