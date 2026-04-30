#include "waveform.h"
#include <math.h>

// Math for RMS functions
double calculate_rms_A(const WaveformSample *samples, int count) {   //passes parameter to function
    double sum_sq = 0.0;                                             //declaring the variable to add up squares
    for (int i = 0; i < count; i++) {                                //for loop while i is less than count it will loop
        sum_sq += samples[i].phaseA * samples[i].phaseA;             //timesing current sample by itself and then add to total
    }
    return sqrt(sum_sq / count);                                  // divide sum square by 1000(count) to get the mean and then square root the mean to get the RMS
}
double calculate_rms_B(const WaveformSample *samples, int count) { //passes parameter to function
    double sum_sq = 0.0;                                           //declaring the variable to add up squares
    for (int i = 0; i < count; i++) {                             //for loop while i is less than count it will loop
        sum_sq += samples[i].phaseB * samples[i].phaseB;          //timesing current sample by itself and then add to total
    }
    return sqrt(sum_sq / count);                                //divide sum square by 1000(count) to get the mean and then square root the mean to get the RMS
}
double calculate_rms_C(const WaveformSample *samples, int count) {   //passes parameter to function
    double sum_sq = 0.0;                                             //declaring the variable to add up squares
    for (int i = 0; i < count; i++) {                                 //for loop while i is less than count it will loop
        sum_sq += samples[i].phaseC * samples[i].phaseC;             //timesing current sample by itself and then add to total
    }
    return sqrt(sum_sq / count);                                  //  //divide sum square by 1000(count) to get the mean and then square root the mean to get the RMS
}






// Math for peak to peak functions
double calculate_peak_to_peak_A(const WaveformSample *samples, int count) {   //passes samples to function
    double min = samples[0].phaseA; //sets initial min to very first sample
    double max = samples[0].phaseA;  //sets initial max to very first sample
    for (int i = 1; i < count; i++) {  //loops through the rest of the samples
        if (samples[i].phaseA < min) min = samples[i].phaseA;  //if current sample is less than min, change min
        if (samples[i].phaseA > max) max = samples[i].phaseA;  //if current sample is bigger than max. change max
    }
    return max - min; //subtract min from max to get peak to peak range
}
double calculate_peak_to_peak_B(const WaveformSample *samples, int count) {  //passes samples to function
    double min = samples[0].phaseB;   //sets initial min to very first sample
    double max = samples[0].phaseB;  //sets initial max to very first sample
    for (int i = 1; i < count; i++) { //loops through the rest of the samples
        if (samples[i].phaseB < min) min = samples[i].phaseB; //if current sample is less than min, change min
        if (samples[i].phaseB > max) max = samples[i].phaseB; //if current sample is bigger than max. change max
    }
    return max - min; //subtract min from max to get peak to peak range
}
double calculate_peak_to_peak_C(const WaveformSample *samples, int count) {  //passes samples to function
    double min = samples[0].phaseC;    //sets initial min to very first sample
    double max = samples[0].phaseC;     //sets initial max to very first sample
    for (int i = 1; i < count; i++) {    //loops through the rest of the samples
        if (samples[i].phaseC < min) min = samples[i].phaseC;   //if current sample is less than min, change min
        if (samples[i].phaseC > max) max = samples[i].phaseC;   //if current sample is bigger than max. change max
    }
    return max - min; //subtract min from max to get peak to peak range
}






// Math for DC offset functions
double calculate_dc_offset_A(const WaveformSample *samples, int count) { //passes parameter to function
    double sum = 0.0;   //declares variable to hold the total sum
    for (int i = 0; i < count; i++) {   // loops through all samples
        sum += samples[i].phaseA;       //adds the current phase value to the total sum
    }
    return sum / count;  //divides sum by count to find the average of the DC offset
}

double calculate_dc_offset_B(const WaveformSample *samples, int count) { //passes parameter to function
    double sum = 0.0;  //declares variable to hold the total sum
    for (int i = 0; i < count; i++) {  // loops through all samples
        sum += samples[i].phaseB;  //adds the current phase value to the total sum
    }
    return sum / count;   //divides sum by count to find the average of the DC offset
}

