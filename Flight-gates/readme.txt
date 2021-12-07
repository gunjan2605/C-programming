Problem statement - 


The provided file includes information for all domestic flights flying into or out of the Atlanta airport (ATL) on November 9, 2015. The file includes information on 2,208 flights, one flight per line. Each line consists of six fields separated by commas. As an example, the first line is as follows.DL,2561,ABE,ATL,600,818The six fields, from left to right, have the following explanations.• Two-letter airline code• Flight number (integer, maximum of 4 digits)• Three-letter code for departure airport• Three-letter code for arrival airport• Scheduled departure time, given in a modified “military style” (no colon to separate hours and minutes, times ranging from 0 to 2359 without am/pm designations)• Scheduled arrival time (same style as for scheduled departure time)Your task is to write a C program to determine1. how many gates (or, equivalently, how many airplanes) are needed to handle arrival and departure traffic at the ATL airport within the 24-hour period and2. how many airplanes should be parked at ATL gates by midnight to ensure there are enough planes to accommodate the flight schedule for the following 24 hours.


Running Instructions - 
Compiler used: GCC 
OS used: macOS Big Sur Version 11.2.2
Running Instructions: 
1. Download and save the file in appropriate folder 
2. Open terminal window 
3. Open the desired folder through the terminal window
4. To compile the program, type "gcc - o <name> gates.c". This command creates an executable file of the name - <name>.out 
5. You can run this program with the following 3 inputs - 

To run this executable file using default insertion sort type ./<name>
To run this executable file using merge sort type file type ./<name> m
To run this executable file using count sort type file type ./<name> c

6. This should display the output in the terminal 