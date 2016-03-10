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
	int g = 1;

	for (int g = 0; g < vertexGraph.size(); g++)
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
	for (int i = 1; i < finalTour.size(); i++)
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
	for(int i = 0; i < cur->neighborDistance.size(); ++i){
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
			temp->primComp = index++;
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
void graph::performBruteThreeOpt(){
	
	//store the current totalDistanceTraveled
	int distance = totalDistanceTraveled;

	//edgeOne:
	for (int vertexAIndex = 0; (vertexAIndex <= finalTour.size() - 6) && finalTour.size() > 6; vertexAIndex ++)
	{
		int edgeOneNumber = vertexAIndex / 2 + 1;

		int vertexBIndex = vertexAIndex + 1;

		vertexStruct *pointA = finalTour.at(vertexAIndex);
		vertexStruct *pointB = finalTour.at(vertexBIndex);

		double distanceAB = distBetweenTwoVertexes(pointA, pointB);


		//edgeTwo:
		for (int vertexCIndex = vertexAIndex + 2; vertexCIndex <= finalTour.size() - 4; vertexCIndex ++)
		{
			int edgeTwoNumber = vertexCIndex / 2 + 1;
        
			int vertexDIndex = vertexCIndex + 1;
        
			vertexStruct *pointC = finalTour.at(vertexCIndex);
			vertexStruct *pointD = finalTour.at(vertexDIndex);
                
			double distanceCD = distBetweenTwoVertexes(pointC, pointD);
                			                        
			//edgeThree:
			for (int vertexEIndex = vertexCIndex + 2; vertexEIndex < finalTour.size() - 1; vertexEIndex++)
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
						finalTour.at(vertexBIndex) = pointB;
						pointB->primComp = vertexBIndex;
						finalTour.at(vertexCIndex) = pointC;					
						pointC->primComp = vertexCIndex;
						finalTour.at(vertexDIndex) = pointD;
						pointD->primComp = vertexDIndex;
						finalTour.at(vertexEIndex) = pointE;
						pointE->primComp = vertexEIndex;
					}else{
						//cout << "found one brute" << "\t";
						return;
					}

				}                        
			}
		}
	}
}

