
#ifndef PROGRAMMINGCOURSEWORK_IO_H
#define PROGRAMMINGCOURSEWORK_IO_H

#include "waveform.h"
#include <stdio.h>

int load_csv(const char *filename, WaveformSample **samples_out);

void write_results(const char *filename, const WaveformSample *samples, int count);

#endif


