
#ifndef PROGRAMMINGCOURSEWORK_WAVEFORM_H
#define PROGRAMMINGCOURSEWORK_WAVEFORM_H

//1 - define the stuct

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;

} WaveformSample;
double calculate_rms(WaveformSample *data, int num_rows, int phase_choice);

#endif //PROGRAMMINGCOURSEWORK_WAVEFORM_H
