#ifndef RTWEEKEND_H
#define RTWEEKEND_H

//common headers
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

//C++ std usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;
using std::ostream;


//constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//util functions

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}



#endif