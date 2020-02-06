# GraphicsGeneratedFromFIle

Part 1-60%
Write a program to read in numerical data from a text file.
The data must be formatted as below.
number of datapoints, [integers separated by a comma]

Example

3, 10,15,34
 
There is an example of how to read from a text file below.
Parse the data into an array of integers.
Draw a bar chart using cout. A horizontal bar chart

Example 

000000000
00000000
00000
0000000
0000

Part 2. 20%
Draw a vertical bar chart.

Example:

  0
  0  0    0
0000    0
00000  0
0000000

Part 3 20%

Use SFML to draw a bar chart.



// Simple program to read in a text file one line at a time using fstream and string.

#include <iostream>

//include both for file and string
#include <string>
#include <fstream>


int main() {
	std::string line;
	
	//place example.txt in the same folder as this code is in.
	std::ifstream myfile("example.txt");
	
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			for (int i = 0; i < line.length(); i++)
			{
				// line.at(i) returns char at position i in string.
				char c = line.at(i);
				std::cout << c;
			}
			std::cout << std::endl;
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
	return 0;
}
