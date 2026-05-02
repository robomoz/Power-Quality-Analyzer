
#ifndef PROGRAMMINGCOURSEWORK_IO_H
#define PROGRAMMINGCOURSEWORK_IO_H

#include "waveform.h"
#include <stdio.h>

int load_csv(const char *filename, WaveformSample **samples_out); //reads the csv file and loads the data into the samples array, returns the number of rows loaded

void write_results(const char *filename, const WaveformSample *samples, int count); //calculates all metrics and writes the full results report to a text file

#endif
//ends the header guard started at the top of the file


