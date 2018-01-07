/*
SRT VALIDATOR VERSION 1.0
Author: Andrea Luciano Damico
Creation date: 03/01/2018

description: This header file contains the namespace ERR, which is where error codes exists.
			 Error codes are implemented as structs with two members: id, a numeric error code, and 
			 description, a constant string containing a brief description of the issue.
			 Note that we use ERR::OK.id in place of EXIT_SUCCESS.

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
namespace err {
	struct ok {
		const int id = 0;
		const std::string description = "The operation has been completed successfully.";
	} ok;

	struct file_not_exists {
		const int id = 1;
		const std::string description = "Unable to read file. Check if file exists, if you have enough privileges to read it, or make sure it's not opened in another application and try again.";
	} file_not_exists;
	
	struct unable_to_write {
		const int id = 2;
		const std::string description = "Unable to write to output file. Check if you have enough privileges to write to this location, make sure that the file isn't open in another application and try again.";
	} unable_to_write;
	
	struct invalid_file {
		const int id = 3;
		const std::string description = "Error. Not a valid SRT file.";
	} invalid_file;
}