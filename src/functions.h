/*




*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "globals.h"

/* Prototypes */
double euclidean_dist(const Dataset & data,
    const Dataset & centroid,
    const size_t N_VALS);

double manhattan_dist(const Dataset & data,
    const Dataset & centroid,
    const size_t N_VALS);

double arithmetic_mean(const Dataset & data,
    const Dataset & centroid,
    DistCallback dist_f,
    const size_t N_VALS);

double geometric_mean(const Dataset & data,
    const Dataset & centroid,
    DistCallback dist_f,
    const size_t N_VALS);

double harmonic_mean (const Dataset & data,
    const Dataset & centroid,
    DistCallback dist_f,
    const size_t N_VALS);

void normailize (DataMatrix & data,
    const size_t N_VALS,
    bool train);

double reciprocal (double x);

template<typename T>
inline void quick_swap(T & x, T & y);

/* Distance calculators */
double euclidean_dist(const Dataset & data,
    const Dataset & centroid,
    const size_t N_VALS) {

    double sum = 0;
    for (size_t f = 0; f < N_VALS; f++)
        sum += pow(data[f] - centroid[f], 2);

    return sqrt(sum);
}

double manhattan_dist(const Dataset & data,
        const Dataset & centroid,
        const size_t N_VALS) {

        double sum = 0;
        for (size_t f = 0; f < N_VALS; f++)
            sum += abs(data[f] - centroid[f]);

        return sum;
}

/* Mean calculators */
double arithmetic_mean (const Dataset & data,
    const Dataset & centroid,
    DistCallback dist_f,
    const size_t N_VALS) {

    double sum = 0;
    for (size_t f = 0; f < N_VALS; f++)
        sum += dist_f(data, centroid, N_VALS);

    return sum / N_VALS;
}

double geometric_mean(const Dataset & data,
    const Dataset & centroid,
    DistCallback dist_f,
    const size_t N_VALS) {

    const double TOO_LARGE = 1.e64;
    const double TOO_SMALL = 1.e-64;
    double sum_log = 0.0;
    double product = 1.0;

    for (size_t f = 0; f < N_VALS;f++) {
        product *= dist_f(data, centroid, N_VALS);

        if (product > TOO_LARGE || product < TOO_SMALL) {
            sum_log+= std::log(product);
            product = 1;
        }
    }

    return std::exp((sum_log + std::log(product)) / N_VALS);
}

double harmonic_mean (const Dataset & data,
    const Dataset & centroid,
    DistCallback dist_f,
    const size_t N_VALS) {

    double sum = 0;
    for (size_t f = 0; f < N_VALS; f++)
        sum += reciprocal(dist_f(data, centroid, N_VALS));

    return N_VALS / sum;
}

/* Data Transforms */
void normailize (DataMatrix & data,
    const size_t N_VALS,
    bool train) {

    /* Keep mins/maxs static to normailize test data with trainging values */
    static Dataset mins(N_VALS);
    static Dataset maxs(N_VALS);

    double denom;

    if (train) {
        for (size_t a = 0; a < N_VALS; a++) {
            double min = numeric_limits<double>::max();
            double max = numeric_limits<double>::max() * -1;
            for (size_t d = 0; d < data.size(); d++) {
                if (data[d][a] < min)
                    min = data[d][a];

                if (data[d][a] > max)
                    max = data[d][a];
            }

            mins[a] = min;
            maxs[a] = max;
        }
    }

    for (size_t a = 0; a < N_VALS; a++) {
        denom = maxs[a] - mins[a];
        for (size_t d = 0; d < data.size(); d++)
            data[d][a] = NORM_MIN + ((data[d][a] - mins[a]) * (NORM_MAX - NORM_MIN)) / denom;
    }
}

/* helpers */
double reciprocal (double x) {
    union {
        double dbl;
        unsigned long long ull;
    } u = {.dbl=(x*=x)};        // x*x = pow( x, 2 )

    u.ull = ( 0xbfcdd6a18f6a6f52ULL - u.ull ) >> (unsigned char)1;

    return u.dbl;
}

template<typename T>
inline void quick_swap(T & x, T & y) {
    if (x != y) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
}

#endif
