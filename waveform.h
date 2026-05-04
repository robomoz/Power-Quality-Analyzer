
#ifndef PROGRAMMINGCOURSEWORK_WAVEFORM_H
#define PROGRAMMINGCOURSEWORK_WAVEFORM_H

//defins the stuct to hold all data from one row of the cvs file

typedef struct {
    double timestamp; //creating functions
    double phaseA;
    double phaseB;
    double phaseC;
    double current;
    double frequency;
    double powerFactor;
    double thd;

} WaveformSample;
//RMS function calculation
double calculate_rms_A(const WaveformSample *samples, int count); //calculates RMS voltage for phase A using the sample array and the number of rows loaded
double calculate_rms_B(const WaveformSample *samples, int count); //calculates RMS voltage for phase B using the sample array and the number of rows loaded
double calculate_rms_C(const WaveformSample *samples, int count); //calculates RMS voltage for phase C using the sample array and the number of rows loaded

//peak to peak voltage function calculation for ABC
double calculate_peak_to_peak_A(const WaveformSample * samples, int count);
double calculate_peak_to_peak_B(const WaveformSample * samples, int count);
double calculate_peak_to_peak_C(const WaveformSample * samples, int count);

// dc offset function calc
double calculate_dc_offset_A(const WaveformSample *samples, int count);
double calculate_dc_offset_B(const WaveformSample *samples, int count);
double calculate_dc_offset_C(const WaveformSample *samples, int count);


// Replacing with single detect_clipping with per-phase versions
int detect_clipping_A(const WaveformSample *samples, int count);
int detect_clipping_B(const WaveformSample *samples, int count);
int detect_clipping_C(const WaveformSample *samples, int count);

//standard deviation for each phase
double calculate_std_dev_A(const WaveformSample *samples, int count);
double calculate_std_dev_B(const WaveformSample *samples, int count);
double calculate_std_dev_C(const WaveformSample *samples, int count);

//within tolerance for phases
int is_within_tolerance(double rms); //takes the rms voltage as a decimal number and checks if it falls within the allowed 207-253V range

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

#endif //ending header gard
