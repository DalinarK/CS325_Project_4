#include <iostream>
#include <fstream>
#include <stdio.h>

#include "graph.h"

using std::string;

struct test {
	int a;
};

//return a vertex at the index
vector<vertexStruct*> copyFinalTour(vector<vertexStruct*> tour);

int main (int argc, const char * argv[1])
{
	std::clock_t start;
    double duration;
	srand(time(NULL));

	printf("In main\n");

	graph tspGraph;
	/* The first argument (argc) is the number of elements in the array so we should have two elements the program name and file name 
	Credit: http://www.site.uottawa.ca/~lucia/courses/2131-05/labs/Lab3/CommandLineArguments.html
	*/
    if(argc < 2)
    {
        std::cout << "Please enter an input filename." << std::endl << std::endl;
        exit(1);
    }
	
	tspGraph.createGraph(argv[1]);
	tspGraph.calculateDistances();   
	

	
	int lastDistance = 0, nextDistance = 0;

	bool useChristofides = true;

	if (argc == 3)
	{
		tspGraph.sortDistances();
		tspGraph.createEdgelist();
		tspGraph.createOddDegreeSubGraph();
		tspGraph.createMinMatching();
		tspGraph.combineMSTandMinMatch();
		tspGraph.calculateEulerTour(0);

		if(tspGraph.getSize() < 10000){
			while(tspGraph.performHeuristicTwoOpt()){
				//tspGraph.performHeuristicThreeOpt();
				tspGraph.performHeuristicTwoOpt();		
			}
		
			if(tspGraph.getTour()->size() < 500){
				while(tspGraph.performHeuristicThreeOpt()){				
					//continue
				}
			}
		}
	

		tspGraph.calculateFinalTourDistance();
	}
	else
	{
		if(tspGraph.getSize() < 800){
		tspGraph.sortDistances();
		}	
		tspGraph.makeNaiveTour(rand() % tspGraph.getVertexGraphSize());
		tspGraph.calculateFinalTourDistance();
		lastDistance = tspGraph.getTourDistance();
		
		vector<vertexStruct*> copy = copyFinalTour(*tspGraph.getTour());

		if(tspGraph.getSize() < 300){
			for(int i = 0; i < 1000; ++i){				
				tspGraph.makeNaiveTour(rand() % tspGraph.getVertexGraphSize());
				tspGraph.calculateFinalTourDistance();
				nextDistance = tspGraph.getTourDistance();		
				
				if(nextDistance < lastDistance){
					copy = copyFinalTour(*tspGraph.getTour());	
					lastDistance = nextDistance;	 
				}		
			}
		}else if(tspGraph.getSize() < 10000){
			for(int i = 0; i < 100; ++i){				
				tspGraph.makeNaiveTour(rand() % tspGraph.getVertexGraphSize());
				tspGraph.calculateFinalTourDistance();
				nextDistance = tspGraph.getTourDistance();		
				
				if(nextDistance < lastDistance){
					copy = copyFinalTour(*tspGraph.getTour());	
					lastDistance = nextDistance;	 
				}
			
			}
		}

		vector <vertexStruct*>* finalTour = NULL;
		int tourDistance = 0;
		if(lastDistance < nextDistance){		
			finalTour = &copy;
			tourDistance = lastDistance;
			tspGraph.updateTour(tourDistance, *finalTour);
		}else{
			finalTour = tspGraph.getTour();
			tourDistance = nextDistance;
			tspGraph.updateTour(tourDistance, *finalTour);
		}

		cout << "final tour size = " << finalTour->size() << endl;

		cout << "Tour distance = " << tspGraph.getTourDistance() << endl;
		cout << "Tour distance = " << tspGraph.getTourDistance() << endl;
		cout << "Tour distance = " << tspGraph.getTourDistance() << endl;

		//tspGraph.writeTourFile(argv[1]);
			 

		int counter = 0;

		if(tspGraph.getSize() < 10000){
			while(tspGraph.performHeuristicTwoOpt()){
				//tspGraph.performHeuristicThreeOpt();
				tspGraph.performHeuristicTwoOpt();		
			}
		
			if(tspGraph.getTour()->size() < 500){
				counter = 0;
				while(tspGraph.performHeuristicThreeOpt()){				
					//continue
				}
			}
		}
	}
	
	

	for(int i = 0; i < (int)(tspGraph.getTour())->size(); ++i){
		cout << "tour " << i << "= " << (tspGraph.getTour())->at(i)->vertexName << "\t";
	}

	cout << "\nTour distance = " << tspGraph.getTourDistance() << endl;

	tspGraph.writeTourFile(argv[1]);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"printf: "<< duration <<'\n';

	return 0;
}

//return a vertex at the index
vector<vertexStruct*> copyFinalTour(vector<vertexStruct*> tour){
	
	vector<vertexStruct*> copy;

	for(int i = 0; i < tour.size(); ++i){
		copy.push_back(tour.at(i));
	}
	return copy;
}
