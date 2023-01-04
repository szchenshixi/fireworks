#include <iostream>
#include <array>

struct Particle {
    enum Axis {AXIS_ROW=0, AXIS_COL, AXIS_NUM};
    std::array<float, AXIS_NUM> mPosition;
    std::array<float, AXIS_NUM> mCenter;
    std::array<float, AXIS_NUM> mVelocity;  // num of col/rows per ms
};
