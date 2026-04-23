#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int load_csv(const char *filename, WaveformSample **samples_out) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Error: could not open file %s\n", filename);
        return 0;
    }

    int capacity = 1000;   // expected size
    int count = 0;

    WaveformSample *samples = malloc(capacity * sizeof(WaveformSample));
    if (!samples) {
        fclose(file);
        return 0;
    }

    char line[256];

    // Skip header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (count >= capacity) {
            capacity *= 2;
            samples = realloc(samples, capacity * sizeof(WaveformSample));
        }

        sscanf(line,
               "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &samples[count].timestamp,
               &samples[count].phaseA,
               &samples[count].phaseB,
               &samples[count].phaseC,
               &samples[count].current,
               &samples[count].frequency,
               &samples[count].powerFactor,
               &samples[count].thd);

        count++;
    }

    fclose(file);
    *samples_out = samples;
    return count;
}


void write_results(const char *filename, int count,
                   double rmsA, double rmsB, double rmsC,
                   double p2pA, double p2pB, double p2pC,
                   double dcA, double dcB, double dcC,
                   int clipped) {

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: could not write results file\n");
        return;
    }

    fprintf(file, "Power Quality Analysis Results\n");
    fprintf(file, "------------------------------\n\n");

    fprintf(file, "Samples analysed: %d\n\n", count);

    fprintf(file, "RMS Voltage (V)\n");
    fprintf(file, "Phase A: %.2f\n", rmsA);
    fprintf(file, "Phase B: %.2f\n", rmsB);
    fprintf(file, "Phase C: %.2f\n\n", rmsC);

    fprintf(file, "Peak-to-Peak Voltage (V)\n");
    fprintf(file, "Phase A: %.2f\n", p2pA);
    fprintf(file, "Phase B: %.2f\n", p2pB);
    fprintf(file, "Phase C: %.2f\n\n", p2pC);

    fprintf(file, "DC Offset (V)\n");
    fprintf(file, "Phase A: %.4f\n", dcA);
    fprintf(file, "Phase B: %.4f\n", dcB);
    fprintf(file, "Phase C: %.4f\n\n", dcC);

    fprintf(file, "Clipped samples detected: %d\n", clipped);

    fclose(file);
}