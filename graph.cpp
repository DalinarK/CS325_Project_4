#include "graph.h"


graph::graph()
{
	vector <vertexStruct*> vertexGraph;
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
			int neighborName = i;
			// Prevents the calculation of the vertexes distance from itself - which would be 0

				int xDiff = vertexGraph[g]->xCoord - vertexGraph[i]->xCoord;
				// cout << "xDiff is " << xDiff << endl;
				int yDiff = vertexGraph[g]->yCoord - vertexGraph[i]->yCoord;
				// cout<< "yDiff is " << yDiff << endl;
				int distance = round(sqrt(pow(xDiff,2) + pow(yDiff,2)));
				// printf("Distance is %d \n", distance);

				neighborPTR->neighborName = neighborName;
				neighborPTR->distance = distance;
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

// Sorts the neighbors by distance
void graph::mergeSortDistances()
{
	cout << "inside mergeSOrtDistances()" << endl;

	
	cout << "sorted distance: " << endl;

	// cout << "coord for: " << vertexGraph[g]->vertexName << " " << vertexGraph[g]->xCoord << ", " << vertexGraph[g]->yCoord << endl;
	// for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++)
	// {
	// 	cout << "distance from " << vertexGraph[g]->vertexName << " to " << vertexGraph[g]->neighborDistance[i]->neighborName << ": " << vertexGraph[g]->neighborDistance[i]->distance << endl;		

	// }

	// for every vertex, sort the neighbors list by distance
	// for (int g = 0; g < vertexGraph.size(); g++)
	int g = 0;
	// {
		int end = vertexGraph[g]->neighborDistance.size() -1;
		mergesort(vertexGraph[g]->neighborDistance, 0, end);

		// for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++)
		// {
		// 	cout << "name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " value: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
		// }
	// }

	// int g = 40;
	// for (int g = 0; g < vertexGraph.size(); g++)
	// {
	// 	cout << "base vertex" << vertexGraph[g]->vertexName << endl;
		for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++)
		{
			cout << "name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " value: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
		}
	// }

	// for (int g = 0; g < vertexGraph.size(); g++)
	// {
		MergeSortHelper(vertexGraph[g]->neighborDistance);

		// for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++)
		// {
		// 	cout << "name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " value: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
		// }
	// }

	// for (int g = 0; g < vertexGraph.size(); g++)
	// {
	// 	cout << "base vertex" << vertexGraph[g]->vertexName << endl;
	// 	for (int i = 0; i < vertexGraph[g]->neighborDistance.size(); i++)
	// 	{
	// 		cout << "name: " << vertexGraph[g]->neighborDistance[i]->neighborName << " value: " << vertexGraph[g]->neighborDistance[i]->distance << endl;
	// 	}
	// }

}
// got from 



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

void graph::DoMerge(vector <neighbors *>& neighborvector, int left, int mid, int right)
{
    vector <neighbors *> tempVector;
    tempVector.resize(vertexGraph[0]->neighborDistance.size());
    int i, left_end, num_elements, tmp_pos;
 
    left_end = (mid - 1);
    tmp_pos = left;
    num_elements = (right - left + 1);
 
    while ((left <= left_end) && (mid <= right))
    {
        if (neighborvector[left]->distance <= neighborvector[mid]->distance)
            tempVector[tmp_pos++] = neighborvector[left++];
        else
            tempVector[tmp_pos++] = neighborvector[mid++];
    }
 
    while (left <= left_end)
        tempVector[tmp_pos++] = neighborvector[left++];
 
    while (mid <= right)
        tempVector[tmp_pos++] = neighborvector[mid++];
 
    // for (i=0; i < num_elements; i++)
    //     neighborvector[right--] = tempVector[right];
}


void graph::Merge_Sort_Iterative(vector <neighbors *>& neighborvector, int left, int right)
{
	int mid;
    if (right <= left)
        return;
 
    std::vector<std::pair<int, int> > list;
    std::vector<MergePosInfo> mlist;
    list.push_back(std::pair<int, int>(left, right));

    MergePosInfo info;

    while(1)
    {
        if(list.size() == 0)
            break;
 
        left = list.back().first;
        right = list.back().second;
        list.pop_back();
        mid = (right + left) / 2;
 
        if(neighborvector[left]->distance < neighborvector[right]->distance)
        {
            info.left = left;
            info.right = right;
            info.mid = mid + 1;
 
            mlist.push_back(info);
            list.push_back(std::pair<int, int>(left, mid));
            list.push_back(std::pair<int, int>((mid+1), right));
        }     
    }

    for(int i = mlist.size() - 1; i >= 0; i--)
    {
        DoMerge(neighborvector, mlist[i].left, mlist[i].mid, mlist[i].right);
    }

}

 // used http://www.softwareandfinance.com/Visual_CPP/Merge_Sort_Iterative.html and adapted
void graph::MergeSortHelper(vector <neighbors *>& neighborvector)
{

    //Merge_Sort_Recursive(numbers, 0, array_size - 1);
    Merge_Sort_Iterative(neighborvector, 0, neighborvector.size() - 1);
}

void graph::test()
{
	cout << "test" << endl;
}

