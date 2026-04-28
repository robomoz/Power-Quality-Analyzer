#include "io.h"
#include "waveform.h"
#include <stdio.h>
#include <stdlib.h>

int load_csv(const char *filename, WaveformSample **samples_out) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Error: could not open file '%s'\n", filename);
        return 0;
    }

    int capacity = 1000;
    int count = 0;

    WaveformSample *samples = malloc(capacity * sizeof(WaveformSample));
    if (!samples) {
        printf("Error: memory allocation failed\n");
        fclose(file);
        return 0;
    }

    char line[256];

    // Skip the header row
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {

        // Grow the array if needed
        if (count >= capacity) {
            capacity *= 2;
            WaveformSample *temp = realloc(samples, capacity * sizeof(WaveformSample));
            if (!temp) {
                printf("Error: realloc failed at row %d\n", count);
                free(samples);
                fclose(file);
                return 0;
            }
            samples = temp;
        }

        // Parse the 8 comma-separated fields into the struct
        sscanf(line,
               "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &(samples + count)->timestamp,
               &(samples + count)->phaseA,
               &(samples + count)->phaseB,
               &(samples + count)->phaseC,
               &(samples + count)->current,
               &(samples + count)->frequency,
               &(samples + count)->powerFactor,
               &(samples + count)->thd);

        count++;
    }

    fclose(file);
    *samples_out = samples;
    return count;
}


void write_results(const char *filename, const WaveformSample *samples, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: could not open results file '%s' for writing\n", filename);
        return;
    }

    // ── Compute all metrics ──────────────────────────────────────────

    double rmsA = calculate_rms_A(samples, count);
    double rmsB = calculate_rms_B(samples, count);
    double rmsC = calculate_rms_C(samples, count);

    double p2pA = calculate_peak_to_peak_A(samples, count);
    double p2pB = calculate_peak_to_peak_B(samples, count);
    double p2pC = calculate_peak_to_peak_C(samples, count);

    double dcA = calculate_dc_offset_A(samples, count);
    double dcB = calculate_dc_offset_B(samples, count);
    double dcC = calculate_dc_offset_C(samples, count);

    int clipA = detect_clipping_A(samples, count);
    int clipB = detect_clipping_B(samples, count);
    int clipC = detect_clipping_C(samples, count);

    double stdA = calculate_std_dev_A(samples, count);
    double stdB = calculate_std_dev_B(samples, count);
    double stdC = calculate_std_dev_C(samples, count);

    double freqMin = min_frequency(samples, count);
    double freqMax = max_frequency(samples, count);
    double freqAvg = avg_frequency(samples, count);

    double pfMin = min_power_factor(samples, count);
    double pfMax = max_power_factor(samples, count);

    double thdMin = min_thd(samples, count);
    double thdMax = max_thd(samples, count);

    double currentMin = min_current(samples, count);
    double currentMax = max_current(samples, count);
    double currentAvg = avg_current(samples, count);

    // The report

    fprintf(file, "============================================================\n");
    fprintf(file, "       POWER QUALITY ANALYSIS REPORT\n");
    fprintf(file, "============================================================\n\n");

    fprintf(file, "Samples analysed : %d\n\n", count);

    // --- RMS Voltage ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "RMS VOLTAGE (nominal 230 V, compliant range 207-253 V)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %7.2f V  -->  %s\n", rmsA, is_within_tolerance(rmsA) ? "COMPLIANT" : "NON-COMPLIANT");
    fprintf(file, "Phase B : %7.2f V  -->  %s\n", rmsB, is_within_tolerance(rmsB) ? "COMPLIANT" : "NON-COMPLIANT");
    fprintf(file, "Phase C : %7.2f V  -->  %s\n\n", rmsC, is_within_tolerance(rmsC) ? "COMPLIANT" : "NON-COMPLIANT");

    // --- Peak-to-Peak ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "PEAK-TO-PEAK VOLTAGE (expected ~650.54 V)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %7.2f V\n", p2pA);
    fprintf(file, "Phase B : %7.2f V\n", p2pB);
    fprintf(file, "Phase C : %7.2f V\n\n", p2pC);

    // --- DC Offset ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "DC OFFSET (expected ~0.00 V for clean AC)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %10.6f V\n", dcA);
    fprintf(file, "Phase B : %10.6f V\n", dcB);
    fprintf(file, "Phase C : %10.6f V\n\n", dcC);

    // --- Clipping ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "CLIPPING DETECTION (|V| >= 324.9 V, expected 20 total)\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %d clipped sample(s)\n", clipA);
    fprintf(file, "Phase B : %d clipped sample(s)\n", clipB);
    fprintf(file, "Phase C : %d clipped sample(s)\n", clipC);
    fprintf(file, "Total   : %d clipped sample(s)\n\n", clipA + clipB + clipC);

    // --- Standard Deviation ---
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "STANDARD DEVIATION\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Phase A : %.4f V\n", stdA);
    fprintf(file, "Phase B : %.4f V\n", stdB);
    fprintf(file, "Phase C : %.4f V\n\n", stdC);

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