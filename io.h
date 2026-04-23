
#ifndef PROGRAMMINGCOURSEWORK_IO_H
#define PROGRAMMINGCOURSEWORK_IO_H

#include "waveform.h"
#include <stdio.h>

int load_csv(const char *filename, WaveformSample **samples_out);
void write_results(const char *filename, int count,
                   double rmsA, double rmsB, double rmsC,
                   double p2pA, double p2pB, double p2pC,
                   double dcA, double dcB, double dcC,
                   int clipped);

#endif


