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
* @author Andrea Luciano Damico
*/

#include "Subtitle.h"

/*!
*@brief Extracts an element of type Time from a stringstream.
*
* This *external* function takes a string as its argument and returns an object of type Time. It does so by taking
* extracting the first two characters from starting position (pos), skips the character where the ":" would be and
* repeats the same with seconds and milliseconds. Note that this function *does not* check whether the stringstream has
* a suitable structure. The programmer is in charge of making sure she's passing the correct type of stringstream.
*
*@param in The input string.
*@param pos The starting position of the extraction process. In the application, we pass it two constants, START_TIME_INITIAL_POS and END_TIME_INITIAL_POS.
*@return An object of type Time
*/
Time stringToTime(std::string in, unsigned pos) {
	std::stringstream inStream(in);
	std::stringstream hours, minutes, seconds, milliseconds;
	hours << in.substr(pos, 2);
	pos += 3;
	minutes << in.substr(pos, 2);
	pos += 3;
	seconds << in.substr(pos, 2);
	pos += 3;
	milliseconds << in.substr(pos, 3);
	int hoursInt, minutesInt, secondsInt, millisecondsInt;
	hours >> hoursInt;
	minutes >> minutesInt;
	seconds >> secondsInt;
	milliseconds >> millisecondsInt;
	return Time(hoursInt, minutesInt, secondsInt, millisecondsInt);
}

///@brief Two constants used to determine the starting position in lines containing start and end times.
const int START_TIME_INITIAL_POS = 0, END_TIME_INITIAL_POS = 17;

///
/// @brief Default constructor.
///
/// Initializes the subtitle object with invalid (null) values.
///
/// This constructor is actually never called in the program, so it mostly amounts to boilerplate code.
///
Subtitle::Subtitle() {
	
	id = 0;
	startTime = Time(0, 0, 0, 0);
	endTime = Time(0, 0, 0, 0);
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
		setStartTime(stringToTime(param[1], START_TIME_INITIAL_POS));
		setEndTime(stringToTime(param[1], END_TIME_INITIAL_POS));
		for (unsigned i = 2; i < param.capacity(); i++) {
			this->lines.push_back(param[i]);
		}
		missingTrailingNewLine = false;
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
	os << "ID:\t\t" << sub.id << std::endl
		<< "Start time:\t" << sub.startTime << std::endl
		<< "End time:\t" << sub.endTime << std::endl << std::endl;
	for (unsigned i = 0; i < sub.lines.capacity(); i++) {
		os << "Line " << i << ": " << sub.lines[i] << std::endl;
	}
	return os;
}

/*!
* @brief Check whether this Subtitle is properly ended (with an empty string as its last line) or not.
*
* @return A boolean that indicates if the last element of lines[] is an empty string or not.
*/
bool Subtitle::getTrailingNewLineState() {
	return missingTrailingNewLine;
}
/*!
* @brief Sets the appropriate missingTrailNewLine value based on the last element in lines[].
*
* @see getTraililngNewLineState()
* @see missingTrailingNewLine
*/
void Subtitle::setTrailingNewLineState()
{
	if (lines[lines.capacity() - 1] == "")
		missingTrailingNewLine = true;
	else
		missingTrailingNewLine = false;
}

/*!
* @brief Checks the length of *all* lines inside this object and returns a bool that indicates if they *all* are below the recommended length.
*
* @b *IMPORTANT*: Right now, checkLineLength() does *NOT* support tags (they're not ignored but treated as if they're real characters).
*
* @return True if all lengths < maxChars, False otherwise.
*/
bool Subtitle::checkLineLength(std::ostream& os)
{
	/*!
	* If cleanBit is clean, the length doesn't exceed Subtitle::maxChars.
	*/
	bool cleanBit = true;
	for (unsigned i = 0; i < lines.capacity() - 1; i++) {
		if (lines[i].length() > Subtitle::maxChars) {
			cleanBit = false;
			os << "Line " << i << " in subtitle n. " << this->id << " is too long: " << lines[i].length() << " characters, should be " << Subtitle::maxChars << "." << std::endl
				<< lines[i] << std::endl;
			for (int i = 0; i < Subtitle::maxChars; i++) {
				os << " ";
			}
			os << "^" << std::endl;
		}
	}
	if (!cleanBit) {
		return false;
	}
	return true;
}
bool Subtitle::checkLineNumber()
{
	if (lines.capacity() <= Subtitle::maxLines)
		return true;
	return false;
}

