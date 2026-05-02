#include "io.h"
#include "waveform.h"
#include <stdio.h>
#include <stdlib.h>

int load_csv(const char *filename, WaveformSample **samples_out) { //passes filename and output to pointer functiom
    FILE *file = fopen(filename, "r"); //opens the file in read mode - doesnt cahnge anything

    if (!file) {  //if the file failed to open
        printf("Error: could not open file '%s'\n", filename); //print error message
        return 0; // return to 0 to show function failed
    }

    int capacity = 1000; //setting initial memory space for 1000 rows
    int count = 0;  //variable that keeps track of how many rows we read

    WaveformSample *samples = malloc(capacity * sizeof(WaveformSample));  //allocate memory for the first 1000 samples
    if (!samples) { //incase the computer ran out of memory
        printf("Error: memory allocation failed\n"); //print error message
        fclose(file); // close file
        return 0; //return to 0 to show function failed
    }

    char line[256]; //creating a text buffer to hold one line of the file

    // Skip the header row
    fgets(line, sizeof(line), file); //reads the first line

    while (fgets(line, sizeof(line), file)) {  //while there is still a line to read in the file


        if (count >= capacity) { //checking if we have run out of allocated space
            capacity *= 2; // so doubles the capacity size
            WaveformSample *temp = realloc(samples, capacity * sizeof(WaveformSample)); //attempts to resize the existing memory block to the new doubled capacity size
            if (!temp) { //if doubling memory failed
                printf("Error: realloc failed at row %d\n", count); //print where it went wrong
                free(samples); //clean up the old memory
                fclose(file); //close file
                return 0;
            }
            samples = temp; //update samples pointer to the new bigger memory
        }

        // moving raw data from text file into the variables
        sscanf(line,  //read the current text line
               "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",  //looking for 8 double numbers and separating them by commas
               &(samples + count)->timestamp, //save the first number to timestamp
               &(samples + count)->phaseA, //save the second number to phase a
               &(samples + count)->phaseB, // save the third number to phase b
               &(samples + count)->phaseC, //save the forth number to phase c
               &(samples + count)->current,  // save the 5th number to current
               &(samples + count)->frequency, // save the 6th number to freq
               &(samples + count)->powerFactor,  //save the 7th number to power factor
               &(samples + count)->thd); //save the 8th number to thd

        count++; //increment count by 1 for the next row to go through all the samples
    }

    fclose(file); //close data file once done and saved
    *samples_out = samples; //send the finished list back yto the main program
    return count; // return total number of samples loaded
}



