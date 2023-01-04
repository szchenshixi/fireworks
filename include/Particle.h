#include <iostream>
#include <array>
#include <tuple>
#include <math.h>

class Particle {
public:
    enum Axis {AXIS_ROW=0, AXIS_COL, AXIS_NUM};

    // Accessors
    std::pair<float, float> getPosition() const;

    // Modifiers
    void init();
    void updatePosition(int deltaTimeMs);
    void setPosition(float row, float column);
    void setCenterToCurrentPosition();
    void setVelocity(float row, float column);
    float distance() const;
    void fadeOut();
    bool hasFadeOut() const;

private:
    std::array<float, AXIS_NUM> mPosition = {0, 0};
    std::array<float, AXIS_NUM> mCenter = {0, 0};
    std::array<float, AXIS_NUM> mVelocity = {0, 0};  // num of col/rows per ms
    bool mFadeOut = true;
};
