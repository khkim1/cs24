#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "ffunc.h"

float fsum(FloatArray *floats);
float split_array(FloatArray *floats_former, FloatArray *floats_latter, FloatArray *floats);
float my_fsum(FloatArray *floats);

/* This function takes an array of single-precision floating point values,
 * and computes a sum in the order of the inputs.  Very simple.
 */
float fsum(FloatArray *floats) {
    float sum = 0;
    int i;

    for (i = 0; i < floats->count; i++)
        sum += floats->values[i];

    return sum;
}

/* This helper function takes two split arrays, the original array of floats
 * and recursively computes the pairwise sum after splitting the original array.
 */
float pairwise_sum(FloatArray *floats_former, FloatArray *floats_latter, FloatArray *floats) {

    // Index to split the float
    int m = (floats->count) / 2;
    int i;
    floats_former->count = m + 1;
    floats_latter->count = (floats->count) - m - 1;

    // Value arrays for the splits
    float *values_former = malloc((floats_former->count) * sizeof(float));
    float *values_latter = malloc((floats_latter->count) * sizeof(float));

    // Set default array values to 0
    memset(values_former, 0, (floats_former->count) * sizeof(float));
    memset(values_latter, 0, (floats_latter->count) * sizeof(float));

    // Split the original array values
    for (i = 0; i < floats->count; i++) {
        if (i <= m) {
            values_former[i] = floats->values[i];
        }
        else{
            values_latter[i - m - 1] = floats->values[i];
        }
    }

    // Set the value arrays for the splits
    floats_former->values = values_former;
    floats_latter->values = values_latter;

    // Calculate pairwise sum
    float sum = my_fsum(floats_former) + my_fsum(floats_latter);

    // Free allocated memory
    free(values_former);
    free(values_latter);

    return sum;

}

/* This function takes an array of single-precision floats and
 * computes the sum using the "pairwise sum" algorithm */
float my_fsum(FloatArray *floats) {

    float sum;
    int N = 3;

    // If array small enough, just use naive sum
    if (floats->count < N) {
        sum = fsum(floats);
    }
    // Else perform pairwise sum
    else {
        // Initialize split arrays
        FloatArray floats_former, floats_latter;

        // Split arrays and perform pairwise sum
        sum = pairwise_sum(&floats_former, &floats_latter, floats);
    }

    return sum;
}


int main() {
    FloatArray floats;
    float sum1, sum2, sum3, my_sum1, my_sum2, my_sum3;

    load_floats(stdin, &floats);
    printf("Loaded %d floats from stdin.\n", floats.count);

    /* Compute a sum, in the order of input. */
    sum1 = fsum(&floats);

    /* Use my_fsum() to compute a sum of the values.  Ideally, your
     * summation function won't be affected by the order of the input floats.
     */
    my_sum1 = my_fsum(&floats);

    /* Compute a sum, in order of increasing magnitude. */
    sort_incmag(&floats);
    sum2 = fsum(&floats);
    my_sum2 = my_fsum(&floats);

    /* Compute a sum, in order of decreasing magnitude. */
    sort_decmag(&floats);
    sum3 = fsum(&floats);
    my_sum3 = my_fsum(&floats);

    /* %e prints the floating-point value in full precision,
     * using scientific notation.
     */
    printf("Sum computed in order of input:  %e\n", sum1);
    printf("Sum computed in order of increasing magnitude:  %e\n", sum2);
    printf("Sum computed in order of decreasing magnitude:  %e\n", sum3);

    /* Print my sum when computed in different orders */
    printf("My sum computed in order of input:  %e\n", my_sum1);
    printf("My sum computed in order of increasing magnitude:  %e\n", my_sum2);
    printf("My sum computed in order of decreasing magnitude:  %e\n", my_sum3);

    return 0;
}

