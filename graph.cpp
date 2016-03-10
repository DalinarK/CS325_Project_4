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
	for (unsigned int i = 1; i < finalTour.size(); i++)
	{
		xDiff = finalTour[i-1]->xCoord - finalTour[i]->xCoord;
		// cout << "xDiff is " << xDiff << endl;
		yDiff = finalTour[i-1]->yCoord - finalTour[i]->yCoord;
		// cout<< "yDiff is " << yDiff << endl;
		totalDistanceTraveled += round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	}

	int sizeofVector = finalTour.size() -1;
	// calculate the distance from first to last vertex to complete tour
	xDiff = finalTour[0]->xCoord - finalTour[sizeofVector]->xCoord;
	yDiff = finalTour[0]->yCoord - finalTour[sizeofVector]->yCoord;
	
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
	for(unsigned int i = 0; i < finalTour.size(); ++i){
		myfile << finalTour.at(i)->vertexName << "\n";
	}

}

void graph::createEdgelist()
{
	vertexStruct *vertexStructPTR;
	neighbors *neighborPTR, *neighborneighborPTR;

	int g = 0;
	std::map<vertexStruct*,vector<vertexStruct*>> minSpanningTree = getMinSpanningTree(getVertex(0));

	// create the vector representing the MST. Neighbors are not added yet
	for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter ){
		// cout << "\nEdge list for: " << map_iter->first->vertexName << endl;
		// Create a vertex
		vertexStructPTR = new vertexStruct;
		vertexStructPTR->vertexName = map_iter->first->vertexName;
		vertexStructPTR->xCoord = map_iter->first->xCoord;
		vertexStructPTR->yCoord = map_iter->first->yCoord;
		MST.push_back(vertexStructPTR);
	}

	// add the neighbors
	for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter ){
	cout << "\nEdge list for: " << map_iter->first->vertexName << endl;
		for( std::size_t i = 0 ; i < map_iter->second.size() ; ++i ){
			// Add only the neighbors in the MST.

			cout << "edge " << map_iter->first->vertexName << " = " << map_iter->second[i]->vertexName <<endl;

			int distance;
			neighborPTR = new neighbors;
			neighborPTR->neighborName =  map_iter->second[i]->vertexName;
			distance = distBetweenTwoVertexes (map_iter->second[i], map_iter->first);
			neighborPTR->distance = distance;
			neighborPTR->neighborAddress = map_iter->second[i];
			MST[g]->neighborDistance.push_back(neighborPTR);
			cout << "added neighbor "  << neighborPTR->neighborName << " to " << MST[g]->vertexName << endl;
			
			// Go to the neighbors and add the current as their vertex to them as well.
			neighborneighborPTR = new neighbors;
			neighborneighborPTR->neighborName = MST[g]->vertexName;
			neighborneighborPTR->distance = distance;
			neighborneighborPTR->neighborAddress =  MST[g];
			MST[neighborPTR->neighborName]->neighborDistance.push_back(neighborneighborPTR);
			cout << "added reverse " << MST[g]->vertexName << " to " << neighborneighborPTR->neighborName << endl;
		}
		g++;
	}

	// Check to see if edges are all there
	for(unsigned int i = 0; i < MST.size(); i++){
		cout << "\nEdge list for: " << MST[i]->vertexName << endl;
		for( unsigned int g = 0; g < MST[i]->neighborDistance.size(); g++ ){
			cout << "edge " << MST[i]->vertexName << " = " << MST[i]->neighborDistance[g]->neighborName <<endl;
		}
	}
	cout << endl;
}

