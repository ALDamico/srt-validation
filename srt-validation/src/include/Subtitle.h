/*
SRT VALIDATOR VERSION 1.0
Author: Andrea Luciano Damico
Creation date: 03/01/2018

Description: This file contains the class declaration. Definitions are found in Subtitle.cpp

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

///
/// \brief Declaration file for type Subtitle.
///
/// This file contains the declarations for the Subtitle class, which acts as the representation of each individual subtitle inside the program's logic
///

#pragma once
#include <string>//Used to store the subtitles read from the input file
#include <vector>//Used to allocate a dynamic vector of type Subtitle
#include <fstream>//Used to read from the input file and optionally to output a report.
#include <sstream>//Used to convert strings to integers. @see Subtitle

class Subtitle
{
public:
	///Default constructor that inizializes every field in the instance with zeroes or empty strings.
	Subtitle();
	///Constructor as used in the main.cpp file. It takes a reference to ifstream and an unsigned long representing the current line and populates the correct field.
	Subtitle(std::ifstream &, unsigned int &);/**<@param	ifstream&	file	The input file as read from the main function, passed as reference.
											  *<@param	unsigned&	_current_line	The current line read by the main function, passed as reference.*/
	///Default destructor. Currently empty-bodied.
	~Subtitle();

	/*Public methods*/
	///Gets the id of the current subtitle.
	int getID();///\return The id of the current subtitle.
	///Sets the id of the current subtitle.
	void setID(int);///<@param _id The id to be assigned to the current subtitle.
	///Gets the starting time of the current subtitle.
	std::string getStartTime();
	///Sets the starting time of the current subtitle.
	void setStartTime(std::string);///<@param 
	///Gets the ending time of the current subtitle.
	std::string getEndTime();
	///Sets the ending time of the current subtitle.
	void setEndTime(std::string);
	///Checks if there are any unmatched tags in the current subtitle.
	bool checkTags();
	bool getTrailingNewLineState();
	static void setMaxLines(int);
	static void setMaxChars(int);
	static int getMaxLines();
	static int getMaxChars();
	friend std::ostream& operator<< (std::ostream&, const Subtitle&);
private:
	int id;
	std::string startTime;
	std::string endTime;
	std::vector<std::string> lines;
	//A boolean used to keep track of whether this object and the next are separated by an empty line.
	//It's only set by the constructor, but we provide a member function to get its value.
	bool missingTrailingNewLine = false;
	static int maxLines;
	static int maxChars;
};
