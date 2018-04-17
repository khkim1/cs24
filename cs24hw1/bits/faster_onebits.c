#include <stdio.h>


int faster_onebits(unsigned int n);


int main(int argc, char **argv) {
    int i, res;
    unsigned int n;

    if (argc == 1) {
        printf("usage:  %s N1 [N2 ...]\n\n", argv[0]);
        printf("\tN1, N2, ... are positive integers\n\n");
        printf("\tFor each argument, the program prints out the number of\n"
               "\tbits that are 1 in the number.\n\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        res = sscanf(argv[i], "%u", &n);
        if (res == 1)
            printf("Input:  %u\tOne-bits:  %u\n\n", n, faster_onebits(n));
        else
            printf("Unparseable input \"%s\".  Skipping.\n\n", argv[i]);
    }

    return 0;
}


/*
 * Given an unsigned integer n, this function returns the nubmer of bits in n
 * that are 1, without the use of shifts and bit-masks
 */
int faster_onebits(unsigned int n) {
    int num_one_bits = 0;

    while (n > 0) {
        num_one_bits++;

        /* Remove the right most '1' from the bit representation of n */
        n = n & (n - 1);
    }

    return num_one_bits;
}
