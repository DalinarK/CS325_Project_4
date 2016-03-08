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

	vector <MinSpanEdge*> minSpanningTree = fileIO.getMinSpanningTree(fileIO.getVertex(0));

	cout << "Min Spanning tree order: " << endl;
	for(int i = 0; i < minSpanningTree.size(); ++i){
		cout << "edge " << i << " = " << minSpanningTree.at(i)->start->vertexName << " <--> " << minSpanningTree.at(i)->end->vertexName<<endl;
	}
	return 0;
}