/*********************************************************************************************
**Method will optimize the grap using a 3-opt 
**Reference to help understand 3-opt https://www.kaggle.com/c/traveling-santa-problem/forums/t/3510/anyone-using-3-opt
**https://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html
**http://cs.stackexchange.com/questions/19808/how-does-the-3-opt-algorithm-for-tsp-work
**Postcondition:  Method returns 1 if successful
**Heuristic make: A close to D and B close to F and C close to E
** Doesn't work
**********************************************************************************************/
int graph::performHeuristicThreeOpt(){
	
	if(finalTour.size() < 3){
		return 0;
	}

	//store the current totalDistanceTraveled
	int distance = totalDistanceTraveled;	

	int distanceAB, distanceCD, distanceEF;
	int distanceAD, distanceEC, distanceBF;
	int vertexAIndex, vertexBIndex, vertexCIndex, vertexDIndex, vertexEIndex, vertexFIndex;

	vertexStruct *pointA, *pointB, *pointC, *pointD, *pointE, *pointF;
	while(true){
		pointA = pointB = pointC = pointD = pointE = pointF = NULL;
		
		//*************************************************************edgeOne:
		//assign the indices to pointA and B
		int random = rand() % finalTour.size();
		vertexAIndex = random;	
		if(random < finalTour.size() -1){
			vertexBIndex = random +1;
		}else{
			vertexBIndex = random -1;
		}

		pointA = finalTour.at(vertexAIndex);
		pointB = finalTour.at(vertexBIndex);

		distanceAB = distBetweenTwoVertexes(pointA, pointB);

		//*************************************************************edgeTwo:					
		if(pointA->neighborDistance.size() > 1){
			//set D		
			for(int i = 0; i < pointA->neighborDistance.size(); ++i){
				if(pointA->neighborDistance.at(i)->neighborAddress != pointB){
					pointD = pointA->neighborDistance.at(i)->neighborAddress;						
					vertexDIndex = pointD->primComp;
					break;
				}
			}
			//set C
			for(int i = 0; i < pointA->neighborDistance.size(); ++i){
				if(pointA->neighborDistance.at(i)->neighborAddress != pointB && pointA->neighborDistance.at(i)->neighborAddress != pointD){
					pointC = pointA->neighborDistance.at(i)->neighborAddress;		
					vertexCIndex = pointC->primComp;
					break;
				}
			}

		}else if(pointB->neighborDistance.size() > 1){
			//set C
			for(int i = 0; i < pointB->neighborDistance.size(); ++i){
				if(pointB->neighborDistance.at(i)->neighborAddress != pointA){
					pointC = pointB->neighborDistance.at(i)->neighborAddress;
					vertexCIndex = pointC->primComp;
					break;
				}
			}
			//set D
			for(int i = 0; i < pointB->neighborDistance.size(); ++i){
				if(pointB->neighborDistance.at(i)->neighborAddress != pointB && pointB->neighborDistance.at(i)->neighborAddress != pointC){
					pointD = pointB->neighborDistance.at(i)->neighborAddress;						
					vertexDIndex = pointD->primComp;
					break;
				}
			}						
		}else{
			//try again
			cout << "continuing \t";
			continue;
		}
                
		distanceCD = distBetweenTwoVertexes(pointC, pointD);    

		//*************************************************************edgeThree:
		//set E
		if(pointC->neighborDistance.size() > 1){
			for(int i = 0; i < pointC->neighborDistance.size(); ++i){
				if(pointC->neighborDistance.at(i)->neighborAddress != pointA && pointC->neighborDistance.at(i)->neighborAddress != pointB &&
				   pointC->neighborDistance.at(i)->neighborAddress != pointD){
					pointE = pointC->neighborDistance.at(i)->neighborAddress;
					vertexEIndex = pointE->primComp;
				}
			}
			//set F
			for(int i = 0; i < pointC->neighborDistance.size(); ++i){
				if(pointC->neighborDistance.at(i)->neighborAddress != pointA && pointC->neighborDistance.at(i)->neighborAddress != pointB &&
				   pointC->neighborDistance.at(i)->neighborAddress != pointD && pointC->neighborDistance.at(i)->neighborAddress != pointE ){
					pointF = pointC->neighborDistance.at(i)->neighborAddress;						
					vertexFIndex = pointF->primComp;
				}
			}
			
		}else if(pointD->neighborDistance.size() > 1){
			for(int i = 0; i < pointD->neighborDistance.size(); ++i){
				if(pointD->neighborDistance.at(i)->neighborAddress != pointA && pointD->neighborDistance.at(i)->neighborAddress != pointB &&
				   pointD->neighborDistance.at(i)->neighborAddress != pointC){
					pointE = pointD->neighborDistance.at(i)->neighborAddress;
					vertexEIndex = pointE->primComp;
				}
			}
			//set F
			for(int i = 0; i < pointD->neighborDistance.size(); ++i){
				if(pointD->neighborDistance.at(i)->neighborAddress != pointA && pointD->neighborDistance.at(i)->neighborAddress != pointB &&
				   pointD->neighborDistance.at(i)->neighborAddress != pointC && pointD->neighborDistance.at(i)->neighborAddress != pointE ){
					pointF = pointD->neighborDistance.at(i)->neighborAddress;						
					vertexFIndex = pointF->primComp;
				}
			}
			
		//set e and f to c and d and perform 2-opt
		}else{
			cout << "continuing \t";
			continue;
		}
                
		distanceEF = distBetweenTwoVertexes(pointE, pointF);
    
		//calculate distance between three points            
		int distanceABCDEF = distanceAB + distanceCD + distanceEF;
	
		distanceAD = distBetweenTwoVertexes(pointA, pointD);
		distanceEC = distBetweenTwoVertexes(pointE, pointC);
		distanceBF = distBetweenTwoVertexes(pointB, pointF);

		//calculate distance between rearranged three points            
		int distanceADECBF = distanceAD + distanceEC + distanceBF;
                cout << "distanceADECBF = " << distanceADECBF << " distance ABCDEF = " << distanceABCDEF << endl;
		//look for improvement
		if (distanceADECBF < distanceABCDEF && verticeNotEqual(pointA, pointB, pointC, pointD, pointE, pointF)){
			cout << "distanceADECBF = " << distanceADECBF << " distance ABCDEF = " << distanceABCDEF << endl;
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
			//reset total distance back to original
			if(distance < totalDistanceTraveled){
				cout << "resetting ";
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
				//return 1 if successful
				//cout << "found one heur\t";
				return 1;
			}
		}
		cout << "nothing "<< verticeNotEqual(pointA, pointB, pointC, pointD, pointE, pointF) << "\t";
	}
	return 0;
}

	
/*********************************************************************************************
**Method will optimize the grap using 2-opt 
**Reference to help understand 3-opt https://www.kaggle.com/c/traveling-santa-problem/forums/t/3510/anyone-using-3-opt
**https://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html
**http://cs.stackexchange.com/questions/19808/how-does-the-3-opt-algorithm-for-tsp-work
**https://en.wikipedia.org/wiki/2-opt
**
**********************************************************************************************/
int graph::performTwoOpt(){	
	//repeat until no improvement is made {       
	//store the current totalDistanceTraveled
	int distance = totalDistanceTraveled;
	int new_distance = 0;
	

	for (int i = 0; i < finalTour.size() - 1; i++) {
        for (int k = i + 1; k < finalTour.size(); k++) {
			vector<vertexStruct*> tourMod;
			tourMod.clear();
			//perform the swap into tourMod
			for (int x =0; x < i; x++){			   
				tourMod.push_back(finalTour.at(x));
			}
			for (int x = k; x >= i; x--){			   
				tourMod.push_back(finalTour.at(x));
			}
			for (int x = k+1; x < finalTour.size(); x++){			   
				tourMod.push_back(finalTour.at(x));
			}               
               
			new_distance = calculateTDistance(tourMod);
			//cout << "tourMod size = "<< tourMod.size() << "final tour size = " << finalTour.size() << "distance = " << distance << "new distance is " << new_distance << "\t";
            if (new_distance < distance) {
				
				//cout << "found one 2opt" << "\t";
				totalDistanceTraveled = new_distance;
				//cout << "new distance is " << new_distance << "found improvement \t";
				finalTour.clear();
                for (int x =0; x < tourMod.size(); x++){			   
					tourMod.at(x)->primComp = x;
					finalTour.push_back(tourMod.at(x));
				}                   
			}
        }
    }
 
	return 0;
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
**dist(pA, pB) + dist(pC, pD) > dist(pA, pC) + dist(pB, pD).**we can prune our search if dist(pA, pB) > dist(pB, pC) does not hold
**********************************************************************************************/
void graph::performHeuristicTwoOpt( ){	
			
	//store the current totalDistanceTraveled
	int distance = totalDistanceTraveled;	

	vector<vertexStruct*> tourModified;

	int distanceAB, distanceCD;
	int distanceAC, distanceBD, distanceBC;

	int distanceABCD, distanceACBD;

	int vertexAIndex = 0, vertexBIndex = 0, vertexCIndex = 0, vertexDIndex = 0;

	vertexStruct *pointA = NULL, *pointB = NULL, *pointC = NULL, *pointD = NULL;

	//edgeOne:
	for (vertexAIndex = 0; (vertexAIndex <= finalTour.size() - 4) && finalTour.size() > 4; vertexAIndex ++)
	{
		
		int edgeOneNumber = vertexAIndex / 2 + 1;

		vertexBIndex = vertexAIndex + 1;
		

		pointA = finalTour.at(vertexAIndex);
		pointB = finalTour.at(vertexBIndex);		
		
		
		for(int i = 0; i < pointB->neighborDistance.size() && i < 1000; ++i){
			if(pointB->neighborDistance.at(i)->neighborAddress != pointA &&
				pointB->neighborDistance.at(i)->neighborAddress != pointD){
				vertexCIndex = pointB->neighborDistance.at(i)->neighborAddress->primComp;
			}
		}

		if(vertexCIndex < finalTour.size() -1){
			int num = finalTour.size() - vertexCIndex;
			srand(time(NULL));			
			vertexDIndex = vertexCIndex + rand() % num;
		}else{
			continue;
		}		
			        
		pointC = finalTour.at(vertexCIndex);		
        pointD = finalTour.at(vertexDIndex);       

		distanceCD = distBetweenTwoVertexes(pointC, pointD);
		distanceAB = distBetweenTwoVertexes(pointA, pointB);			             									                
		distanceABCD = distanceAB + distanceCD;

		distanceAC = distBetweenTwoVertexes(pointA, pointC);
		distanceBD = distBetweenTwoVertexes(pointB, pointD);
		distanceBC = distBetweenTwoVertexes(pointB, pointC);
		distanceACBD = distanceAC + distanceBD;

        if(distanceAB > distanceBC)  {
			
			if (distanceACBD < distanceABCD){
				tourModified.clear();

				//perform swap              
				for(int i = 0; i < vertexBIndex; ++i){
					tourModified.push_back(finalTour.at(i));
				}
					              
				for(int i = vertexCIndex; i >= vertexBIndex; --i){
					tourModified.push_back(finalTour.at(i));
				}

				for(int i = vertexCIndex + 1; i < finalTour.size(); ++i){
					tourModified.push_back(finalTour.at(i));
				}
				
				int modifiedDistance = calculateTDistance(tourModified);

				cout << "mod Distance = " << modifiedDistance << " distance = " << distance << endl;
				if (modifiedDistance < distance) {
				
					//cout << "found one 2opt" << "\t";
					totalDistanceTraveled = modifiedDistance;
					//cout << "new distance is " << new_distance << "found improvement \t";
					finalTour.empty();

					for (int x =0; x < tourModified.size(); x++){			   
						tourModified.at(x)->primComp = x;
						finalTour.push_back(tourModified.at(x));
					}                   
				}
			}			
		}
	}
}

int graph::calculateTDistance(vector<vertexStruct*> finalTour){
	int totalDTraveled = 0;
	long int  yDiff;
	long int  xDiff;
	//calculate the distances between vertexes
	for (int i = 1; i < finalTour.size(); i++)
	{
		xDiff = finalTour[i-1]->xCoord - finalTour[i]->xCoord;
		// cout << "xDiff is " << xDiff << endl;
		yDiff = finalTour[i-1]->yCoord - finalTour[i]->yCoord;
		// cout<< "yDiff is " << yDiff << endl;
		totalDTraveled += graph::round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
	}

	int sizeofVector = finalTour.size() -1;
	// calculate the distance from first to last vertex to complete tour
	xDiff = finalTour[0]->xCoord - finalTour[sizeofVector]->xCoord;
	yDiff = finalTour[0]->yCoord - finalTour[sizeofVector]->yCoord;
	
	totalDTraveled += (int) graph::round(sqrt(pow(xDiff,2) + pow(yDiff,2)));

	return totalDTraveled;
}

	
bool graph::verticeNotEqual(vertexStruct *a, vertexStruct *b, vertexStruct *c, vertexStruct *d, vertexStruct *e, vertexStruct *f){
	
	vertexStruct* aV[] = {a, b, c, d, e, f};

	for(int i = 1; i < 6; ++i){
		if(aV[i] == a){
			return false;
		}

		if(i > 1 && aV[i] == b){
			return false;
		}

		if(i > 2 && aV[i] == c){
			return false;
		}

		if(i > 3 && aV[i] == d){
			return false;
		}

		if(i > 4 && aV[i] == e){
			return false;
		}
	}	
	return true;
}

/*********************************************************************************
 * ** Function name: main2Opt
 * ** Parameters : Final tour of cities
 * ** Description: iApplyiung 2 opr to tsp
 * *********************************************************************************/
void graph::main2Opt()
{
    vector <vertexStruct*> newTour;
    int size = finalTour.size(); 
    int counter = 0;
    /* Perform 20 iterations */
    while ( counter < 20 )
    {
        double currentBest = totalDistanceTraveled;
        for ( int i = 0; i < size - 1; i++ ) 
        {
            for ( int k = i + 1; k < size; k++) 
            {
                optHelper( i, k );
                double newDistance = getTourDistance();
                /* If distance with swapped cities is less then update current */
                if ( newDistance < currentBest ) 
                {
                    counter = 0;
                    finalTour = newTour;
                    currentBest = newDistance;
                }
            }
        }
        counter++;
    }
}

/*********************************************************************************
 * ** Function name: optHelper
 * ** Parameters : Indexes pf Final tour of cities
 * ** Description: iApplyiung 2 opr to tsp
* *********************************************************************************/
void graph::optHelper( const int& i, const int& k ) 
{
    vector <vertexStruct*> newTour;
    int size = finalTour.size();
    //take tour 0 to i-1 and add to new Tour
    for ( int j = 0; j <= i - 1; ++j )
    {
        newTour.at(j) = finalTour.at(j);
    }
    //take tour city at i to tour city at k and add in reverse order to new tou
    int dec = 0;
    for ( int c = i; c <= k; ++c )
    {
        newTour.at(c) = finalTour.at(k - dec);
        dec++;
    }
    for ( int c = k + 1; c < size; ++c )
    {
        newTour.at(c) = finalTour.at(c);
    }
}
