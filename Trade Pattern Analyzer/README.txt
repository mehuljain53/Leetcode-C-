Price pattern detector
----------------------

The goal is to write a price pattern detector class in C++.

1. Definitions

Price - positive value of type 'double', representing a stock price.
Price stream - a sequence of prices ordered in time.

*** A .csv file (sample_input.csv) containing a price stream is included with this project.
Each record in this file has time,price format. The records are ordered in time.
Time format is HH:MM:SS.mmm   (millisecond precision)
Price is a floating-point value with precision up to 2 digits after the decimal point.

Time is not used in baseline assignment.

Price pattern - a sub-sequence of values from the price stream that constitutes one or more
values repeating multiple times (greated than 1) consecutively.
A pattern is characterized by pattern length (number of price values) and number of repetitions.

Price pattern examples:

The input price stream 1 2 1 2 1 1 1 3 3 (integer values for simplicity)

For patterns of length 1
- has a repeating pattern of [1] (3 repetitions): 1 2 1 2 (1) (1) (1) 3 3
- has a repeating pattern of [3] (2 repetitions): 1 2 1 2 1 1 1 (3) (3)

For patterns of length 2
- has a repeating pattern of [1 2] (2 repetitions): (1 2) (1 2) 1 1 1 3 3
- has a repeating pattern of [2 1] (2 repetitions): 1 (2 1) (2 1) 1 1 3 3

2. Assignment

Write a price pattern detector - a module that should implement pattern detection functionality.
PatternDetector skeleton class is included with the assignment.
PatternDetector is parameterized (via constructor) with pattern length and number of repetitions.
PatternDetector should implement the following function:

   bool detectPattern(string time, double price)

It should work as following:

Price values from the input price stream are fed into pattern detector's detectPattern(..) function one by one.
The function should return true if the price value completes a pattern that satisfies the detector's parameters.

Examples:

Sample Input/Output (using the sample price sequence as above)
pattern_length=1,
number_of_repetitions=2:
price stream:   1 2 1 2 1 1 1 3 3
detectPattern:  F F F F F T T F T  (F=False, T=True)

pattern_length=2,
number_of_repetitions=2:
price stream:   1 2 1 2 1 1 1 3 3
detectPattern:  F F F T T F F F F

Requirements:

You should modify PatternDetector to implement the functionality described above.
The final code should compile, run and produce valid output.

Makefile is included. main() function is provided in main.cpp.
There is no need to change this function, but it should be studied to understand how the PatternDetector class is used.
Feel free to start by compiling and running PatternDetector as following:

*** Do not modify the format of the output in the main function.

[dir]/make
[dir]/PatternDetector
Running with no parameters will print usage.

Try running as following:
[dir]/PatternDetector 2 2 sample_input.csv
This should print out results of running the sample_input.csv stream through the default PatternDetector implementation.

Bonus.

For bonus points, enhance PatternDetector to work with time. Introduce a new time window parameter (in milliseconds) into the detector and main function.
All the samples in sample_input.csv have a timestamp of millisecond precision. The detectPattern function already accepts time and price.
Time window affects the way a pattern is recognized.
Price samples that satisfy the detector parameters heave to be within the time window in *milliseconds*. In other words, in determining if
a price completes a pattern, detectPattern(..) has to consider how old previous prices are and disregard those older than time window.
The usage for the time window functionality should be:

>  [dir]/PatternDetector [pattern length] [repetition count] [input file] [time window]

Note that the original, 3-argument usage must still work with this version! Running PatternDetector without the time window argument
should simply process the input without considering time windows. Additionally, providing a time window argument of 0 should result
in ignoring the time window.


Good luck!

