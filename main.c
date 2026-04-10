#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include"io.h"
//memory allocation
int main() {
    int num_rows = 1000;
    WaveformSample *data = (WaveformSample *)malloc(num_rows * sizeof(WaveformSample));

    if (data == NULL){
        printf("Memory allocation failed! \n ");
        return 1;
    }

    //loading function
    if (load_data("power_quality_log.csv", data, num_rows) != 0){
        printf("Error loading file!\n");
        free(data);  //clearing data
        return 1;
    }

    printf("Successfully loaded %d rows of data. \n", num_rows);
    free(data);
    return 0;
}