void graph::createOddDegreeSubGraph()
{
	vertexStruct *vertexStructPTR;

	
	for (unsigned int i = 0; i < MST.size(); i++)
	{
		if (MST[i]->neighborDistance.size()%2 != 0)
		{
			vertexStructPTR = new vertexStruct;
			cout << "Adding " << MST[i]->vertexName << " to OddDegreeSubGraph because it has " << MST[i]->neighborDistance.size() << " edges" << endl;
			vertexStructPTR->vertexName = MST[i]->vertexName;
			vertexStructPTR->xCoord = MST[i]->xCoord;
			vertexStructPTR->yCoord = MST[i]->yCoord;
			vertexStructPTR->visted = false;
			oddSubGraph.push_back(vertexStructPTR);
		}
	}

	long int xDiff;
	long int  yDiff;
	long int  distance;
	neighbors *neighborPTR;


	// Calculate the distances between all of the points
	int graphSize = oddSubGraph.size();
	// cout << "subgraph size is: " << graphSize << endl;
	// For each vertex, this function will iterate through all the other vertexes
	for (int g = 0; g < graphSize; g++)
	{
		// cout << "added vertex" << oddSubGraph[g]->vertexName << " x: " << oddSubGraph[g]->xCoord << " y: " << oddSubGraph[g]->yCoord << endl;

		// cout << "vertex " << oddSubGraph[g]->vertexName << " has " << oddSubGraph[g]->neighborDistance.size() << " neighbors " << endl;
		for (int i = 0; i < graphSize; i++)
		{
			neighborPTR = new neighbors;
			// Prevents the calculation of the vertexes distance from itself - which would be 0

				xDiff = oddSubGraph[g]->xCoord - oddSubGraph[i]->xCoord;
				// cout << "xDiff is " << xDiff << " " <<oddSubGraph[g]->xCoord  << " - " << oddSubGraph[i]->xCoord << endl;
				yDiff = oddSubGraph[g]->yCoord - oddSubGraph[i]->yCoord;
				// cout<< "yDiff is " << yDiff << endl;
				distance = (int) round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
				// cout << "Distance is " << distance << endl;
				if (distance != 0)
				{
					neighborPTR->neighborName = oddSubGraph[i]->vertexName;
					neighborPTR->distance = distance;
					neighborPTR->neighborAddress = oddSubGraph[i];
					// cout << "neighbor name is " << neighborPTR->neighborAddress->vertexName << endl;
					oddSubGraph[g]->neighborDistance.push_back(neighborPTR);
					// cout << "distance from " << oddSubGraph[g]->vertexName << " to " << oddSubGraph[g]->neighborDistance.back()->neighborName << ": " << oddSubGraph[g]->neighborDistance.back()->distance << endl;		
				}
				
		}
	}
	int g = 0;
	// Sort the distances between all the edges in the subgraph
	// for (unsigned int g = 0; g < oddSubGraph.size(); g++)
	// {
		cout << "Vertex:" << oddSubGraph[g]->vertexName << " is now sorted. Size is " << endl;
	// 	sort(oddSubGraph[g]->neighborDistance.begin(), oddSubGraph[g]->neighborDistance.end(), sortByDistance);
		
		for (unsigned int i = 0; i < oddSubGraph[g]->neighborDistance.size(); i++){
			cout << "Neighbor name: " << oddSubGraph[g]->neighborDistance[i]->neighborName << " distance: " << oddSubGraph[g]->neighborDistance[i]->distance << endl;
		}	
	// } 

	// int graphElement = 2;
	// // cout << "coord for: " << vertexGraph[graphElement]->vertexName << " " << vertexGraph[graphElement]->xCoord << ", " << vertexGraph[graphElement]->yCoord << endl;
	// for (unsigned int i = 0; i < oddSubGraph[graphElement]->neighborDistance.size(); i++)
	// {
	// 	cout << "distance from " << oddSubGraph[graphElement]->vertexName << " to " << oddSubGraph[graphElement]->neighborDistance[i]->neighborName << ": " << oddSubGraph[graphElement]->neighborDistance[i]->distance << endl;		

	// }
}