//taking the calculated math to then print out into the results
void write_results(const char *filename, const WaveformSample *samples, int count) { //passes name data and count
    FILE *file = fopen(filename, "w"); //opens a new file in write mode - this is the results 'table'
    if (!file) { // if the file couldnt be created
        printf("Error: could not open results file '%s' for writing\n", filename); //it prints error message
        return; //exit the function
    }

    // ── Compute all metrics ──────────────────────────────────────────

    double rmsA = calculate_rms_A(samples, count);  //computes RMS A function and saves result
    double rmsB = calculate_rms_B(samples, count);  //computes RMS B function and saves result
    double rmsC = calculate_rms_C(samples, count);  //computes RMS C function and saves result

    double p2pA = calculate_peak_to_peak_A(samples, count); //calls Peak to peak A and saves result
    double p2pB = calculate_peak_to_peak_B(samples, count); //calls Peak to peak B and saves result
    double p2pC = calculate_peak_to_peak_C(samples, count); //calls Peak to peak C and saves result

    double dcA = calculate_dc_offset_A(samples, count); //calls DC offset A and saves result
    double dcB = calculate_dc_offset_B(samples, count); //calls DC offset B and saves result
    double dcC = calculate_dc_offset_C(samples, count); //calls DC offset C and saves result

    int clipA = detect_clipping_A(samples, count); //calls clipping A and saves result
    int clipB = detect_clipping_B(samples, count); //calls clipping B and saves result
    int clipC = detect_clipping_C(samples, count); //calls clipping B and saves result

    double stdA = calculate_std_dev_A(samples, count); //calls stand dev A and saves result
    double stdB = calculate_std_dev_B(samples, count); //calls stand dev B and saves resul
    double stdC = calculate_std_dev_C(samples, count); //calls stand dev C and saves resul

    double freqMin = min_frequency(samples, count);  //Calls min freq and saves result
    double freqMax = max_frequency(samples, count); //Calls max freq and saves result
    double freqAvg = avg_frequency(samples, count); //Calls avg freq and saves result

    double pfMin = min_power_factor(samples, count); //calls min power factor and saves result
    double pfMax = max_power_factor(samples, count);  //calls max power factor and saves result

    double thdMin = min_thd(samples, count); //calls min THD and saves result
    double thdMax = max_thd(samples, count);  //calls max THD and saves result

    double currentMin = min_current(samples, count); //calls Min Current and saves result
    double currentMax = max_current(samples, count); //calls Max Current and saves resul
    double currentAvg = avg_current(samples, count); //calls avg Current and saves resul

    // The report

    fprintf(file, "============================================================\n");
    fprintf(file, "       POWER QUALITY ANALYSIS REPORT\n");
    fprintf(file, "============================================================\n\n");

    fprintf(file, "Samples Analysed : %d\n\n", count);  //prints how many data points were used

    // --- RMS Voltage ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "RMS VOLTAGE (nominal 230 V, compliant range 207-253 V)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %7.2f V  -->  %s\n", rmsA, is_within_tolerance(rmsA) ? "COMPLIANT" : "NON-COMPLIANT");  //prints A result and checks if its within range
    fprintf(file, "Phase B : %7.2f V  -->  %s\n", rmsB, is_within_tolerance(rmsB) ? "COMPLIANT" : "NON-COMPLIANT");  //prints B result and checks if it is within range
    fprintf(file, "Phase C : %7.2f V  -->  %s\n\n", rmsC, is_within_tolerance(rmsC) ? "COMPLIANT" : "NON-COMPLIANT"); //prints C result and checks if it is within range

    // --- Peak-to-Peak ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "PEAK-TO-PEAK VOLTAGE (expected ~650.54 V)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %7.2f V\n", p2pA); //prints the peak to peak result for Phase A
    fprintf(file, "Phase B : %7.2f V\n", p2pB); //prints the peak to peak result for Phase B
    fprintf(file, "Phase C : %7.2f V\n\n", p2pC); //prints the peak to peak result for Phase C

    // --- DC Offset ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "DC OFFSET (expected ~0.00 V for clean AC)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %10.6f V\n", dcA); //prints DC offset with 6 decimal places for A
    fprintf(file, "Phase B : %10.6f V\n", dcB); //prints DC offset with 6 decimal places for B
    fprintf(file, "Phase C : %10.6f V\n\n", dcC);  //prints DC offset with 6 decimal places for C
    // --- Clipping ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "CLIPPING DETECTION (|V| >= 324.9 V, expected 20 total)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %d clipped sample(s)\n", clipA); //prints number of clipped samples in A
    fprintf(file, "Phase B : %d clipped sample(s)\n", clipB); //prints number of clipped samples in B
    fprintf(file, "Phase C : %d clipped sample(s)\n", clipC); //prints number of clipped samples in C
    fprintf(file, "Total   : %d clipped sample(s)\n\n", clipA + clipB + clipC); //prints the sum of all clipped samples

    // --- Standard Deviation ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "STANDARD DEVIATION\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %.4f V\n", stdA);  //prints standard deviation for Phase A
    fprintf(file, "Phase B : %.4f V\n", stdB); // prints standard deviation for Phase B
    fprintf(file, "Phase C : %.4f V\n\n", stdC); // prints standard deviation for Phase C

    // --- Frequency ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "FREQUENCY (nominal 50.0 Hz)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Min : %.4f Hz\n", freqMin);
    fprintf(file, "Max : %.4f Hz\n", freqMax);
    fprintf(file, "Avg : %.4f Hz\n\n", freqAvg);

    // --- Power Factor ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "POWER FACTOR (nominal 0.95)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Min : %.4f\n", pfMin);
    fprintf(file, "Max : %.4f\n\n", pfMax);

    // --- Current ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "LINE CURRENT (typical ~3.5 A)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Min : %.4f A\n", currentMin);
    fprintf(file, "Max : %.4f A\n", currentMax);
    fprintf(file, "Avg : %.4f A\n\n", currentAvg);

    // --- THD ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "TOTAL HARMONIC DISTORTION (EN 50160 limit: 8%%)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Min : %.2f%%\n", thdMin);
    fprintf(file, "Max : %.2f%%\n\n", thdMax);

    fprintf(file, "============================================================\n");
    fprintf(file, "END OF REPORT\n");
    fprintf(file, "============================================================\n");

    fclose(file);
    printf("Results written to '%s'\n", filename);
}