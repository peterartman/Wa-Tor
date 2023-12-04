#include <iostream>
#include <random>
#include <thread>
#include <variant>
#include <vector>
#include <SFML/Graphics.hpp>

// #include <stdio.h>
// #include <omp.h>
// #include <chrono>

class Water;
const int xdim = 400; 
const int ydim = 400;
int WindowXSize = 800;
int WindowYSize = 800;
int cellXSize = WindowXSize / xdim;
int cellYSize = WindowYSize / ydim;

using namespace std;

unsigned int NumShark = 12000;
unsigned int NumFish = 12000;
constexpr unsigned int FishBreed = 7; //Number of time units that pass before a fish can reproduce
constexpr unsigned int SharkBreed = 15; //Number of time units that must pass before a shark can reproduce;
constexpr unsigned int SharkStarve = 30;
constexpr unsigned int GridSize = 800;
constexpr unsigned int Threads = 1;

unsigned int sharkCount = 0;
unsigned int fishCount = 0;
unsigned int waterCount = 0;
unsigned int numWater = (GridSize * GridSize) - (NumFish + NumShark);
int randomType = 0;


int totalSteps = 0; //Total steps ba all fish and sharks

class WaTorTail {
public:
	virtual void move() = 0;
	virtual void addStep() = 0;
	virtual int getStepCounter() = 0;

	int stepCounter;
	unsigned int timeToBread;
	pair<int, int> position;

private:

};

std::vector<std::vector<WaTorTail*>> grid(GridSize, std::vector<WaTorTail*>(GridSize));

pair<int,int > checkBonduaries(int x, int y)
{


	pair<int, int> returnedPair = make_pair(x, y);
	return (returnedPair);
}

class Water : public WaTorTail
{
private:

public:
	int stepCounter;

	Water();
	~Water() = default;
	void move() override
	{
		
	}
	void addStep() override
	{

	}
	int getStepCounter() override
	{
		return 0;
	}
};

Water::Water() = default;

class Fish: public WaTorTail
{
	public:
		int stepCounter;
		unsigned int timeToBread;
		bool adjecentLoc[4];
		pair<int,int> position;
		Fish();

		~Fish() = default;
		void breed();
		void endOflife();
		void move() override
		{
			stepCounter++;
		}
		void addStep() override
		{
			stepCounter++;
		}
		int getStepCounter() override
		{
			return  stepCounter;
		}
};

Fish::Fish()
{
	Fish::timeToBread = FishBreed;
	Fish::stepCounter = 0;
	Fish::position = make_pair(0, 0);
}

void Fish::endOflife()
{
	grid[Fish::position.first][Fish::position.second] = new Water();
}



void Fish::breed()
{
	
}

class Shark: public WaTorTail
{
	public:
		unsigned int energyLevel;
		int stepCounter;
		unsigned int timeToBread;
		pair<int,int> position; //(x,y)
		bool adjecentLoc[4] = { false,false,false,false };
		Shark();
		~Shark() = default;

		void breed();

		void endOflife();

		void addStep() override
		{
			stepCounter++;
		}

		void move() override
		{
			
		}

		int getStepCounter() override
		{
			return  stepCounter;
		}

};

Shark::Shark()
{
	Shark::stepCounter = 0;
	Shark::energyLevel = SharkStarve;
	Shark::timeToBread = SharkBreed;
	Shark::position = make_pair(0, 0);
}

void Shark::endOflife()
{
	grid[Shark::position.first][Shark::position.second] = new Water();
}


void Shark::breed()
{

}

void elementsDeployment()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, (GridSize - 1));

	//START of simulation elements deployment
	while ((sharkCount < NumShark) && (fishCount < NumFish) && (waterCount < numWater))
	{
		while (sharkCount < NumShark)
		{
			int row = 0;
			int col = 0;

			row = dis(gen);
			col = dis(gen);

			if (grid[row][col] == nullptr)
			{
				grid[row][col] = new Shark();
				grid[row][col]->position.first = row;
				grid[row][col]->position.second = col;
			}
		}

		while (fishCount < NumFish)
		{
			int row = 0;
			int col = 0;

			row = dis(gen);
			col = dis(gen);

			if (grid[row][col] == nullptr)
			{
				grid[row][col] = new Fish();
				grid[row][col]->position.first = row;
				grid[row][col]->position.second = col;
			}
		}

		while (waterCount < numWater)
		{
			int row = 0;
			int col = 0;

			row = dis(gen);
			col = dis(gen);

			if (grid[row][col] == nullptr)
			{
				grid[row][col] = new Water();
			}
		}
	}
	//END of simulation elements deployment
}


int main()
{
	elementsDeployment();

	bool simulationEnd = false;
	int simulationLegth = 1;
	int chronosCounter = 0;
	// double itime = 0.0;
	// double ftime = 0.0;
	// double exec_time = 0.0;

	// START time
	// itime = omp_get_wtime();
	// auto start = std::chrono::high_resolution_clock::now();

	// START simulation

	while (simulationEnd == false)
	{
		if(chronosCounter < simulationLegth)
		{
			for (int row = 0; row < grid.size(); ++row) {
				for (int col = 0; col < grid[row].size(); ++col) {
					WaTorTail* waTorTail = grid[row][col];

					if (Fish* fish = dynamic_cast<Fish*>(waTorTail)) {
						fish->move();
					}
					else if (Shark* shark = dynamic_cast<Shark*>(waTorTail)) {
						shark->move();
					}
				}
			}
			chronosCounter = chronosCounter + 1;
		}
		else
		{
			simulationEnd = true;
		}
	}
	// auto end = std::chrono::high_resolution_clock::now();
	// END simulation

	// omp_get_wtime();
	// END Time

	// #pragma omp parallel for

	for (int row = 0; row < grid.size(); ++row) {
		for (int col = 0; col < grid[row].size(); ++col) {
			WaTorTail* waTorTail = grid[row][col];

			if (Fish* fish = dynamic_cast<Fish*>(waTorTail)) {
				totalSteps = totalSteps + grid[row][col]->getStepCounter();
			}
			else if (Shark* shark = dynamic_cast<Shark*>(waTorTail)) {
				totalSteps = totalSteps + grid[row][col]->getStepCounter();
			}
		}
	}

	// exec_time = ftime - itime;
	// std::chrono::duration<double> duration = end - start;


	std::cout << "Chronos counter: " << chronosCounter << endl;
	std::cout << "Sharks: " << sharkCount << " fish: " << fishCount << " water: " << waterCount << endl;
	std::cout << "Total steps done by all sharks and fish: " << totalSteps << std::endl;

	// std::cout << "Execution time: " << duration.count() << std::endl;
	
	// printf("\n\nTime taken is %f", exec_time);

	// Add code without sfml;

	return 0;
	
}