// Theodora Tataru
// C00231174

#include <iostream>
#include <vector>
//include both for file and string
#include <string>
#include <fstream>
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 

template <typename T>
void printArray(T array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i];
	}
	std::cout << std::endl;
}

template <typename T>
void clearArray(T array[], int size)
{
	std::fill_n(array, size, 0);
}

int readFile(char dataString[])
{
	int sizeMyString = 0;
	std::ifstream myfile("data.txt");

	if (myfile.is_open())
	{
		std::string line;
		while (std::getline(myfile, line))
		{
			for (int i = 0; i < line.length(); i++)
			{
				char c = line.at(i);
				dataString[i] = c;
				sizeMyString++;
			}
		}
		myfile.close();
		return sizeMyString;
	}
	else
	{
		std::cout << "Unable to open file";
		return sizeMyString;
	}
}

void parseArrayByComma(char dataString[], int size, int numbers[], int &sizeTheNumber)
{
	char theNumber[20];
	int aInteger = 0;
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		if (dataString[i] != ',')
		{
			theNumber[index] = dataString[i];
			index++;
		}
		if(dataString[i] == ',' or i == size-1)
		{
			for (int j = 0; j < index; j++)
			{
				if (aInteger == 0)
				{
					
					aInteger = theNumber[j]-48;
				}
				else
				{
					aInteger = (aInteger * 10) + (theNumber[j]-48);
				}
			}
			numbers[sizeTheNumber] = aInteger;
			sizeTheNumber++;
			clearArray(theNumber, index);
			index = 0;
			aInteger = 0;
		}
	}
}

void printChartOrizontaly(int numbers[], int size)
{
	std::cout << "\nPrint chart orizontaly: \n" << std::endl;
	for (int i = 1; i < size; i++)
	{
		for (int j = numbers[i]; j > 0; j--)
		{
			std::cout << "|";
		}
		std::cout << std::endl;
	}
}
int maxInteger(int numbers[], int size)
{
	int max = numbers[0];
	for (int i = 1; i < size; i++)
	{
		if (max < numbers[i])
		{
			max = numbers[i];
		}
	}
	return max;
}
void printChartVertically(int numbers[], int size)
{
	std::vector<std::vector<char>> myGraph;
	int initialMemory = maxInteger(numbers, size)+1;

	// filling the array with spaces to look invisibile
	for (int i = 0; i < initialMemory; i++)
	{
		myGraph.push_back(std::vector<char>());
		for (int j = 0; j < initialMemory; j++)
		{
			myGraph[i].push_back(' ');
		}
	}
	// drawing the chart in the 2D array
	for (int i = 1; i <= numbers[0]; i++)
	{
		for (int r = i-1; r <= i-1; r++)
		{
			for (int c = myGraph[i].size() - 1; c > myGraph[i].size() - 1 - numbers[i]; c--)
			{
				myGraph[c][r] = '^';
			}
		}
	}
	std::cout << "\nPrint chart vertically: " << std::endl;
	for (int i = 0; i < myGraph.size(); i++)
	{
		for (int j = 0; j < myGraph[i].size(); j++)
		{
			std::cout << myGraph[i][j];
		}
		std::cout << std::endl;
	}
}

void drawGraph(int numbers[], int sizeNumbers)
{
	////////////////////////////////////////////////
	/*                  SFML                      */
	////////////////////////////////////////////////
	//create Window 
	sf::RenderWindow window(sf::VideoMode(800, 800), "First Graphics in C++");
	sf::RectangleShape simpleRectangle;

	// set timePerFrame to 1 60th of a second. 60 frames per second
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();
	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{
			window.clear();
			int size = 800 / sizeNumbers;
			int spaces = size / sizeNumbers;
			int bottomLocation = spaces;
			int scaling = 800 / maxInteger(numbers, sizeNumbers) - 1;


			for (int i = 1; i < sizeNumbers; i++)
			{
				simpleRectangle.setSize(sf::Vector2f(size, numbers[i]*scaling));
				simpleRectangle.setFillColor(sf::Color::Red);
				simpleRectangle.setPosition(bottomLocation, 800-numbers[i]*scaling);
				window.draw(simpleRectangle);

				bottomLocation += spaces + size;
			}

			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}


int main()
{	// from the file, a char of array
	char dataString[20];
	int sizeMyString;
	// after parsing, the integers from the file
	int numbers[20];
	int sizeNumber = 0;
	
	sizeMyString = readFile(dataString);
	std::cout << "Content of the file:" << std::endl;
	printArray(dataString, sizeMyString);
	parseArrayByComma(dataString, sizeMyString, numbers, sizeNumber);
	//std::cout << maxInteger(numbers, sizeNumber) << std::endl;
	
	printChartOrizontaly(numbers, sizeNumber);
	printChartVertically(numbers, sizeNumber);
	drawGraph(numbers, sizeNumber);

	return 0;
}


