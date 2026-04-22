
#ifndef PROGRAMMINGCOURSEWORK_IO_H
#define PROGRAMMINGCOURSEWORK_IO_H

#include "waveform.h"
#include <stdio.h>

//just to load data from the csv
int load_data(const char *filename, WaveformSample *data, int num_rows);
