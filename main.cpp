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

	int graphSize;

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
	graphSize = tspGraph.getSize();

	
	tspGraph.createOddDegreeSubGraph();
	tspGraph.createMinMatching();
	tspGraph.combineMSTandMinMatch();
	tspGraph.calculateEulerTour(0);
	tspGraph.calculateFinalTourDistance();

	cout << "Tour distance = " << tspGraph.getTourDistance() << endl;


	// tspGraph.makeNaiveTour(rand() % tspGraph.getVertexGraphSize());

	// tspGraph.calculateFinalTourDistance();
	// for(int i = 0; i < (int)(tspGraph.getTour())->size(); ++i){
	// 	cout << "tour " << i << "= " << (tspGraph.getTour())->at(i)->vertexName << "\t";
	// }	

	// vector <vertexStruct*>* finalTour = tspGraph.getTour();

	// cout << "final tour size = " << finalTour->size() << endl;

	// cout << "Tour distance = " << tspGraph.getTourDistance() << endl;
	// cout << "Tour distance = " << tspGraph.getTourDistance() << endl;
	// cout << "Tour distance = " << tspGraph.getTourDistance() << endl;

	// //tspGraph.writeTourFile(argv[1]);

	
	// tspGraph.calculateFinalTourDistance();
	// int tourDistance = tspGraph.getTourDistance();

	int counter = 0;

	while(tspGraph.performHeuristicTwoOpt()){
		//tspGraph.performHeuristicThreeOpt();
		tspGraph.performHeuristicTwoOpt();
		cout << counter++ << "\t";
	}
	
	// if(tspGraph.getTour()->size() < 1000){
	// 	counter = 0;
	// 	while(tspGraph.performHeuristicThreeOpt()){				
	// 		cout << counter++ << "\t";
	// 	}
	// }

	
	

	// cout << "After 2-opt" << endl;
	

	for(int i = 0; i < (int)(tspGraph.getTour())->size(); ++i){
		cout << "tour " << i << "= " << (tspGraph.getTour())->at(i)->vertexName << "\t";
	}

	cout << "\nTour distance = " << tspGraph.getTourDistance() << endl;

	tspGraph.writeTourFile(argv[1]);

	return 0;
}
