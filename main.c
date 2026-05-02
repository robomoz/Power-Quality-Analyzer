#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int main(int argc, char *argv[]) {  //main function, arc counts arguments, argv stores them as strings

    // Check that a filename was provided as a command-line argument
    if (argc < 2) { //checks if fewer than 2 arguments were given (program name + filename)
        printf("Usage: %s <filename.csv>\n", argv[0]); //prints usage instructions using tbe program name stored in argv[0]
        printf("Example: %s power_quality_log.csv\n", argv[0]); //prints an example to make it clearer
        return 1; //exits with error code 1 to signal something went wrong
    }

    // Load the CSV
    WaveformSample *samples = NULL; //declares pointer for the sample array, set to NULL until allocated
    int count = load_csv(argv[1], &samples); //calls load_csv with the filename, fills samples and returns row count

    if (count == 0) { //checks if no data was loaded, which means the file was empty or failed to open
        printf("Error: no data loaded from '%s'. Exiting.\n", argv[1]); //then prints the error message with the filename
        return 1; //exits error
    }

    printf("Successfully loaded %d samples from '%s'\n", count, argv[1]); //confirms how many rows were loaded

    // Run analysis and write report
    write_results("results.txt", samples, count); //calls write_results to calculate all metrics and save the report

    // Print a summary to the terminal as well
    printf("\n--- Quick Summary ---\n"); //prints a header for the terminal summary section

    double rmsA = calculate_rms_A(samples, count); //calculates RMS voltage for phase A
    double rmsB = calculate_rms_B(samples, count); //calculates RMS voltage for phase B
    double rmsC = calculate_rms_C(samples, count); //calculates RMS voltage for phase C

    printf("RMS Voltage  ->  Phase A: %.2f V  |  Phase B: %.2f V  |  Phase C: %.2f V\n",
           rmsA, rmsB, rmsC); //prints RMS values for all three phases to 2 decimal points

    printf("Tolerance    ->  Phase A: %s  |  Phase B: %s  |  Phase C: %s\n",
           is_within_tolerance(rmsA) ? "PASS" : "FAIL",  //checks phase A is within 207-253V and prints resul
           is_within_tolerance(rmsB) ? "PASS" : "FAIL", //checks phase B is within 207-253V and prints resul
           is_within_tolerance(rmsC) ? "PASS" : "FAIL"); //checks phase C is within 207-253V and prints resul

    int totalClipped = detect_clipping_A(samples, count) //counts clipped samples in phase A
                     + detect_clipping_B(samples, count) //counts clipped samples in phase B
                     + detect_clipping_C(samples, count); //counts clipped samples in total

    printf("Clipping     ->  %d clipped sample(s) detected across all phases\n", totalClipped); //prints total clipped count

    printf("\nFull report saved to results.txt\n"); //tells the user where to find the full report

    // Free allocated memory
    free(samples); //frees the dynamically allocated array to prevent a memory leak
    samples = NULL; //sets pointer to NULL so it cannot be accidentally used after being freed

    return 0; //exits with code 0 to signal the program completed successfully
}