double calculate_dc_offset_C(const WaveformSample *samples, int count) {//passes parameter to function
    double sum = 0.0; //declares variable to hold the total sum
    for (int i = 0; i < count; i++) { // loops through all samples
        sum += samples[i].phaseC;  //adds the current phase value to the total sum
    }
    return sum / count;  //divides sum by count to find the average of the DC offset
}


// Math for clipping function
int detect_clipping_A(const WaveformSample *samples, int count) { //passes parameter to function
    int clipped = 0;   //declares counter for number of clipped samples
    for (int i = 0; i < count; i++) { //looping through every sample
        if (fabs((samples + i)->phaseA) >= 324.9) { //checks if absolute value is over the limit of 324.9
            clipped++;  //adds one to the clipped counter if limit is hit
        }
    }
    return clipped; //returns the total number of clipped samples found
}

int detect_clipping_B(const WaveformSample *samples, int count) {  //passes parameter to function
    int clipped = 0;  //declares counter for number of clipped samples
    for (int i = 0; i < count; i++) { //looping through every sample
        if (fabs((samples + i)->phaseB) >= 324.9) {  //checks if absolute value is over the limit of 324.9
            clipped++;  //adds one to the clipped counter if limit is hit

        }
    }
    return clipped;   //returns the total number of clipped samples found

int detect_clipping_C(const WaveformSample *samples, int count) { //passes parameter to function
    int clipped = 0;  //declares counter for number of clipped samples
    for (int i = 0; i < count; i++) {  //looping through every sample
        if (fabs((samples + i)->phaseC) >= 324.9) {  //checks if absolute value is over the limit of 324.9
            clipped++;  //adds one to the clipped counter if limit is hit
        }
    }
    return clipped; //returns the total number of clipped samples found
}





double calculate_std_dev_A(const WaveformSample *samples, int count) { //passes parameter to function
    double mean = calculate_dc_offset_A(samples, count); //calls dc offset function to get the average
    double sum_sq_diff = 0.0;  //declares variable for sum of squared differences
    for (int i = 0; i < count; i++) { //loops through the samples
        double diff = (samples + i)->phaseA - mean;  //subtracts the mean from a different sample to get difference
        sum_sq_diff += diff * diff;   //squares the difference and adds it to the total
    }
    return sqrt(sum_sq_diff / count);  //divides by count and square roots to get std deviation
}
double calculate_std_dev_B(const WaveformSample *samples, int count) {//passes parameter to function
    double mean = calculate_dc_offset_B(samples, count); //calls dc offset function to get the average
    double sum_sq_diff = 0.0;  //declares variable for sum of squared differences
    for (int i = 0; i < count; i++) {  //loops through the samples
        double diff = (samples + i)->phaseB - mean;  //subtracts the mean from a different sample to get difference
        sum_sq_diff += diff * diff; //squares the difference and adds it to the total
    }
    }
    return sqrt(sum_sq_diff / count);//divides by count and square roots to get std deviation
}
double calculate_std_dev_C(const WaveformSample *samples, int count) {//passes parameter to function
    double mean = calculate_dc_offset_C(samples, count);//calls dc offset function to get the average
    double sum_sq_diff = 0.0;  //declares variable for sum of squared differences
    for (int i = 0; i < count; i++) {//loops through the samples
        double diff = (samples + i)->phaseC - mean; //subtracts the mean from a different sample to get difference
        sum_sq_diff += diff * diff; //squares the difference and adds it to the total
    }
    return sqrt(sum_sq_diff / count);//divides by count and square roots to get std deviation
}



// RMS tolerance check
int is_within_tolerance(double rms) {
    return (rms >= 207.0 && rms <= 253.0);
}





// Math for frequency functions
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




// Math for power factor calculations
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






// Math for current
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





// Math for THD calculations
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
