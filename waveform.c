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
}

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
int is_within_tolerance(double rms) {  //passes the RMS value to check
    return (rms >= 207.0 && rms <= 253.0); //checks if value is between 207 and 253 then returns the result
}





// Math for frequency functions
double max_frequency(const WaveformSample *samples, int count) {  //passes sample to function
    double max = samples[0].frequency; //sets initial max to the first frequency sample
    for (int i = 1; i < count; i++) { //loops through the samples
        if (samples[i].frequency > max) { //if current frequency is higher than max
            max = samples[i].frequency;  // update max with higher value
        }
    }
    return max;  // returns the highest frequency found
}
double min_frequency(const WaveformSample *samples, int count) {  //passes sample to function
    double min = samples[0].frequency; // sets initial min to the first freq sample

    for (int i = 1; i < count; i++) { // loops through the samples
        if (samples[i].frequency < min) {  //if current freq is lower than min
            min = samples[i].frequency;   //update the min with the lower value
        }
    }
    return min;  //returns the lowest frequency found
}
double avg_frequency(const WaveformSample *samples, int count) { //passes sample to function
    double sum = 0.0;  // declares variable for the total sum
    for (int i = 0; i < count; i++) { //loops through the freq samples
        sum += samples[i].frequency; //adds current freq to the sum to get avg
    }
    return sum / count;  //actual maths - divides total sum to get average freq
}




// Math for power factor calculations
double max_power_factor(const WaveformSample *samples, int count) { //passes samples to function
    double max = samples[0].powerFactor; // sets the initial max to first power factor sample
    for (int i = 1; i < count; i++) { // looping through the data
        if (samples[i].powerFactor > max) { //checks if current value is higher than max
            max = samples[i].powerFactor;  //updates max with the new value
        }
    }
    return max;  //returns highest power factor result
}
double min_power_factor(const WaveformSample *samples, int count) { //passes samples to function
    double min = samples[0].powerFactor;   // sets the initial min to first power factor sample
    for (int i = 1; i < count; i++) { // looping through the data
        if (samples[i].powerFactor < min) { //checks if current value is lower than min
            min = samples[i].powerFactor; //updates min with the new value
        }
    }
    return min; //returns highest power factor result
}






// Math for current
double max_current(const WaveformSample *samples, int count) { //passes samples to function
    double max = samples[0].current; //sets initial max to first current sample
    for (int i = 1; i < count; i++) {   // looping through the data
        if (samples[i].current > max) {  //checks if current value is higher than max
            max = samples[i].current;  // updates max with the higher value
        }
    }
    return max; //returns highest current
}
double min_current(const WaveformSample *samples, int count) { //passes samples to function
    double min = samples[0].current;    //sets initial min to first current sample
    for (int i = 1; i < count; i++) {    // looping through the data
        if (samples[i].current < min) { //checks if current value is lower than min
            min = samples[i].current;  // updates min with the higher value
        }
    }
    return min; //returns lowest value
}
double avg_current(const WaveformSample *samples, int count) { //passes samples to function
    double sum = 0.0; //declares variable for the total sum
    for (int i = 0; i < count; i++) {    // looping through the data
        sum += samples[i].current;  //adds current value to the total sum
    }
    return sum / count; // the actual math, divides sum by count to get avg current
}





// Math for THD calculations
double max_thd(const WaveformSample *samples, int count) { //passes samples to function
    double max = samples[0].thd;   //sets initial max to first THD sample
    for (int i = 1; i < count; i++) {  //looping through the data
        if (samples[i].thd > max) {  //checks if current THD is higher tha max
            max = samples[i].thd; // updates max with higher value
        }
    }
    return max;  //returns the highest THD value
}
double min_thd(const WaveformSample *samples, int count) { //passes samples to function
    double min = samples[0].thd; //sets initial min to first THD sample
    for (int i = 1; i < count; i++) {   // looping through the data
        if (samples[i].thd < min) { //checks if current THD is lower than min
            min = samples[i].thd;   //updates min with the lower value
        }
    }
    return min; //returns lowest THD value
}
