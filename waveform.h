
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
//RMS function calclation
double calculate_rms_A(const WaveformSample *samples, int count);
double calculate_rms_B(const WaveformSample *samples, int count);
double calculate_rms_C(const WaveformSample *samples, int count);

//peak to peak voltage function calculation for ABC
double calculate_peak_to_peak_A(const Waveformsample * samples, int count);
double calculate_peak_to_peak_B(const Waveformsample * samples, int count);
double calculate_peak_to_peak_C(const Waveformsample * samples, int count);

// dc offset function calc
double calculate_dc_offset_A(const WaveformSample *samples, int count);
double calculate_dc_offset_B(const WaveformSample *samples, int count);
double calculate_dc_offset_C(const WaveformSample *samples, int count);

//exeeding theshold calc
int detect_clipping(const WaveformSample * samples, int count);

//within tolerance for phases
int is_within_tolerance(double rms, double *percentage);

//frequency calc
double max_frequency(const WaveformSample *samples, int count);
double min_frequency(const WaveformSample *samples, int count);
double avg_frequency(const WaveformSample *samples, int count);

//power factor calculations
double max_power_factor(const WaveformSample *samples, int count);
double min_power_factor(const WaveformSample *samples, int count);

//current calc
double max_current(const WaveformSample *samples, int count);
double min_current(const WaveformSample *samples, int count);
double avg_current(const WaveformSample *samples, int count);

//thd percent calc
double max_thd(const WaveformSample *samples, int count);
double min_thd(const WaveformSample *samples, int count);

#endif
