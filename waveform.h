
#ifndef PROGRAMMINGCOURSEWORK_WAVEFORM_H
#define PROGRAMMINGCOURSEWORK_WAVEFORM_H

//1 - define the stuct

typedef struct {
    double timestamp;
    double phaseA;
    double phaseB;
    double phaseC;
    double current;
    double frequency;
    double powerFactor;
    double thd;

} WaveformSample;
//functions for waveform sample
double calculate_rms(const WaveformSample *samples, int count, char phase);
double calculate peak_to_peak(const Waveformsample * samples, int count, char phase);
double calculate_dc_offset(const WaveformSample *samples, int count, char phase);
int detect_clipping(const WaveformSample * samples, int count, char phase); //exeeds threshold
int is_within_tolerance(double rms);

#endif
