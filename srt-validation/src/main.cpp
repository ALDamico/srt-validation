/*
SRT VALIDATOR VERSION 1.0
Author: Andrea Luciano Damico
Creation date: 03/01/2018

Description: This program parses a SRT file and verifies whether it's well-formed or not.

Copyright 2018 Andrea Luciano Damico

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
@file main.cpp
*/

//Includes
#include <iostream> //mostly used for error reporting
#include <fstream> //required for input-output operations on files
#include <string> //required for the Subtitle class
#include <vector> //The various subtitles are represented in memory through a vector
#include <sstream> //Required for converting command line arguments to numeric values
#include <chrono>
#include "include/error_codes.h" //Error codes used by this program
#include "include/Subtitle.h" //Class subtitle, with << operator overload for displaying 
#include "include/Time.h"

/*!
*@brief Extracts an element of type Time from a stringstream
*
* This function takes a stringstream as its argument and returns an object of type Time. It does so by taking 
* extracting the first two characters from starting position (pos), skips the character where the ":" would be and 
* repeats the same with seconds and milliseconds. Note that this function *does not* check whether the stringstream has
* a suitable structure. The programmer is in charge of making sure she's passing the correct type of stringstream.
*
*@param in The input stringstream.
*@param pos The starting position of the extraction process.
*@return An object of type Time
*/
Time sstreamToTime(std::stringstream in, unsigned pos) {
	std::stringstream minutes, seconds, milliseconds;
	minutes << in.str().substr(pos, 2);
	pos += 3;
	seconds << in.str().substr(pos, 2);
	pos += 3;
	milliseconds << in.str().substr(pos, 3);
	int minutesInt, secondsInt, millisecondsInt;
	minutes >> minutesInt;
	seconds >> secondsInt;
	milliseconds >> millisecondsInt;
	return Time(minutesInt, secondsInt, millisecondsInt);
}

/*!
* \brief Entry point for the main application.
*
* This function starts by checking whether the application has been started without any parameters or if the very first parameter is -h. If one of those conditions is true, a usage message is printed and the application exits with a 0 exit code.
*
* Otherwise, the arguments are parsed. No argument is positional. Each argument is treated sequentially as it it encountered while scanning the argument vector.
*
* After that, the application will try to open the file. If successful, the checking proper will commence.
*/
int main(int argc, char *argv[]) {
	{

		std::string filename;
		//Analyzes and parses the command line arguments passed to the application.

		//Determine if the first option is -h or the program has been launched without arguments and print the usage message. All other parameters are ignored.
		if ((argc == 1) || (static_cast<std::string>(argv[1]) == "-h"))
		{
			std::cout << "Usage:" << std::endl
				<< "srt-validation [-h] FILENAME [-p|-a] [-l #] [-c #]" << std::endl
				<< std::endl
				<< "Arguments:" << std::endl << std::endl
				<< "-h\thelp\nPrint this help message and exit. Must be the first argument passed to the program. All subsequent arguments are ignored." << std::endl << std::endl
				<< "FILENAME\nThe name of the SRT file to analyze, including extension." << std::endl << std::endl
				<< "-p\tperformance\nRun the analysis in performance mode. Each subtitle will be checked against the following one. This argument is incompatible with -a." << std::endl << std::endl
				<< "-a\taccurate\nRun the analysis in accurate mode. Each subtitle will be checked against ALL following subtitles. This argument is incompatible with -p." << std::endl << std::endl
				<< "-l #\tline length\nSet how many lines are allowed per subtitle. Default is 2." << std::endl << std::endl
				<< "-c #\tcharacters per line\nSet how many characters are allowed per subtitle. Default is 42.";
			exit(err::ok.id);
		}

		//Scan the entire array of C strings and sets various things.
		for (int i = 1; i < argc; i++)
		{
			std::string currentArg = argv[i];
			if (currentArg == "-p") {
				//Add code relevant to performance mode
			}
			else if (currentArg == "-a") {
				//Add code relevant to accurate mode. Maybe I just need to set a bool to true? Or maybe we can create a static int variable inside the Subtitle class?
			}
			else if (currentArg == "-l") {
				//Creates a stringstream called convert from the next argument and converts it to an integer.
				std::stringstream convert(argv[i + 1]);
				int maxLines = 0;
				convert >> maxLines;
				Subtitle::setMaxLines(maxLines);
				i++;
			}
			else if (currentArg == "-c") {
				//Creates a stringstream called convert from the next argument and converts it to an integer.
				std::stringstream convert(argv[i + 1]);
				int maxChars = 0;
				convert >> maxChars;
				Subtitle::setMaxChars(maxChars);
				i++;
			}
			else {
				//The loop has found the file name to use and assigns it to the variable we defined earlier, so that we can return it when the function ends.
				filename = currentArg;
			}
		}
		std::ifstream inputFile;
		inputFile.open(filename);
		std::vector<Subtitle> subs;
		/*if (inputFile.good()) {
			//Checks whether the file exists
			unsigned parsedLine = 0, subtitles = 0;
			std::chrono::system_clock::time_point startingTime = std::chrono::system_clock::now();
			while (!inputFile.eof()) {
				subs.push_back(Subtitle(inputFile, parsedLine));
				subtitles++;
				parsedLine++;
			}
			std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
			std::chrono::milliseconds timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startingTime);
			std::cout << "Done parsing " << parsedLine + 1 << " lines in " << timeTaken.count() << " ms." << std::endl << "Found " << subtitles << " subtitles.";
			std::cout << "Would you like to output all subtitles to the console? (y/n) ";
			char choice;
			std::cin >> choice;
			if (choice == 'y') {
				for (unsigned i = 0; i < subtitles - 1; i++) {
					std::cout << subs[i];
				}
			}
		}
		else
		{
			std::cout << err::file_not_exists.description;
			return err::file_not_exists.id;
		}

		inputFile.close();
		std::cout << err::ok.description;
		return err::ok.id;
	}*/
	}
}