# srt-validation

srt-validation aims to be a small and simple command-line utility that scans subtitles in SRT format and checks for various errors.
This is accomplished by reading a file and checking for the following:
1. Number of characters per line;
2. Number of lines for each subtitle;
3. Checking for overlapping subtitles;
4. Checking for mismatched tags;
5. Checking for missing empty lines after a subtitle.

# How to install
srt-validation is still a work-in-progress. This section will be updated once the code is in a usable form.

# Usage
After completion, srt-validate will support the following command-line options:
1. -h</br>
  Prints an usage message and exits;
2. -p</br>
  <b>Performance mode</b>. Each subtitle is checked <i>only</i> against the subtitle that immediately follows it.
3. -a</br>
  <b>Accurate mode</b>. Each subtitle is checked against <i>all</i> the subtitles that follow it.
4. -l <i>number of lines per subtitle</i></br>
  Sets the <b>maximum numbers of lines per subtitle</b>. There are more lines per subtitle than this number, an error message is printed to the console.
5. -c <i>number of characters per line</i></br>
  Sets the <b>maximum number of characters per line</b>. If a line length exceeds this threshold, an error message is printed to the console.
  
Note that at the time of this writing not all command-line options are supported.
