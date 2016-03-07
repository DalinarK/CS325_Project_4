#include "graph.h"


graph::graph()
{
	vector <vertexStruct*> vertexGraph;
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
    		sConverted = stoi(s);
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
	cout << "graph size is" << graphSize << endl;
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

				neighborPTR->neighborName = vertexGraph[i]->vertexName;
				neighborPTR->distance = distance;
				neighborPTR->neighborAddress = vertexGraph[i];
				// cout << "neighbor name is " << neighborPTR->neighborAddress->vertexName << endl;
				vertexGraph[g]->neighborDistance.push_back(neighborPTR);
				// cout << "distance from " << vertexGraph[g]->vertexName << " to " << vertexGraph[g]->neighborDistance[i]->neighborName << ": " << vertexGraph[g]->neighborDistance.back()->distance << endl;		
		}
	} 

	// int graphElement = 40;
	// cout << "coord for: " << vertexGraph[graphElement]->vertexName << " " << vertexGraph[graphElement]->xCoord << ", " << vertexGraph[graphElement]->yCoord << endl;
	// for (int i = 0; i < vertexGraph[graphElement]->neighborDistance.size(); i++)
	// {
	// 	cout << "distance from " << vertexGraph[graphElement]->vertexName << " to " << vertexGraph[graphElement]->neighborDistance[i]->neighborName << ": " << vertexGraph[graphElement]->neighborDistance[i]->distance << endl;		

	// }

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
		// cout << "Vertex:" << vertexGraph[g]->vertexName << "sorted" << endl;
		sort(vertexGraph[g]->neighborDistance.begin(), vertexGraph[g]->neighborDistance.end(), sortByDistance);
		
		for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++){
		// cout << "name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " value: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
		}	
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

