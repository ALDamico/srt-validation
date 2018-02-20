/*
SRT VALIDATOR VERSION 1.0
Author: Andrea Luciano Damico
Creation date: 03/01/2018

Description: This file contains member function definitions and static member assignments for
			 the Subtitle.h file.

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
* @file Subtitle.cpp
*
*/

#include "Subtitle.h"

///
/// @brief Default constructor.
///
/// Initializes the subtitle object with invalid (null) values.
///
/// This constructor is actually never called in the program, so it mostly amounts to boilerplate code.
///
Subtitle::Subtitle() {
	
	id = 0;
	startTime = Time(0, 0, 0);
	endTime = Time(0, 0, 0);
	lines.push_back("");
}

/*!
*@brief A constructor that takes a vector of strings as its argument and populates the subtitle accordingly.
*
*This constructor assigns the first element of the vector to the ID, the second is processed into two elements of type Time and the rest is assigned to a vector of strings.
*
*@param param A vector of strings used to construct the object.
*/
Subtitle::Subtitle(std::vector<std::string> param) {
	if (param.capacity() > 2) {
		std::stringstream convert(param[0]);
		convert >> this->id;
		convert.str("");
		convert.str(param[1]);
		for (unsigned i = 2; i < param.capacity(); i++) {
			this->lines.push_back(param[i]);
		}
	}
	else {
		Subtitle();
	}
}

///
///@brief Default destructor. Currently empty-bodied.
///
Subtitle::~Subtitle() {
}

///
///Gets the id of the current subtitle.
///@return The id of the current subtitle.
///
int Subtitle::getID() {
	return id;
}

///
///Sets the id of the current subtitle.
///@param id The id to assign to the subtitle.
///@return Void.
///
void Subtitle::setID(int id) {
	this->id = id;
}

///
///Gets the starting time of the current subtitle.
///@return The starting time of the current subtitle.
///
Time Subtitle::getStartTime() {
	return startTime;
}

///
///Sets the starting time of the current subtitle.
///@param startTime The starting time to assign to the subtitle.
///@return Void.
///
void Subtitle::setStartTime(Time startTime) {
	this->startTime = startTime;
}

///
///Gets the ending time of the current subtitle.
///@return A string with the ending time of the current subtitle.
///
Time Subtitle::getEndTime() {
	return endTime;
}

///
///Sets the ending time of the current subtitle.
///@param endTime The ending time we assign to the subtitle.
///@return Void.
///
void Subtitle::setEndTime(Time endTime) {
	this->endTime = endTime;
}

///
///@brief The maximum number of lines per subtitle. This number *also includes* the empty line used to mark the end of a subtitle in an SRT file.
///
int Subtitle::maxLines = 3;
///
///@brief The maximum number of characters per line.
///
int Subtitle::maxChars = 42;

///
///@brief Overloading of << for class Subtitle.
///
///Allows using << with an output stream as to make easier outputting the content of a subtitle to the console.
///@param os An ostream passed as reference.
///@param sub A Subtitle passed as constant reference, so that the function can't inadvertently modify it.
///@return A reference to an ostream.
///
std::ostream& operator<<(std::ostream& os, const Subtitle& sub) {
	os << "ID: " << sub.id << std::endl
		//<< "Start time: "; << sub.startTime << std::endl
		<< "End time: " << sub.endTime;
	for (unsigned i = 0; i < sub.lines.capacity(); i++) {
		os << "Line " << i << ": " << sub.lines[i] << std::endl;
	}
	return os;
}

///@brief 
bool Subtitle::getTrailingNewLineState() {
	return missingTrailingNewLine;
}

bool Subtitle::checkTags() {
	for (unsigned line = 0; line < lines.capacity(); line++) {
		for (unsigned pos = 0; pos < lines[line].length(); pos++) {
			if (lines[line][pos] == '<') {

			}
		}
	}
	return true;
}

void Subtitle::setMaxChars(int maxChars) {
	Subtitle::maxChars = maxChars;
}

void Subtitle::setMaxLines(int maxLines) {
	Subtitle::maxLines = maxLines;
}