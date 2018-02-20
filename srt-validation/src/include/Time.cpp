/*
SRT VALIDATOR VERSION 1.0
Author: Andrea Luciano Damico
Creation date: 19/02/2018

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
#include "Time.h"

/**
* @brief Time default constructor
*
* Inizializes the time as 00:00.000
*/
Time::Time() {
	this->minutes = (std::chrono::minutes)0;
	this->seconds = (std::chrono::seconds)0;
	this->milliseconds = (std::chrono::milliseconds)0;
}

/**
*@brief Time normal constructor
*
* Inizializes the time with three integer values
* @param minutes Number of minutes.
* @param seconds Number of seconds.
* @param milliseconds Number of milliseconds.
*/
Time::Time(int minutes, int seconds, int milliseconds) {
	this->minutes = (std::chrono::minutes) minutes;
	this->seconds = (std::chrono::seconds) seconds;
	this->milliseconds = (std::chrono::milliseconds) milliseconds;
}

/**
*@brief Overloading of operator > for comparisons
*
*The operator > can be used to compare two of these times. This is useful when checking for overlapping subtitles.
*@param tm The right-hand operand.
*/
bool Time::operator>(Time& tm) {
	if (this->minutes > tm.minutes) {
		return true;
	} 
	else if (this->seconds > tm.seconds) {
		return true;
	}
	else if (this->milliseconds > tm.milliseconds) {
		return true;
	}
	return false;
}

/**
*@brief Overloading of operator << for ostream
*
*This member function allows us to use our Time class with ostreams. It prints the number of minutes, seconds and milliseconds separated by their respective a ":" and a ".", respectively.
@param os A reference to an ostream.
*/
std::ostream& operator<<(std::ostream& os, const Time& tm)  {
	return os << tm.minutes.count() << ":" << tm.seconds.count() << "." << tm.milliseconds.count();
}