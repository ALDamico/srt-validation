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
#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>

/**
*@file Time.h
*@class Time
*@brief A class used to represent time codes in a subtitle.
*
* Time.h allows to represent time codes in a subtitle as minutes, seconds and milliseconds.
* It contains three std::chrono::time_point private members and two operator overloadings.
*/
class Time
{
public:
	Time();
	Time(int, int, int, int);
	bool operator>(Time&);
	friend std::ostream& operator<< (std::ostream&, const Time&);
private:
	///@brief Number of hours.
	std::chrono::hours hours;
	///@brief Number of minutes.
	std::chrono::minutes minutes;
	///@brief Number of seconds.
	std::chrono::seconds seconds;
	///@brief Number of milliseconds.
	std::chrono::milliseconds milliseconds;
};
