#pragma once

#include <sstream>

#ifdef DEBUG
extern std::stringstream debugout;
#endif // DEBUG

/// Maximum x coordinate.
///
/// x coordinates should be in the range [0, MAX_X]
extern double MAX_X;

/// Maximum y coordinate.
///
/// y coordinates should be in the range [0, MAX_Y]
extern double MAX_Y;

/// Allowance for possible epsilon loss
extern const double EPS_MIN;
