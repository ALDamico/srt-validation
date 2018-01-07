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

//Includes
#include <iostream> //mostly used for error reporting
#include <fstream> //required for input-output operations on files
#include <string> //required for the Subtitle class
#include <vector> //The various subtitles are represented in memory through a vector
#include <sstream> //Required for converting command line arguments to numeric values
#include <chrono>
#include "error_codes.h" //Error codes used by this program
#include "Subtitle.h" //Class subtitle, with << operator overload for displaying 


std::string argParse(int argc, char *argv[]) {
	//Analyzes and parses the command line arguments passed to the application. Returns a string (the file to open).

		//Determine if the first option is -h and print the usage message. All other parameters are ignored.
	if (static_cast<std::string>(argv[1]) == "-h") {
		std::cout << "Usage:" << std::endl
			<< "srtvalidate [-h] FILENAME [-p|-a] [-l #] [-c #]" << std::endl
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

	//Initialize the string where we're going to put the file name.
	std::string filename;

	//Scan the entire array of C strings and sets various things.
	for (int i = 1; i < argc; i++) {
		std::string currentArg = argv[i];
		if (currentArg == "-p") {
			//Add code relevant to performance mode
		}
		else if (currentArg == "-a") {
			//Add code relevant to performance mode. Maybe I just need to set a bool to true? Or maybe we can create a static int variable inside the Subtitle class?
		}
		else if (currentArg == "-l") {
			//Creates a stringstream called convert from the next argument and converts it to an integer.
			std::stringstream convert(argv[i + 1]);
			convert >> Subtitle::maxLines;
			i++;
		}
		else if (currentArg == "-c") {
			//Creates a stringstream called convert from the next argument and converts it to an integer.
			std::stringstream convert(argv[i + 1]);
			convert >> Subtitle::maxChars;
			i++;
		}
		else {
			//The loop has found the file name to use and assigns it to the variable we defined earlier, so that we can return it when the function ends.
			filename = currentArg;
		}
	}
	return filename;
}

int main(int argc, char *argv[]) {
	{
		std::string filename = argParse(argc, argv);
		std::ifstream inputFile;
		inputFile.open(filename);
		std::vector<Subtitle> subs;
		if (inputFile.good()) {
			//Checks whether the file exists
			unsigned parsedLine = 0, subtitles = 0;
			std::chrono::system_clock::time_point startingTime = std::chrono::system_clock::now();
			while (!inputFile.eof()) {
				subs.push_back(Subtitle(inputFile, parsedLine));
				subtitles++;
				parsedLine++;
			}
			std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> timeTaken = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startingTime);
			std::cout << "Done parsing " << parsedLine+1 << " lines in " << timeTaken.count() << " seconds." << std::endl << "Found " << subtitles << " subtitles.";
			std::cout << "Would you like to output all subtitles to the console? (y/n) ";
			char choice;
			std::cin >> choice;
			if (choice == 'y') {
				for (int i = 0; i < subtitles; i++) {
					std::cout << subs[i];
				}
			}
		}
		else {
			std::cout << err::file_not_exists.description;
			return err::file_not_exists.id;
		}
		
		inputFile.close();
		std::cout << err::ok.description;
		return err::ok.id;
	}
}