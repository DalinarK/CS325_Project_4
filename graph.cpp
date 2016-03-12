#include "graph.h"


graph::graph()
{
	vector <vertexStruct*> vertexGraph;
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
		for (int i = 0; i < (int)graphSize; i++)
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
	int g = 1;

	for (int g = 0; g < (int)vertexGraph.size(); g++)
	{
		//cout << "Vertex:" << vertexGraph[g]->vertexName << " is now sorted" << endl;
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
	totalDistanceTraveled = 0;
	long int  yDiff;
	long int  xDiff;
	//calculate the distances between vertexes
	for (int i = 1; i < (int)finalTour.size(); i++)
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

	//cout << "total distance toured is " << totalDistanceTraveled << endl;	
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
	for(int i = 0; i < (int)finalTour.size(); ++i){
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
	for (unsigned int g = 0; g < oddSubGraph.size(); g++)
	{
		cout << "Vertex:" << oddSubGraph[g]->vertexName << " is now sorted. Size is " << endl;
		sort(oddSubGraph[g]->neighborDistance.begin(), oddSubGraph[g]->neighborDistance.end(), sortByDistance);
		
		for (unsigned int i = 0; i < oddSubGraph[g]->neighborDistance.size(); i++){
			// cout << "Neighbor name: " << oddSubGraph[g]->neighborDistance[i]->neighborName << " distance: " << oddSubGraph[g]->neighborDistance[i]->distance << endl;
		}	
	} 

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
			//cout << "Vertex " << oddSubGraph[i]->vertexName << " has not been visited! Now marked as " << oddSubGraph[i]->visted << endl;

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
					//cout << "Vertex " << oddSubGraph[i]->neighborDistance[g]->neighborAddress->vertexName << " has not been visited! Now marked as " << oddSubGraph[i]->neighborDistance[g]->neighborAddress->visted << endl;
					// adding neighbors to the current vertex
					//cout << "edge " << minimumWeight.back()->vertexName << " = " << oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName <<endl;

					int distance;
					neighborPTR = new neighbors;
					neighborPTR->neighborName =  oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName;
					distance = distBetweenTwoVertexes (minimumWeight.back(), oddSubGraph[g]->neighborDistance[i]->neighborAddress);
					neighborPTR->distance = distance;
					neighborPTR->neighborAddress = oddSubGraph[g]->neighborDistance[i]->neighborAddress;
					minimumWeight.back()->neighborDistance.push_back(neighborPTR);
					//cout << "added neighbor "  << neighborPTR->neighborName << " to " << minimumWeight.back()->vertexName <<  " with distance " << distance << endl;
					
					// Add the second vertex to the minimumWeight vector
					// cout << "vertex " << minimumWeight.back()->vertexName << " joined with " << oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName << endl;
					vertexStructPTR = new vertexStruct;
					vertexStructPTR->vertexName = oddSubGraph[g]->neighborDistance[i]->neighborAddress->vertexName;
					vertexStructPTR->xCoord = oddSubGraph[g]->neighborDistance[i]->neighborAddress->xCoord;
					vertexStructPTR->yCoord = oddSubGraph[g]->neighborDistance[i]->neighborAddress->yCoord;
					// cout << "pushing second vertex " << vertexStructPTR->vertexName << " onto minimumWeight " << endl;
					minimumWeight.push_back(vertexStructPTR);

					// add the first vertex as a neighbor to the second vertex
					//cout << "reverse: added neighbor " <<  minimumWeight[minimumWeight.size()-2]->vertexName << " to " << minimumWeight.back()->vertexName << endl;
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
					//cout << MST[i]->vertexName << " matched. Combining edges with " << minimumWeight[g]->neighborDistance[j]->neighborName << endl;
					MST[i]->neighborDistance.push_back(minimumWeight[g]->neighborDistance[j]);
				}

			}
		}
	}

	for (unsigned int k = 0; k < MST.size(); k++)
	{
		for (unsigned int i = 0; i < MST.size(); i++)
		{
			for (unsigned int g = 0; g < MST[i]->neighborDistance.size(); g++)
			{
				if (MST[k]->vertexName == MST[i]->neighborDistance[g]->neighborName)
				{
					MST[i]->neighborDistance[g]->neighborAddress = MST[k];
					MST[i]->visted = false;
				}
			}
		}
	}

	for (unsigned int i = 0; i < MST.size(); i++)
	{
		cout << "Vertex " << MST[i]->vertexName << endl;
		for (unsigned int g = 0; g < MST[i]->neighborDistance.size(); g++)
		{
			cout << MST[i]->neighborDistance[g]->neighborName << endl;
		}
	}
}

