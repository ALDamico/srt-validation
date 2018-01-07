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

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Subtitle
{
public:
	Subtitle();//Default constructor
	Subtitle(std::ifstream &, unsigned int &);

	~Subtitle();
	int get_id();
	void set_id(int _id);
	std::string get_startTime();
	void set_startTime(std::string);
	std::string get_endTime();
	void set_endTime(std::string);
	//These two static variables are declared as public to allow them to be initialized
	//directly in main()
	static int maxLines;
	static int maxChars;
	////////////////////////////////////////////
	friend std::ostream& operator<< (std::ostream&, const Subtitle&);
private:
	int id;
	std::string startTime;
	std::string endTime;
	std::vector<std::string> lines;
	
};
