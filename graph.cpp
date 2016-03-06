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

}

int graph::getSize()
{

	return vertexGraph.size();
}

void graph::mergeSortDistances()
{

	vector <int> unsorted; 

	for (int i = 0; i < vertexGraph[0]->neighborDistance.size(); i++)
	{
		unsorted.push_back(vertexGraph[0]->neighborDistance[i]->distance);
	}
	cout << endl;
   
    // for (int i = 0; i < unsorted.size(); i++)
    // {
    //     cout << unsorted[i] << " ";
    // }
    // cout << "in main" << endl;

    vector <int> sorted = merge_sort(unsorted);

    for (int i = 0; i < sorted.size(); i++)
    {
        cout << sorted[i] << " ";
    }
 
}

void graph::test()
{
	cout << "test" << endl;
}

vector<int> graph::merge(vector<int> &vec,const vector<int>& left, const vector<int>& right)
{
    // Fill the resultant vector with sorted results from both vectors
    vector<int> result;
    unsigned left_it = 0, right_it = 0;

    while(left_it < left.size() && right_it < right.size())
    {
        // If the left value is smaller than the right it goes next
        // into the resultant vector
        if(left[left_it] < right[right_it])
        {
            result.push_back(left[left_it]);
            left_it++;
        }
        else
        {
            result.push_back(right[right_it]);
            right_it++;
        }
    }

    // Push the remaining data from both vectors onto the resultant
    while(left_it < left.size())
    {
        result.push_back(left[left_it]);
        left_it++;
    }

    while(right_it < right.size())
    {
        result.push_back(right[right_it]);
        right_it++;
    }
    // //show merge process..
    //   int i;
    //   for(i=0;i<result.size();i++)
    //      {                                
    //      cout<<result[i]<<" ";
    //      }
    // // break each line for display purposes..
    //     cout<<"***********"<<endl; 

    //take a source vector and parse the result to it. then return it.  
    vec = result;               
    return vec;
}

vector<int> graph::merge_sort(vector<int>& vec)
{
    // Termination condition: List is completely sorted if it
    // only contains a single element.
    if(vec.size() == 1)
    {
        return vec;
    }

    // Determine the location of the middle element in the vector
    std::vector<int>::iterator middle = vec.begin() + (vec.size() / 2);

    vector<int> left(vec.begin(), middle);
    vector<int> right(middle, vec.end());

    // Perform a merge sort on the two smaller vectors
    left = merge_sort(left);
    right = merge_sort(right);

    return merge(vec,left, right);
}