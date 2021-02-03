#pragma once

#include <vector>
#include <ctime>
#include <cmath>
#include <random>

#include "Graph2D.h"
#include "Settings.h"

namespace cmst
{

    /// Generate an integer in the range [a, b]
    ///
    /// Needs to be improved using other random classes
    int randomInt(int a, int b);

    /// Generate a floating-point number in the range [a, b]
    ///
    /// Needs to be improved using other random classes
    double randomDouble(double a, double b);

    /// Generate some random points.
    ///
    /// The number of points is generated randomly in the range [num_lower_bound, num_upper_bound],
    /// and the x, y coordinates of the points are respectively in the range
    /// [0, x_upper_bound] and [0, y_upper_bound].
    std::vector<Point2D> TestcaseGenerator(int num_lower_bound = 100, int num_upper_bound = 500,
                                  double x_upper_bound = MAX_X, double y_upper_bound = MAX_Y);
}