void graph::createMinMatching()
{
	vertexStruct *vertexStructPTR;
	neighbors *neighborPTR;

	//go through the entire list of vectors
	for (unsigned int i = 0; i < oddSubGraph.size(); i++)
	{
		// Find the first vertex that hasn't been visited yet
		if (oddSubGraph[i]->visted != true)
		{
			oddSubGraph[i]->visted = true;
			cout << "Vertex " << oddSubGraph[i]->vertexName << " has not been visited! Now marked as " << oddSubGraph[i]->visted << endl;

			vertexStructPTR = new vertexStruct;
			vertexStructPTR->vertexName = oddSubGraph[i]->vertexName;
			vertexStructPTR->xCoord = oddSubGraph[i]->xCoord;
			vertexStructPTR->yCoord = oddSubGraph[i]->yCoord;
			minimumWeight.push_back(vertexStructPTR);
			// Look through the rest of the vectors and find one that isn't visited yet. THe first one found
			// should be the lowest weight available because everything is sorted
			for (unsigned int g = 0; g < oddSubGraph[g]->neighborDistance.size(); g++)
			{

				if (oddSubGraph[i]->neighborDistance[g]->neighborAddress->visted != true)
				{
					oddSubGraph[i]->neighborDistance[g]->neighborAddress->visted = true;
					cout << "Vertex " << oddSubGraph[i]->neighborDistance[g]->neighborAddress->vertexName << " has not been visited! Now marked as " << oddSubGraph[i]->neighborDistance[g]->neighborAddress->visted << endl;
					// adding neighbors to the current vertex
					cout << "edge " << minimumWeight.back()->vertexName << " = " << oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName <<endl;

					int distance;
					neighborPTR = new neighbors;
					neighborPTR->neighborName =  oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName;
					distance = distBetweenTwoVertexes (minimumWeight.back(), oddSubGraph[g]->neighborDistance[i]->neighborAddress);
					neighborPTR->distance = distance;
					neighborPTR->neighborAddress = oddSubGraph[g]->neighborDistance[i]->neighborAddress;
					minimumWeight.back()->neighborDistance.push_back(neighborPTR);
					cout << "added neighbor "  << neighborPTR->neighborName << " to " << minimumWeight.back()->vertexName <<  " with distance " << distance << endl;
					
					// Add the second vertex to the minimumWeight vector
					// cout << "vertex " << minimumWeight.back()->vertexName << " joined with " << oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName << endl;
					vertexStructPTR = new vertexStruct;
					vertexStructPTR->vertexName = oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName;
					vertexStructPTR->xCoord = oddSubGraph[g]->neighborDistance[i]->neighborAddress->xCoord;
					vertexStructPTR->yCoord = oddSubGraph[g]->neighborDistance[i]->neighborAddress->yCoord;
					// cout << "pushing second vertex " << vertexStructPTR->vertexName << " onto minimumWeight " << endl;
					minimumWeight.push_back(vertexStructPTR);

					// add the first vertex as a neighbor to the second vertex
					cout << "reverse: added neighbor " <<  minimumWeight[minimumWeight.size()-2]->vertexName << " to " << minimumWeight.back()->vertexName << endl;
					neighborPTR = new neighbors;
					neighborPTR->neighborName = minimumWeight[minimumWeight.size()-2]->vertexName;
					neighborPTR->distance = distance;
					neighborPTR->neighborAddress = minimumWeight[minimumWeight.size()-2];
					minimumWeight.back()->neighborDistance.push_back(neighborPTR);
					// cout << "added neighbor "  << neighborPTR->neighborName << " to " << MST[g]->vertexName <<  " with distance " << distance << endl;
					break;
				}
			}
		}
	}

}

void graph::combineMSTandMinMatch()
{
	for (unsigned int i = 0; i < MST.size(); i++)
	{
		for (unsigned int g = 0; g < minimumWeight.size(); g++)
		{
			if (MST[i]->vertexName == minimumWeight[g]->vertexName)
			{
				
				for (unsigned int j = 0; j < minimumWeight[g]->neighborDistance.size(); j++)
				{ 
					cout << MST[i]->vertexName << " matched. Combining edges with " << minimumWeight[g]->neighborDistance[j]->neighborName << endl;
					MST[i]->neighborDistance.push_back(minimumWeight[g]->neighborDistance[j]);
				}

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

	for(unsigned int i = 0; i < finalTour.size() - 1; ++ i){
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