/*!
* @brief Checks for mismatches in the tags.
*
* This method checks for mismatches in a subtitle's tags by performing regex matches against its lines.
* Supports the following tags:
* - <b> @b bold tag;
* - <i> @e italic tag;
* - <u> underlined tag;
* - <font> font color;
*
* @return True if all tags are properly matched, false otherwise.
*/
bool Subtitle::checkTags(std::ostream& os) {
	const std::regex BOLD_TAG_OPEN("(.*)<b>(.*)");
	const std::regex BOLD_TAG_CLOSED("(.*)</b>(.*)");
	const std::regex ITALIC_TAG_OPEN("(.*)<i>(.*)");
	const std::regex ITALIC_TAG_CLOSED("(.*)</i>(.*)");
	const std::regex UNDERLINED_TAG_OPEN("(.*)<u>(.*)");
	const std::regex UNDERLINED_TAG_CLOSED("(.*)</f>(.*)");
	const std::regex FOND_TAG_OPEN("(.*)(<font=#)([0-9]|[A-F]|[a-f]{6}>)(.*)");
	const std::regex FONT_TAG_CLOSED("(.*)</font>(.*)");
	//Counters for the various types of tags.
	int boldTagOpenCount =			0,  
		boldTagClosedCount =		0, 
		italicTagClosedCount =		0, 
		italicTagOpenCount =		0, 
		underlinedTagOpenCount =	0, 
		underlinedTagClosedCount =	0;
	bool cleanBit = true;
	for (unsigned i = 0; i < lines.capacity() - 1; i++) {
		if (std::regex_match(lines[i], BOLD_TAG_OPEN)) {
			boldTagOpenCount++;
		}
		if (std::regex_match(lines[i], BOLD_TAG_CLOSED)) {
			boldTagClosedCount++;
		}
		if (std::regex_match(lines[i], ITALIC_TAG_OPEN)) {
			italicTagOpenCount++;
		}
		if (std::regex_match(lines[i], ITALIC_TAG_CLOSED)) {
			italicTagClosedCount++;
		}
		if (std::regex_match(lines[i], UNDERLINED_TAG_OPEN)) {
			underlinedTagOpenCount++;
		}
		if (std::regex_match(lines[i], UNDERLINED_TAG_CLOSED)) {
			underlinedTagClosedCount++;
		}
	}
	if (boldTagClosedCount - boldTagOpenCount != 0) {
		os << "Bold tag mismatch in subtitle " << this->id << std::endl;
		cleanBit = false;
	}
	if (italicTagClosedCount - italicTagOpenCount != 0) {
		os << "Italic tag mismatch in subtitle " << this->id << std::endl;
		cleanBit = false;
	}
	if (underlinedTagClosedCount - underlinedTagOpenCount) {
		os << "Underlined tag mismatch in subtitle " << this->id << std::endl;
		cleanBit = false;
	}
	if (!cleanBit) {
		os << *this << std::endl;
	}
	return cleanBit;
}

/*!
* @brief Sets the value of maxChars.
*
* @param maxChars The (unsigned) value to assign to the maxChars static variable.
*/
void Subtitle::setMaxChars(unsigned maxChars) {
	Subtitle::maxChars = maxChars;
}

/*!
* @brief Gets the value of maxLines.
*
* maxLines should account for an extra empty line to mark the end of the subtitle, otherwise missingTrailingNewLine is set to true and an error is logged.
*
* @return The maximum number of allowed lines in a subtitle (default: 3).
*/
int Subtitle::getMaxLines() {
	return Subtitle::maxLines;
}

int Subtitle::getMaxChars()
{
	return Subtitle::maxChars;
}

/*!
* @brief Sets the value of maxLines.
*
* maxLines should account for an extra empty line to mark the end of the subtitle, otherwise missingTrailingNewLine is set to true and an error is logged.
*/
void Subtitle::setMaxLines(unsigned maxLines) {
	Subtitle::maxLines = maxLines;
}

