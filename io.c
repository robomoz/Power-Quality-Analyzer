//data loops through
#include <stdio.h>
#include <stdlib.h>
#include "io.h
#include "waveform.h"

int load_data(cont char *filename, WaveformSample *data, int num_rows){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error: Could not open the data file");
        return 1;
    }


    // We create a buffer to "catch" the text labels, so they don't mess up our doubles
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        fclose(fp);
        return 1;
    }

    // Loop through the file to read 1,000 rows
    for (int i = 0; i < num_rows; i++) {


        // Instead of data[i], we calculate the address of the current "box"
        WaveformSample *current = data + i;

        // reading the data row by row
        int read_count = fscanf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                                &current->timestamp,
                                &current->phase_A_voltage,
                                &current->phase_B_voltage,
                                &current->phase_C_voltage,
                                &current->line_current,
                                &current->frequency,
                                &current->power_factor,
                                &current->thd_percent);

        // incase we hit the end of the file earlier than expected
        if (read_count != 8) {
            break;
        }
    }

    fclose(fp);
    return 0;
}


void export_report(const char *filename, double rmsA, double rmsB, double rmsC) {
    FILE *fp = fopen(filename, "w"); // "w" creates or overwrites the file
    if (fp == NULL) {
        printf("Error: Could not create the results file.\n");
        return;
    }

    fprintf(fp, "--- Power Quality Analysis Report ---\n");
    fprintf(fp, "Phase A RMS: %.2f V\n", rmsA);
    fprintf(fp, "Phase B RMS: %.2f V\n", rmsB);
    fprintf(fp, "Phase C RMS: %.2f V\n", rmsC);



    fclose(fp);
}
