
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


#endif //PROGRAMMINGCOURSEWORK_WAVEFORM_H
