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
///@file Subtitle.h
/// \brief Declaration file for type Subtitle.
///
/// @author Andrea Luciano Damico
///
/// This file contains the declarations for the Subtitle class, which acts as the representation of each individual subtitle inside the program's logic.
///

#pragma once
#include <string>//Used to store the subtitles read from the input file
#include <vector>//Used to allocate a dynamic vector of type Subtitle
#include <fstream>//Used to read from the input file and optionally to output a report.
#include <sstream>//Used to convert strings to integers. @see Subtitle
#include <regex>
#include "Time.h"

class Subtitle
{
public:
	/*Constructors and destructors*/
	Subtitle();
	Subtitle(std::vector<std::string>);
	~Subtitle();

	/*Public methods*/
	int getID();
	void setID(int);
	Time getStartTime();
	void setStartTime(Time);
	Time getEndTime();
	void setEndTime(Time);
	bool checkTags();
	bool getTrailingNewLineState();
	void setTrailingNewLineState();
	bool checkLineLength();
	bool checkLineNumber();
	bool checkTrailingNewLine();
	static void setMaxLines(unsigned);
	static void setMaxChars(unsigned);
	static int getMaxLines();
	static int getMaxChars();

	friend std::ostream& operator<< (std::ostream&, const Subtitle&);
private:
	int id;
	Time startTime;
	Time endTime;
	std::vector<std::string> lines;
	//A boolean used to keep track of whether this object and the next are separated by an empty line.
	//It's only set by the constructor, but we provide a member function to get its value.
	bool missingTrailingNewLine = false;
	static int maxLines;
	static int maxChars;
};
