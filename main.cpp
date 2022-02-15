# include <iostream>
# include "PerlinNoise.hpp"
# include <vector>
#include <ctime>
#include <string.h>
#include <algorithm>
#include <iterator>

using namespace std;

float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

//global for ideal goal location
int lastFilled[2] = {0,0};

//fills an area
void fillAreaFixed(int width,int height,string grid[height],int start[2]){
	grid[start[0]][start[1]]='s';
	string buffer[height];
	for(int y=0;y<height;y++){
		buffer[y]=grid[y];
	}
	bool change=true;
	while(change){
		change=false;
		for(int x=0;x<width;x++){
			for(int y=0;y<height;y++){
				if ((grid)[y][x] == 's')
				{
					if ((grid)[y][x+1] == ' ')
					{
						
						(buffer)[y][x+1] = 's';
						change = true;
						lastFilled[0] = y;
						lastFilled[1] = x+1;
					}
					
					if ((grid)[y][x-1] == ' ')
					{
						
						(buffer)[y][x-1] = 's';
						change = true;
						lastFilled[0] = y;
						lastFilled[1] = x-1;
					}

					if ((grid)[y-1][x] == ' ')
					{
						
						(buffer)[y-1][x] = 's';
						change = true;
						lastFilled[0] = y-1;
						lastFilled[1] = x;
					}

					if ((grid)[y+1][x] == ' ')
					{
						
						(buffer)[y+1][x] = 's';
						change = true;
						lastFilled[0] = y+1;
						lastFilled[1] = x;
					}

				}
				
			}
		}

		for(int y=0;y<height;y++){
			grid[y]=buffer[y];
		}

	}
	
}




//checks if ALL areas of grid are reachable using fill algorithim
bool isSolvable(int width, int height, string grid[height])
{
	int start[2] = {1,1};
	fillAreaFixed(width, height, grid, start);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (grid[y][x] == ' ')
			{
				return false;
			}
		}
	}
	return true;
}

string * generateLevel(int width, int height,int Seed, string grid[height])
{
	double frequency = 8;	
	frequency = std::clamp(frequency, 0.1, 64.0);
	std::int32_t octaves = 8;
	octaves = std::clamp(octaves, 1, 16);
	std::uint32_t seed = Seed;
		

	siv::PerlinNoise perlin(seed);
	const double fx = width / frequency;
	const double fy = height / frequency;

	
	for (std::int32_t y = 0; y < height; ++y)
	{
		
		for (std::int32_t x = 0; x < width; ++x)
		{
			
			double val = (perlin.noise2D_0_1(x / fx, y / fy / 3));
			if (y == 0 || x == 0 || y == height-1 || x == width-1)
			{
				
				grid[y] += 'X';
				
			}else if (val > 0.6)
			{
				grid[y] += 'X';
			}else
			{
				grid[y] += ' ';
			}
		}
	}

	return grid;
	
}

void clean(int width, int height, string grid[height])
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (grid[y][x] == 's')
			{
				grid[y][x] = ' ';
			}
		}
	}
}

void run(int size = 30)
{
	srand(time(0));
	
	string empty[100] = {};
	string grid[100] = {};
	int start[2] = {1,1};
	
	int levelsTested = 0;
	generateLevel(size*3,size,rand() % 1000 +1,grid);
	while (true)
	{
		cout << levelsTested++ << endl;
		copy(std::begin(empty), std::end(empty), std::begin(grid));
		generateLevel(size*3,size,rand() % 1000 +1,grid);
		
		if (isSolvable(size*3,size,grid))
		{
			clean(size*3,size,grid);
			break;
		}
	}
	
	grid[lastFilled[0]][lastFilled[1]] = '0';

	for (int y = 0; y < size; y++)
	{
		cout << grid[y];
		cout << endl;
	}
	cout << isSolvable(size*3,size,grid) << endl;
	
} 

int main()
{
	int size = 0;
	while (true)
	{
		cin >> size;
		run(size);
		
	}
	
}