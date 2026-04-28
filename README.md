
# Programming for Engineers Coursework

Power Quality Waveform Analyser written in C (C99).

## Description
This program reads a CSV file containing three-phase power quality data
and calculates RMS voltage, peak-to-peak values, DC offset, and clipping.

##notes for main.c 

it needs to Accept the filename as a command-line argument (argc, argv)
Call load_csv()
Call all your analysis functions
Call write_results()
free() the allocated memory

