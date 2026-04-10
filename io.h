
#ifndef PROGRAMMINGCOURSEWORK_IO_H
#define PROGRAMMINGCOURSEWORK_IO_H

#include "waveform.h"
#include <stdio.h>

//just to load data from the csv
int load_data(const char *filename, WaveformSample *data, int num_rows);

void export_report(cont char *filename, double rmsA, double rmsB, double rmsC); //root mean square for phase a,b,c
#endif //PROGRAMMINGCOURSEWORK_IO_H