void graph::calculateEulerTour(int startVertex)
{
	vector <vertexStruct*> vertexStack;	

	vertexStruct *temp, *cur, *current, *next;
	temp = cur = MST[startVertex];
	
	//start at one to include the start vertex as umarked
	int unmarkedVertices = MST.size();

	cur->visted = false;

	// // //mark all vertices unvisited
	// for(unsigned int i = 0; i < oddSubGraph.size(); ++i){		
	// 	oddSubGraph[i]->visted = false;
	// }

	// //add the start vertex to the vertex graph
	// //mark cur as visited then push cur's edge list onto stack
	vertexStack.push_back(cur);
	current = vertexStack.back();



	// create the initial tour
	while(current->neighborDistance.size() != 0)
	{
		// mark as visited
		cout << current->vertexName << " has been added to final" << endl;
		current->visted = true;
		// get neighbor
		next = vertexStack.back()->neighborDistance.back()->neighborAddress;
		// remove neighbor from list
		vertexStack.back()->neighborDistance.pop_back();
		// remove previous neighbor from list
		for (unsigned int i = 0; i < next->neighborDistance.size(); i ++)
		{
			
			if (next->neighborDistance[i]->neighborName == current->vertexName)
			{
				cout << "found " << current->vertexName << ". deleting now" << endl;
				cout << "neighbor " << next->vertexName << " size is " << next->neighborDistance.size() << endl;
				next->neighborDistance.erase(next->neighborDistance.begin()+ i);
				cout << " after " << next->neighborDistance.size() << endl;
				break;
			}
			
		}
		// Add the neighbor to teh final tour
		vertexStack.push_back(next);
		current = next;
	}

	cout << "intermeddiate tour currently is " << endl;
	for (unsigned int i = 0; i < vertexStack.size(); i++)
	{
		vertexStack[i]->visted = false;
		cout << vertexStack[i]->vertexName << " \t";
	}
	cout << endl;

	vertexStack.pop_back();

	for (unsigned int i = 0; i < vertexStack.size(); i++)
	{
	
		if (vertexStack[i]->visted == false)
		{
			finalTour.push_back(vertexStack[i]);
			vertexStack[i]->visted = true;
		}
		
	}


	cout << "final tour currently is " << endl;
	for (unsigned int i = 0; i < finalTour.size(); i++)
	{
		cout << finalTour[i]->vertexName << " \t";
	}
	cout << endl;

	for (unsigned int x = 0; x < MST.size(); x++)
	{
		if (MST[x]->visted == false)
		{
			for (unsigned int i =0; i < finalTour.size(); i++)
			{
				if (MST[x]->vertexName == finalTour[i]->vertexName)
				{
					if (MST[x]->visted != finalTour[i]->visted)
					{
						cout << "there was not a match!" << endl;
					}
				}

			}
		}
	}

// exit(0);

	cout << "size difference between final tour and MST " << MST.size() << " vs " << finalTour.size() << endl;
	for ( unsigned int x = 0; x < 30; x++){
		cout << MST.size() << " vs " << finalTour.size() << endl;
		// go through the vertexes and see if there are any neighbors left. If so create a tour and
		// add that tour to the final tour
		for (unsigned int i = 0; i < finalTour.size(); i++)
		{
			// cout << finalTour[i]->vertexName << " has " << finalTour[i]->neighborDistance.size() << " neighbors "<< endl;
			if (finalTour[i]->neighborDistance.size() > 0)
			{

				next = finalTour[i]->neighborDistance.back()->neighborAddress;
				// Remove neighbor from this list
				if (finalTour[i]->neighborDistance.back()->neighborAddress->visted == false){
					
					// cout << finalTour[i]->vertexName << " now has " << finalTour[i]->neighborDistance.size() << " neighbors "<< endl;
					cout << next->vertexName << " to added to final after " << finalTour[i]->vertexName << endl;
					next->visted = true;
					cout << "set to " << next->visted << endl;
					// insert into the graph
					std::vector<vertexStruct*>::iterator iter;
					iter = finalTour.begin() + i + 1;
					

					// remove finalTour[i] from the eighbor's from neighborDistance list
					for (unsigned int j = 0; j < next->neighborDistance.size(); j ++)
					{
						
						if (next->neighborDistance[j]->neighborName == next->vertexName)
						{
							cout << "neighbor" << next->vertexName << "has these neighbors" << endl;
							for(int l = 0; l < next->neighborDistance.size(); l ++)
							{
								cout << "neighbors for " << next->neighborDistance[l]->neighborName << endl;
							}
							// cout << "found " << current->vertexName << ". deleting now" << endl;
							next->neighborDistance.erase(next->neighborDistance.begin()+ j);
							// cout << " after " << next->neighborDistance.size() << endl;
							

							for(int l = 0; l < next->neighborDistance.size(); l ++)
							{
								cout << "after neighbors for " << next->neighborDistance[l]->neighborName<< endl;
							}

							break;
						}
					}
					finalTour.insert(iter, next);
					finalTour[i]->neighborDistance.pop_back();
				}
	
			}
		}

		for (unsigned int i = 0; i < finalTour.size(); i++)
		{
			// cout << finalTour[i]->vertexName << " \t";

			if (finalTour[i]->neighborDistance.size() > 0)
			{
				cout << finalTour[i]->vertexName << " neighbors " << endl;
				for (unsigned int j = 0; j < finalTour[i]->neighborDistance.size(); j ++)
				{
					cout << finalTour[i]->neighborDistance[j]->neighborName << " visit status " << finalTour[i]->neighborDistance[j]->neighborAddress->visted << endl;
				}
			}
		}

cout << "size difference between final tour and MST " << MST.size() << " vs " << finalTour.size() << endl;

	}
	exit(0);
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
	for(int i = 0; i < (int)start->neighborDistance.size(); ++i){
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
			for(int i = 0; i < (int)cur->neighborDistance.size(); ++i){
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
	
	//used to store the index where the vertex is stored in the final graph
	//will be used to set primComp in the vertexStruct
	int index = 0;
	//make sure final tour is empty	
	finalTour.clear();
	totalDistanceTraveled = 0;

	vertexStruct *temp, *cur;
	temp = cur = getVertex(startVertex);

	//start at one to include the start vertex as umarked
	int unmarkedVertices = 1;
	cur->visted = false;

	std::map<vertexStruct*,vector<vertexStruct*>> minSpanningTree = getMinSpanningTree(cur);

	vector<vertexStruct*> vertexStack;

	//mark all vertices unvisited
	for(int i = 0; i < (int)cur->neighborDistance.size(); ++i){
		temp = cur->neighborDistance.at(i)->neighborAddress;			
		temp->visted = false;
		++unmarkedVertices;
	}
	
	//add the start vertex to the vertex graph
	//mark cur as visited then push cur's edge list onto stack
	finalTour.push_back(cur);
	cur->primComp = index++;
	cur->visted = true;
	--unmarkedVertices;
	for(int i = 0; i < (int)minSpanningTree[cur].size(); ++i){
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
			temp->primComp = index++;
			temp->visted = true;
			--unmarkedVertices;

			//now push all temps unmarked vertice onto stack
			for(int i = 0; i < (int)minSpanningTree[temp].size(); ++i){
				if(!minSpanningTree[temp].at(i)->visted){
					vertexStack.push_back(minSpanningTree[temp].at(i));
				}
			}
		}
	}
}


/*********************************************************************************
**Method is a getter
*********************************************************************************/
int graph::getTourDistance(){

	return totalDistanceTraveled;
}

/*********************************************************************************
**Method will calculate the distance between two vertices
*********************************************************************************/
int graph::distBetweenTwoVertexes(vertexStruct * first, vertexStruct * second)
{

	long int xDiff = first->xCoord - second->xCoord;
	// cout << "xDiff is " << xDiff << endl;
	long int yDiff = first->yCoord - second->yCoord;
	// cout<< "yDiff is " << yDiff << endl;
	long int distance = (int) round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	//cout << "distance: " << distance << endl;
	return distance;
}


/*********************************************************************************************
**Method will optimize the grap using a 3-opt 
**Reference to help understand 3-opt https://www.kaggle.com/c/traveling-santa-problem/forums/t/3510/anyone-using-3-opt
**https://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html
**http://cs.stackexchange.com/questions/19808/how-does-the-3-opt-algorithm-for-tsp-work
**Function doesn't work
**********************************************************************************************/
bool graph::performHeuristicThreeOpt(){
	
	//store the current totalDistanceTraveled
	int distance = totalDistanceTraveled;

	//edgeOne:
	for (int vertexAIndex = 0; (vertexAIndex <= (int)finalTour.size() - 6) && (int)finalTour.size() > 6; vertexAIndex ++)
	{
		int edgeOneNumber = vertexAIndex / 2 + 1;

		int vertexBIndex = vertexAIndex + 1;

		vertexStruct *pointA = finalTour.at(vertexAIndex);
		vertexStruct *pointB = finalTour.at(vertexBIndex);

		double distanceAB = distBetweenTwoVertexes(pointA, pointB);


		//edgeTwo:
		for (int vertexCIndex = vertexAIndex + 2; vertexCIndex <= (int)finalTour.size() - 4 && equalsCloseBNeighbour(vertexCIndex, pointB); vertexCIndex ++)
		{
			int edgeTwoNumber = vertexCIndex / 2 + 1;
        
			int vertexDIndex = vertexCIndex + 1;
        
			vertexStruct *pointC = finalTour.at(vertexCIndex);
			vertexStruct *pointD = finalTour.at(vertexDIndex);
                
			double distanceCD = distBetweenTwoVertexes(pointC, pointD);
                			                        
			//edgeThree:
			for (int vertexEIndex = vertexCIndex + 2; vertexEIndex < (int)finalTour.size() - 1; vertexEIndex++)
			{
				int vertexFIndex = vertexEIndex + 1;
                
				vertexStruct *pointE = finalTour.at(vertexEIndex);
				vertexStruct *pointF = finalTour.at(vertexFIndex);
                
				double distanceEF = distBetweenTwoVertexes(pointE, pointF);
                
				double distanceABCDEF = distanceAB + distanceCD + distanceEF;
				double distanceAD = distBetweenTwoVertexes(pointA, pointD);
				double distanceEC = distBetweenTwoVertexes(pointE, pointC);
				double distanceBF = distBetweenTwoVertexes(pointB, pointF);
				double distanceADECBF = distanceAD + distanceEC + distanceBF;
                
				if (distanceADECBF < distanceABCDEF){

					//improvement so swap vertices	
					finalTour.at(vertexBIndex) = pointD;
					pointD->primComp = vertexBIndex;
					finalTour.at(vertexCIndex) = pointE;					
					pointE->primComp = vertexCIndex;
					finalTour.at(vertexDIndex) = pointC;
					pointC->primComp = vertexDIndex;
					finalTour.at(vertexEIndex) = pointB;	
					pointB->primComp = vertexEIndex;
					
					calculateFinalTourDistance();														

					//reset back to original tour
					if(distance < totalDistanceTraveled){

						totalDistanceTraveled = distance;
						finalTour.at(vertexBIndex) = pointB;
						pointB->primComp = vertexBIndex;
						finalTour.at(vertexCIndex) = pointC;					
						pointC->primComp = vertexCIndex;
						finalTour.at(vertexDIndex) = pointD;
						pointD->primComp = vertexDIndex;
						finalTour.at(vertexEIndex) = pointE;
						pointE->primComp = vertexEIndex;
					}else{
						//cout << "found one 3-opt" << "\t";
						return true;
					}

				}                        
			}
		}
	}
	return false;
}



/*********************************************************************************************
**Method will optimize the grap using 2-opt 
**Reference to help understand 3-opt https://www.kaggle.com/c/traveling-santa-problem/forums/t/3510/anyone-using-3-opt
**https://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html
**http://cs.stackexchange.com/questions/19808/how-does-the-3-opt-algorithm-for-tsp-work
**https://en.wikipedia.org/wiki/2-opt
**https://web.tuke.sk/fei-cit/butka/hop/htsp.pdf
**selecting an edge (c1, c2) and searching
**for another edge (pA, pB), completing a move only if
**dist(pA, pB) + dist(pC, pD) > dist(pA, pC) + dist(pB, pD).
**we can prune our search if dist(pA, pB) > dist(pB, pC) does not hold
**********************************************************************************************/
bool graph::performHeuristicTwoOpt( ){	
			
	//store the current totalDistanceTraveled
	int distance = totalDistanceTraveled;	

	int distanceAB, distanceCD;
	int distanceAC, distanceBD, distanceBC;

	int distanceABCD, distanceACBD;

	int vertexAIndex = 0, vertexBIndex = 0, vertexCIndex = 0, vertexDIndex = 0;

	vertexStruct *pointA = NULL, *pointB = NULL, *pointC = NULL, *pointD = NULL;

	//edgeOne:
	for (vertexAIndex = 0; (vertexAIndex <= (int)finalTour.size() - 4) && finalTour.size() > 4; vertexAIndex ++)
	{			
		vertexBIndex = vertexAIndex + 1;
		
		pointA = finalTour.at(vertexAIndex);
		pointB = finalTour.at(vertexBIndex);		
		//edgeTwo:
		for (int vertexCIndex = vertexAIndex + 2; vertexCIndex <= (int)finalTour.size() - 2 && 
			equalsCloseBNeighbour(vertexCIndex, pointB); vertexCIndex ++)
		{						
			int vertexDIndex = vertexCIndex + 1;
        				        
			pointC = finalTour.at(vertexCIndex);		
			pointD = finalTour.at(vertexDIndex);       

			distanceCD = distBetweenTwoVertexes(pointC, pointD);
			distanceAB = distBetweenTwoVertexes(pointA, pointB);			             									                
			distanceABCD = distanceAB + distanceCD;

			distanceAC = distBetweenTwoVertexes(pointA, pointC);
			distanceBD = distBetweenTwoVertexes(pointB, pointD);
			distanceBC = distBetweenTwoVertexes(pointB, pointC);
			distanceACBD = distanceAC + distanceBD;			
			
			if (distanceACBD < distanceABCD){
				//improvement so swap vertices	
				finalTour.at(vertexBIndex) = pointC;
				pointC->primComp = vertexBIndex;
				finalTour.at(vertexCIndex) = pointB;					
				pointB->primComp = vertexCIndex;				
				
				calculateFinalTourDistance();
								
				if (totalDistanceTraveled < distance) {
					//found improvement
					return true;	               
				}else{
					//go back
					//no improvement
					totalDistanceTraveled = distance;
					finalTour.at(vertexBIndex) = pointB;
					pointB->primComp = vertexBIndex;
					finalTour.at(vertexCIndex) = pointC;					
					pointC->primComp = vertexCIndex;
				}						
			}
		}
	}
	return false;
}

bool graph::equalsCloseBNeighbour(int vertexIndex, vertexStruct *pointB){
		
	int testSize = pointB->neighborDistance.size() < 1000 ? 20 : 5;

	for(int i =0; i < (int)pointB->neighborDistance.size() && i < testSize; ++i){
		if(finalTour.at(vertexIndex) == pointB->neighborDistance.at(i)->neighborAddress){
			return true;
		}
	}
	return false;
}




