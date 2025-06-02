#pragma once
#include <Eigen/Dense>

struct Observation {
    double t;                      // [s] seconds since reference epoch (e.g., UNIX time, or t = 0)
    double ra;                     // [rad] Right Ascension
    double dec;                    // [rad] Declination
    Eigen::Vector3d observer_pos; // [m] Observer position in ECI (x, y, z)
};
