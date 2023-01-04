#include "Particle.h"
#include <array>
#include <iostream>
#include <math.h>
#include <ncurses.h>

class Firework {
  public:
    Firework() = default;

    void init();
    void update(uint32_t deltaTimeMs);
    void draw();
    float lifeInPercentage() const;

  private:
    static float randZeroToOne() { return ((float)rand() / (float)RAND_MAX); }
    static float randMToN(float M, float N) {
        return (N - M) * randZeroToOne() + M;
    }
    static float randVel() {
        // Generate the velocity in a reasonable range
        constexpr float SCALE_DOWN_FACTOR = 1e-4;
        float result = ((float)(rand() % 4) + 0.5 + 2 * randZeroToOne()) *
                         ((float)-LINES) * (float)SCALE_DOWN_FACTOR;
        return result;
    }

    static constexpr int MK_SIZE = 200;
    static constexpr int M_MAX_LIFE = 3000;  // millisecond
    static constexpr float M_EXPLODE_T = 0.4;  // life less than this explodes

    std::array<Particle, MK_SIZE> mParticles;
    int mColor = 0;
    bool mIsExploded = false;
    int mLife = M_MAX_LIFE;  // millisecond
};
