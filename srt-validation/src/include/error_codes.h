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

/// \file error_codes.h
/// \brief The header file where error codes (and descriptions) for srt-validation are defined.
/// This header file lists a series of structs inside the namespace err.

/// \namespace err
/// \brief Namespace err contains a bunch of structs used to represent error codes and brief descriptions thereof.
///
/// Inside namespace err are stored a series of structs.
/// Their content is similar: each of them consists of a const int and a const string.
/// The int represents the error code associated with that specific struct, whereas the string is a brief description of the error status.
/// For each struct listed, an item is istantiated, allowing us to use them in the main.cpp file.
/// @see main.cpp
///

namespace err {
	struct ok {
		///Error code associated with correct execution of the program.
		const int id = 0;
		///Brief description of the error code.
		const std::string description = "The operation has been completed successfully.";
	} ok; ///<Item declared in the err namespace.

	struct file_not_exists {
		///Error code raised when the program is not able to read the input file.
		const int id = 1;
		///Brief description of the error code.
		const std::string description = "Unable to read file. Check if file exists, if you have enough privileges to read it, or make sure it's not opened in another application and try again."; ///Brief description of the error code.
	} file_not_exists; ///<Item declared in the err namespace. 
	
	struct unable_to_write {
		///Error code raised when the program is unable to write to an output file.
		const int id = 2; 
		///Brief description of the error code.
		const std::string description = "Unable to write to output file. Check if you have enough privileges to write to this location, make sure that the file isn't open in another application and try again.";///Brief description of the error code.
	} unable_to_write; ///<Item declared in the err namespace.
	
	struct invalid_file {
		///Error code raised when the program does not recognize the input file as a valid SRT file.
		const int id = 3;
		///Brief description of the error code.
		const std::string description = "Error. Not a valid SRT file.";
	} 	invalid_file; ///<Item declared in the err namespace.
}