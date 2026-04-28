#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int main(int argc, char *argv[]) {

    // Check that a filename was provided as a command-line argument
    if (argc < 2) {
        printf("Usage: %s <filename.csv>\n", argv[0]);
        printf("Example: %s power_quality_log.csv\n", argv[0]);
        return 1;
    }

    // Load the CSV
    WaveformSample *samples = NULL;
    int count = load_csv(argv[1], &samples);

    if (count == 0) {
        printf("Error: no data loaded from '%s'. Exiting.\n", argv[1]);
        return 1;
    }

    printf("Successfully loaded %d samples from '%s'\n", count, argv[1]);

    // Run analysis and write report
    write_results("results.txt", samples, count);

    // Print a summary to the terminal as well
    printf("\n--- Quick Summary ---\n");

    double rmsA = calculate_rms_A(samples, count);
    double rmsB = calculate_rms_B(samples, count);
    double rmsC = calculate_rms_C(samples, count);

    printf("RMS Voltage  ->  Phase A: %.2f V  |  Phase B: %.2f V  |  Phase C: %.2f V\n",
           rmsA, rmsB, rmsC);

    printf("Tolerance    ->  Phase A: %s  |  Phase B: %s  |  Phase C: %s\n",
           is_within_tolerance(rmsA) ? "PASS" : "FAIL",
           is_within_tolerance(rmsB) ? "PASS" : "FAIL",
           is_within_tolerance(rmsC) ? "PASS" : "FAIL");

    int totalClipped = detect_clipping_A(samples, count)
                     + detect_clipping_B(samples, count)
                     + detect_clipping_C(samples, count);

    printf("Clipping     ->  %d clipped sample(s) detected across all phases\n", totalClipped);

    printf("\nFull report saved to results.txt\n");

    // Free allocated memory
    free(samples);
    samples = NULL;

    return 0;
}