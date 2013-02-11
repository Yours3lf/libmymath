#ifndef globals_h
#define globals_h

#include "mymath/mymath.h"
#include <list>
#include <vector>

using namespace mymath;
using namespace std;

/*
 * Global variables
 */

//use quasi random numbers or not
//only works on linux
//it gives better random number distribution
#define USE_QRNG 1

#define COUNT_INTERSECTIONS 0

#define GAMMA_CORRECTION 1

static const float fepsilon = 0.0001f;
static const vec3 epsilon( fepsilon );

static const int hit = 1, inside = -1, miss = 0;

static const int gridsize = 8;
static const int gridshift = 3;

static int num_samples = 64;
static int trace_depth = 8;

#if COUNT_INTERSECTIONS == 1
static unsigned int intersections = 0;
#endif

#endif
