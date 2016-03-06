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
    	newStruct->vertex = temporaryStore[0];
    	newStruct->xCoord = temporaryStore[1];
    	newStruct->yCoord = temporaryStore[2];	

    	// cout << "Pushing " <<  newStruct->vertex << " " << newStruct->xCoord << " " << newStruct->yCoord << endl;
    	vertexGraph.push_back(newStruct);
    	
    }

}

int graph::getSize()
{

	return vertexGraph.size();
}
