/*




*/

/* Prototypes */
inline double euclidean_dist(double x1, double x2);

void manhattan_dist (const DataMatrix & data,
    const DataMatrix & centroids,
    Affiliation & affiliations,
    DataMatrix & distances,
    const size_t K,
    const size_t N_VALS);

double arithmetic_mean_dist (const Dataset & data,
    const Dataset & centroid,
    const size_t N_VALS);

void normailize (DataMatrix & data,
    const size_t N_VALS,
    bool train);

/* Distance calculators */
inline double euclidean_dist(double x1, double x2) {
    return pow(x2 - x1, 2);
}

/* Helpers */
template<typename T>
inline void quick_swap(T & x, T & y);

/* Experimental - Often bad */
// TODO: rewrite for modularity
void manhattan_dist (const DataMatrix & data,
    const DataMatrix & centroids,
    Affiliation & affiliations,
    DataMatrix & distances,
    const size_t K,
    const size_t N_VALS) {

    double sum = 0;

    for (size_t d = 0; d < data.size(); d++) {
        double min = numeric_limits<double>::max();
        size_t min_idx = 0;
        for (size_t k = 0; k < K; k++) {

            const Dataset& c = centroids[k];
            for (size_t a = 0; a < N_VALS; a++)
                sum += abs(data[d][a] - c[a]);

            distances[d][k] = sum;
            if (distances[d][k] < min) {
                min = distances[d][k];
                min_idx = k;
            }
            sum = 0;
        }
        affiliations[d] = min_idx;
    }
}

/* Mean calculators */
double arithmetic_mean_dist (const Dataset & data,
    const Dataset & centroid,
    const size_t N_VALS) {

    double sum = 0;
    for (size_t v = 0; v < N_VALS; v++)
        sum += euclidean_dist(data[v], centroid[v]);

    return sqrt(sum);
};

/* Data Transforms */
void normailize (DataMatrix & data,
    const size_t N_VALS,
    bool train) {

    /* Keep mins/maxs static to normailize test data with trainging values */
    static Dataset mins(N_VALS);
    static Dataset maxs(N_VALS);

    if (train) {
        for (size_t a = 0; a < N_VALS; a++) {
            double min = numeric_limits<double>::max();
            double max = numeric_limits<double>::max() * -1;
            double denom;
            for (size_t d = 0; d < data.size(); d++) {
                if (data[d][a] < min)
                    min = data[d][a];

                if (data[d][a] > max)
                    max = data[d][a];
            }
            mins[a] = min;
            maxs[a] = max;
            denom = max - min;

            for (size_t d = 0; d < data.size(); d++)
                data[d][a] = (data[d][a] - min) / denom;
        }
    } else {
        for (size_t a = 0; a < N_VALS; a++) {
            double denom = maxs[a] - mins[a];
            for (size_t d = 0; d < data.size(); d++)
                data[d][a] = (data[d][a] - mins[a]) / denom;
        }
    }
}

template<typename T>
inline void quick_swap(T & x, T & y) {
    if (x != y) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
}
