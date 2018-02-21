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
@author Andrea Luciano Damico
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
		std::chrono::system_clock::time_point readBegin = std::chrono::system_clock::now();
		unsigned parsedLine = 0, subtitles = 0;
		bool dirtyBit = false;
		std::vector<std::string>currentBatch;
		if (inputFile.good()) {
			//Variable where the current line is stored
			std::string currentLine;
			//Main read loop
			while (!inputFile.eof()) {
				subtitles++;
				//This loops fetches lines in the input file until it reaches an empty line
				do {
					getline(inputFile, currentLine);
					currentBatch.push_back(currentLine);
					parsedLine++;
				}
				while (currentLine != "");
				//We pass the vector we just created to a ctor.
				subs.push_back(Subtitle(currentBatch));
				if (dirtyBit == true) {
					subs[subtitles].setTrailingNewLineState(true);
					dirtyBit = false;
				}
				//Clear the currentBatch so that the loop can start anew.
				currentBatch.clear();
			}
		}
		else
		{
			std::cout << err::file_not_exists.description;
			return err::file_not_exists.id;
		}
		inputFile.close();
		std::chrono::system_clock::time_point readEnd = std::chrono::system_clock::now();
		std::chrono::milliseconds timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(readEnd - readBegin);
		std::cout << "Done parsing " << parsedLine << " lines in " << timeTaken.count() << " ms." << std::endl
			<< "Found " << subtitles + 1 << " subtitles." << std::endl;
		for (unsigned i = 0; i < subtitles; i++) {
			subs[i].checkTags();
			subs[i].checkLineLength();
		}
		getchar();
		std::cout << err::ok.description;
		return err::ok.id;
	}
}