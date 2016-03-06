#ifdef readFile_h
#define readFile_h

using std::vector;

// struct vertexStruct{
// 	int vertex;
// 	int xCoord;
// 	int yCoord;
// 	vector <int> neighborDistance;
// };

class readFile
{
private:

	phase currentPhase;
	status nextGeneration;
	status currentGeneration;
	int numberOfLiveNeighbors;

public:

	Cell();

	//get functions

	phase get_phase();
	status get_nextGeneration();
	status get_currentGeneration();
	int get_numberOfLiveNeighbors();

	//set functions
	void set_phase();
	void set_nextGenerationDead();
	void set_nextGenerationAlive();
	void set_nextGenEqualCurrentGen();
	void set_currentGenerationDead();
	void set_currentGenerationAlive();
	void set_numberOfLiveNeighbors(int input);



	void set_advanceToNextGen();
	};


#endif