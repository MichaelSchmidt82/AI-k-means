#ifndef GLOBALS_H
#define GLOBALS_H

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

#endif // !GLOBALS_H
