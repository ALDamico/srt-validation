# srt-validation

srt-validation aims to be a small and simple command-line utility that scans subtitles in SRT format and checks for various errors.
This is accomplished by reading a file and checking for the following:
1. Number of characters per line;
2. Number of lines for each subtitle;
3. Checking for overlapping subtitles;
4. Checking for mismatched tags;
5. Checking for missing empty lines after a subtitle.

# How to install
There is no need to install srt-validation: just copy the executable somewhere, open a Command Prompt window, cd to the executable's path, and run it by typing srt-validation FILENAME
You may want to add it to your system's PATH environment variable. In this case, open a PowerShell window *with administrative privileges* and use the command 
  setx PATH "$env:path;PATH/TO/SRT-VALIDATION" -m
then restart PowerShell and you're good to go.

# Usage
srt-validation supports the following command-line arguments:
1. -h</br>
  Prints an usage message and exits;
2. -l <i>number of lines per subtitle</i></br>
  Sets the <b>maximum numbers of lines per subtitle</b>. There are more lines per subtitle than this number, an error message is printed to the console.
3. -c <i>number of characters per line</i></br>
  Sets the <b>maximum number of characters per line</b>. If a line length exceeds this threshold, an error message is printed to the console.
4. -t <i>character per line tolerance</i></br>
  Specifies how much extra characters per line the application will tolerate.
