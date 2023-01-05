#include "Particle.h"
#include <array>
#include <iostream>
#include <math.h>
#include <ncurses.h>
#include <tuple>

class Firework {
  public:
    Firework() = default;

    void init();
    void update(int deltaTimeMs);
    void draw();
    float lifeInPercentage() const;

  private:
    static float randZeroToOne();
    static float randMToN(float M, float N);
    static float randVel();
    static std::pair<float, float> heartEquation(float angle);
    static void setHeartShapeVelocity(Particle& particle);
    static void setCircleShapeVelocity(Particle& particle);

    void explode();
    void simulateFadeOut();

    static constexpr int MK_SIZE = 220;
    static constexpr int M_MAX_LIFE = 5000;   // millisecond
    // life less than this will explodes
    static constexpr float M_EXPLODE_T = 0.6;
    // life larger than this will highlight
    static constexpr float M_HIGHLIGHT_T = 0.3;
    // life less than this will dim
    static constexpr float M_DIM_T = 0.15;

    std::array<Particle, MK_SIZE> mParticles;
    int mColor = 0;
    bool mIsExploded = false;
    int mLife = M_MAX_LIFE; // millisecond
};
