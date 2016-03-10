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
	srand(time(NULL));

	printf("In main\n");

	graph tspGraph;
	/* The first argument (argc) is the number of elements in the array so we should have two elements the program name and file name 
	Credit: http://www.site.uottawa.ca/~lucia/courses/2131-05/labs/Lab3/CommandLineArguments.html
	*/
    if(argc != 2)
    {
        std::cout << "Please enter an input filename." << std::endl << std::endl;
        exit(1);
    }
	
	tspGraph.createGraph(argv[1]);
	tspGraph.calculateDistances();   
	tspGraph.sortDistances();


/*
	std::map<vertexStruct*,vector<vertexStruct*>> minSpanningTree = tspGraph.getMinSpanningTree(tspGraph.getVertex(0));

	// cout << "Min Spanning tree order: " << endl;

	int count = 0;
	int i = 0;
	//How to iterate through a map with key vector
	//http://www.cplusplus.com/forum/beginner/161248/
	for(auto map_iter = minSpanningTree.cbegin() ; map_iter != minSpanningTree.cend() ; ++map_iter ){
		// cout << "\nEdge list for: " << map_iter->first->vertexName << endl;
		i = 0;
		for( auto vec_iter = map_iter->second.cbegin() ; vec_iter != map_iter->second.cend() ; ++vec_iter ){
			// cout << "edge_" << count << " = " << vec_iter[i]->vertexName << ", ";
			++count;
		}
	}
	cout << endl;

	for(auto map_iter = minSpanningTree.cbegin(); map_iter != minSpanningTree.cend(); ++map_iter){
		// cout << "Edge list for " << map_iter->first->vertexName << endl;
		for( std::size_t i = 0 ; i < map_iter->second.size() ; ++i ){
			// cout << "edge " << i << " = " << map_iter->second[i]->vertexName <<endl;
			++count;
		}
	}
	*/

	// cout << "Making Tour" << endl;
	/*for(int i = 0; i < 10; ++i ){
		tspGraph.makeNaiveTour(i);
		tspGraph.calculateFinalTourDistance();
		cout << "newTour created distance = " << tspGraph.getTourDistance() << endl;

	}*/

	tspGraph.makeNaiveTour(0);
	tspGraph.calculateFinalTourDistance();
	for(int i = 0; i < (tspGraph.getTour())->size(); ++i){

		cout << "tour " << i << "= " << (tspGraph.getTour())->at(i)->vertexName << "\t";
	}

	tspGraph.calculateFinalTourDistance();

	vector <vertexStruct*>* finalTour = tspGraph.getTour();

	cout << "final tour size = " << finalTour->size() << endl;

	cout << "Tour distance = " << tspGraph.getTourDistance() << endl;
	cout << "Tour distance = " << tspGraph.getTourDistance() << endl;
	cout << "Tour distance = " << tspGraph.getTourDistance() << endl;

	//tspGraph.writeTourFile(argv[1]);

	
	tspGraph.calculateFinalTourDistance();
	int tourDistance = tspGraph.getTourDistance();

	/*
	//20 improvements
	int i = 0;
	while(i < 7){		
		i += tspGraph.performHeuristicThreeOpt();
		i +=  tspGraph.performHeuristicThreeOpt();
	}*/

	
	//Random iterative improvements
	int i = 0;
	for(int i =0; i < 100; ++i){
		tspGraph.performBruteThreeOpt();
		tspGraph.performHeuristicThreeOpt();
		tspGraph.performHeuristic1ThreeOpt();
		if(i %500 == 0)
			tspGraph.performTwoOpt();
	}

	cout << "After 3-opt" << endl;
	

	for(int i = 0; i < (tspGraph.getTour())->size(); ++i){
		cout << "tour " << i << "= " << (tspGraph.getTour())->at(i)->vertexName << "\t";
	}

	cout << "\nTour distance = " << tspGraph.getTourDistance() << endl;

	tspGraph.writeTourFile(argv[1]);

	return 0;
}
