/**
 * A benchmark UI.
 *
 * It handles user input and cleanly outputs results given a benchmarking
 * function.
 */

#include <bench.h>
#include <b2exp.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Usage menu.
void usage(char* name) {
    printf(
        "%s [options...]\n"
        "\n"
        "Benchmarks b2exp against the standard library exp2 function.\n"
        "\n"
        "Options:\n"
        "  -f <double>: The start of the input range.\n"
        "  -s <double>: The step between inputs.\n"
        "  -t <long>: The number of inputs to test.\n"
        "  -p <precision>: The binary precision to test into.\n"
        "      It is recommended not to use -s, -t, or -f with this.\n"
        "  -h: Prints this help.\n"
        ,name);
}

int main(int argc, char* const* argv) {
    // The first input.
    double first = -2048.0;
    // The binary precision step.
    int precision = -16;
    // The step.
    double step = scalbn(1.0, precision);
    // The number of iterations.
    uint64_t times = 1UL << (12 - precision);

    // Option handling.
    int c;
    while ((c = getopt(argc, argv, "f:s:t:p:h")) != -1) switch (c) {
        case 'f':
            first = atof(optarg);
            break;
        case 's':
            step = atof(optarg);
            break;
        case 't':
            times = atoi(optarg);
            break;
        case 'p':
            precision = atoi(optarg);
            step = scalbn(1.0, precision);
            times = 1UL << (12 - precision);
            break;
        case 'h':
            usage(argv[0]);
            return 0;
    }

    // Benchmark.
    uint64_t a_sec, a_nsec, b_sec, b_nsec;

    double last = bench_f64(
        &b2exp,
        &exp2,
        first,
        step,
        times,
        &a_sec,
        &a_nsec,
        &b_sec,
        &b_nsec
    );

    // Print results.
    printf(
        "Overall: %lf ns between %lf and %lf\n"
        "  std: %lf ns total %lf ns/iter\n"
        "  cst: %lf ns total %lf ns/iter\n"
        "  diff: %lf std/cst %lf cst/std\n",
        ((double)a_sec + b_sec) * 1000000000 + (a_nsec + b_nsec), first, last,
        (double)b_sec * 1000000000 + b_nsec, ((double)b_sec * 1000000000 + b_nsec) / times,
        (double)a_sec * 1000000000 + a_nsec, ((double)a_sec * 1000000000 + a_nsec) / times,
        ((double)b_sec * 1000000000 + b_nsec) / ((double)a_sec * 1000000000 + a_nsec),
        ((double)a_sec * 1000000000 + a_nsec) / ((double)b_sec * 1000000000 + b_nsec)
    );

    return 0;
}
