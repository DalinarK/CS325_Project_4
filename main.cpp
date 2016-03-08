#include <iostream>
#include <fstream>
#include <stdio.h>

#include "graph.h"

using std::string;

struct test {
	int a;
};

int main (int argc, const char * argv[1])
{

	printf("In main\n");

	graph fileIO;
	/* The first argument (argc) is the number of elements in the array so we should have two elements the program name and file name 
	Credit: http://www.site.uottawa.ca/~lucia/courses/2131-05/labs/Lab3/CommandLineArguments.html
	*/
    if(argc != 2)
    {
        std::cout << "Please enter an input filename." << std::endl << std::endl;
        exit(1);
    }
	
	fileIO.createGraph(argv[1]);
	fileIO.calculateDistances();   
	fileIO.sortDistances();

	std::map<vertexStruct*,vector<vertexStruct*>> minSpanningTree = fileIO.getMinSpanningTree(fileIO.getVertex(0));

	cout << "Min Spanning tree order: " << endl;

	int count = 0;
	//How to iterate through a map with key vector
	//http://www.cplusplus.com/forum/beginner/161248/
	for(const auto& pair : minSpanningTree){
		cout << "Edge list for " << pair.first->vertexName << endl;
		for( std::size_t i = 0 ; i < pair.second.size() ; ++i ){
			cout << "edge " << i << " = " << pair.second[i]->vertexName <<endl;
			++count;
		}
	}

	cout << "edges in min spanning tree = " << count << endl;

	cout << "Making Tour" << endl;
	fileIO.makeNaiveTour(0);

	vector <vertexStruct*>* finalTour = fileIO.getTour();

	cout << "final tour size = " << finalTour->size() << endl;

	for(int i = 0; i < finalTour->size(); ++i){
		cout << finalTour->at(i)->vertexName << "\t";
	}

	cout << endl;
	return 0;
}