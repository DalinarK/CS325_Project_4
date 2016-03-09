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
	//fileIO.sortDistances();

	// std::map<vertexStruct*,vector<vertexStruct*>> minSpanningTree = fileIO.getMinSpanningTree(fileIO.getVertex(0));

	// // cout << "Min Spanning tree order: " << endl;

	// int count = 0;
	// int i = 0;
	// // //How to iterate through a map with key vector
	// // //http://www.cplusplus.com/forum/beginner/161248/

	// for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter ){
	// 	cout << "\nEdge list for: " << map_iter->first->vertexName <z< endl;
	// 	i = 0;
		// for( std::size_t i = 0 ; i < map_iter->second.size() ; ++i ){
		// 	// cout << "edge " << i << " = " << map_iter->second[i]->vertexName <<endl;
		// 	++count;
		// }
	// }
	// cout << endl;

	fileIO.createEdgelist();

	// cout << "edges in min spanning tree = " << count << endl;
	// cout << "Making Tour" << endl;
	fileIO.makeNaiveTour(0);
	fileIO.calculateFinalTourDistance();

	vector <vertexStruct*>* finalTour = fileIO.getTour();

	cout << "final tour size = " << finalTour->size() << endl;

	// for(int i = 0; i < finalTour->size(); ++i){
	// 	cout << finalTour->at(i)->vertexName << "\t";
	// }
	cout << endl;


	cout << "Tour distance = " << fileIO.getTourDistance() << endl;

	fileIO.writeTourFile(argv[1]);


	return 0;
}