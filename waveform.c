#include "waveform.h"
#include <math.h>

//Math for RMS functions
double calculate_rms_A(const WaveformSample *samples, int count) {
    double sum_sq = 0.0;
    for (int i = 0; i < count; i++) {
        sum_sq += samples[i].phaseA * samples[i].phaseA;
    }
    return sqrt(sum_sq / count);
}
double calculate_rms_B(const WaveformSample *samples, int count) {
    double sum_sq = 0.0;
    for (int i = 0; i < count; i++) {
        sum_sq += samples[i].phaseB * samples[i].phaseB;
    }
    return sqrt(sum_sq / count);
}
double calculate_rms_C(const WaveformSample *samples, int count) {
    double sum_sq = 0.0;
    for (int i = 0; i < count; i++) {
        sum_sq += samples[i].phaseC * samples[i].phaseC;
    }
    return sqrt(sum_sq / count);
}






//Math for peak to peak functions
double calculate_peak_to_peak_A(const WaveformSample *samples, int count) {
    double min = samples[0].phaseA;
    double max = samples[0].phaseA;

    for (int i = 1; i < count; i++) {
        if (samples[i].phaseA < min) min = samples[i].phaseA;
        if (samples[i].phaseA > max) max = samples[i].phaseA;
    }
    return max - min;
}
double calculate_peak_to_peak_B(const WaveformSample *samples, int count) {
    double min = samples[0].phaseB;
    double max = samples[0].phaseB;

    for (int i = 1; i < count; i++) {
        if (samples[i].phaseB < min) min = samples[i].phaseB;
        if (samples[i].phaseB > max) max = samples[i].phaseB;
    }
    return max - min;
}
double calculate_peak_to_peak_C(const WaveformSample *samples, int count) {
    double min = samples[0].phaseC;
    double max = samples[0].phaseC;

    for (int i = 1; i < count; i++) {
        if (samples[i].phaseC < min) min = samples[i].phaseC;
        if (samples[i].phaseC > max) max = samples[i].phaseC;
    }
    return max - min;
}






//Math for DC offset functions
double calculate_dc_offset_A(const WaveformSample *samples, int count) {
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += samples[i].phaseA;
    }
    return sum / count;
}

double calculate_dc_offset_B(const WaveformSample *samples, int count) {
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += samples[i].phaseB;
    }
    return sum / count;
}
double calculate_dc_offset_B(const WaveformSample *samples, int count) {
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += samples[i].phaseB;
    }
    return sum / count;
}
double calculate_dc_offset_C(const WaveformSample *samples, int count) {
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += samples[i].phaseC;
    }
    return sum / count;
}


//Math for clipping function
int detect_clipping(const WaveformSample *samples, int count) {
    int clipped = 0;

    for (int i = 0; i < count; i++) {
        if (samples[i].phaseA >= 324.9 ||
            samples[i].phaseB >= 324.9 ||
            samples[i].phaseC >= 324.9) {
            clipped++;
        }
    }
    return clipped;
}



// RMS tolerance check
int is_within_tolerance(double rms) {
    return (rms >= 207.0 && rms <= 253.0);
}





//Math for frequency functions
double max_frequency(const WaveformSample *samples, int count) {
    double max = samples[0].frequency;

    for (int i = 1; i < count; i++) {
        if (samples[i].frequency > max) {
            max = samples[i].frequency;
        }
    }
    return max;
}
double min_frequency(const WaveformSample *samples, int count) {
    double min = samples[0].frequency;

    for (int i = 1; i < count; i++) {
        if (samples[i].frequency < min) {
            min = samples[i].frequency;
        }
    }
    return min;
}
double avg_frequency(const WaveformSample *samples, int count) {
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += samples[i].frequency;
    }
    return sum / count;
}




//Math for power factor calculations
double max_power_factor(const WaveformSample *samples, int count) {
    double max = samples[0].powerFactor;

    for (int i = 1; i < count; i++) {
        if (samples[i].powerFactor > max) {
            max = samples[i].powerFactor;
        }
    }
    return max;
}
double min_power_factor(const WaveformSample *samples, int count) {
    double min = samples[0].powerFactor;

    for (int i = 1; i < count; i++) {
        if (samples[i].powerFactor < min) {
            min = samples[i].powerFactor;
        }
    }
    return min;
}






//Math for current
double max_current(const WaveformSample *samples, int count) {
    double max = samples[0].current;

    for (int i = 1; i < count; i++) {
        if (samples[i].current > max) {
            max = samples[i].current;
        }
    }
    return max;
}
double min_current(const WaveformSample *samples, int count) {
    double min = samples[0].current;

    for (int i = 1; i < count; i++) {
        if (samples[i].current < min) {
            min = samples[i].current;
        }
    }
    return min;
}
double avg_current(const WaveformSample *samples, int count) {
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += samples[i].current;
    }
    return sum / count;
}





//Math for THD calculations
double max_thd(const WaveformSample *samples, int count) {
    double max = samples[0].thd;

    for (int i = 1; i < count; i++) {
        if (samples[i].thd > max) {
            max = samples[i].thd;
        }
    }
    return max;
}
double min_thd(const WaveformSample *samples, int count) {
    double min = samples[0].thd;

    for (int i = 1; i < count; i++) {
        if (samples[i].thd < min) {
            min = samples[i].thd;
        }
    }
    return min;
}
