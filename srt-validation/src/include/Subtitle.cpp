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
*/

#include "Subtitle.h"

Subtitle::Subtitle() {
	//Initializes the subtitle object with invalid (null) values.
	//This constructor is actually never called in the program, so it mostly amounts to boilerplate code.
	id = 0;
	startTime = "";
	endTime = "";
	lines.push_back("");
}

Subtitle::Subtitle(std::ifstream& file, unsigned& _current_line) {
	//The constructor as actually called by the program. It takes a reference to an input file stream and reads
	//its content
	std::string line;
	getline(file, line);
	_current_line++;
	std::stringstream convert(line);
	convert >> id;
	convert.clear();
	/*
		TODO: IMPLEMENT CONVERSION FROM THE LINE TO START TIME AND END TIME
	*/
	int isNewIDReached = id;
	do {
		getline(file, line);
		_current_line++;
		lines.push_back(line);
		convert << line;
		convert >> isNewIDReached;
		convert.str("");
	} while (line != "" && isNewIDReached > id);
	if (isNewIDReached > id)
		missingTrailingNewLine = true;
}

Subtitle::~Subtitle() {
}

int Subtitle::getID() {
	return id;
}

void Subtitle::setID(int id) {
	this->id = id;
}

std::string Subtitle::getStartTime() {
	return startTime;
}

void Subtitle::setStartTime(std::string startTime) {
	this->startTime = startTime;
}

std::string Subtitle::getEndTime() {
	return endTime;
}

void Subtitle::setEndTime(std::string endTime) {
	this->endTime = endTime;
}

//Default values for the static variables.
int Subtitle::maxLines = 3;
int Subtitle::maxChars = 42;

std::ostream & operator<<(std::ostream& os, const Subtitle& sub) {
	os << "ID: " << sub.id << std::endl
		<< "Start time: " << sub.startTime << std::endl
		<< "End time: " << sub.endTime;
	for (unsigned i = 0; i < sub.lines.capacity(); i++) {
		os << "Line " << i << ": " << sub.lines[i] << std::endl;
	}
	return os;
}

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