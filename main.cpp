#include <iostream>
#include <fstream>
#include <stdio.h>

#include "Cell.h"

using std::string;


int main (int argc, const char * argv[1])
{
	Cell fileIO;
	/* The first argument (argc) is the number of elements in the array so we should have two elements the program name and file name 
	Credit: http://www.site.uottawa.ca/~lucia/courses/2131-05/labs/Lab3/CommandLineArguments.html
	*/
    if(argc != 2)
    {
        std::cout << "Please enter an input filename." << std::endl << std::endl;
        exit(1);
    }

    printf("In main\n");
	
	fileIO.createGraph(argv[1]);
    


	return 0;
}