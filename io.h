
#ifndef PROGRAMMINGCOURSEWORK_IO_H
#define PROGRAMMINGCOURSEWORK_IO_H

#include "waveform.h"
#include <stdio.h>

//just to load data from the csv
int load_data(const char *filename, WaveformSample **samples, int *count);
int write_results(const char *filename, double rmsA, double rmsB, double rmsC
                  double p2pA, double p2pB, double p2pC,
                  double dcA, double dcB, double dcC,
                  int clipA, int clipB, int clipC);

#endif


