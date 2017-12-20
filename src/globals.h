#ifndef GLOBALS_H
#define GLOBALS_H

/* Constants */
const double NORM_MIN = 0.5;
const double NORM_MAX = 1.5;

/* Includes */
#include <cassert>
#include <cmath>
#include <limits>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/* Using statements */
using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::string;
using std::stringstream;
using std::vector;

/* Typedefs */
typedef vector<double> Dataset;
typedef Dataset* DatasetPtr;
typedef vector<Dataset> DataMatrix;
typedef vector<size_t> Affiliation;

typedef double (*DistanceCallback)(const Dataset & data,
    const Dataset & centroid,
    const size_t N_VALS);

#endif // !GLOBALS_H
