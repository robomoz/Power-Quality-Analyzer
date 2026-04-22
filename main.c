
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

int main(int arc, char *argv[]){
    WaveformSample *data = NULL;

    int num_rows = 0;


    if (argc != 2) {
        printf("Usage: %s <csv_file>\n", argv[0]);
        return 1;
    }

    //load data from cvs
    if (load_data(argv[1], &data, &num_rows) != 0) {
        printf("Error loading file!\n");
        return 1;
    }

    printf("Successfully loaded %d rows of data.\n", num_rows);


    double rms_A = calculate_rms(data, num_rows, 'A');
    printf("Phase A RMS voltage: %.2f V\n", rms_A);


    free(data);

    return 0;
}
