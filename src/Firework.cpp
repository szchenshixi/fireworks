#include "Firework.h"

void Firework::init() {
    mColor = rand() % 8;
    mIsExploded = false;
    mLife = randMToN(0.95, 1.0) * M_MAX_LIFE;

    constexpr float SCALE_DOWN_FACTOR = 1e-4;
    float initCol = (float)(rand() % COLS);
    float initVelocity = ((float)(rand() % 4) + 2 + randZeroToOne()) *
                         ((float)-LINES) * (float)SCALE_DOWN_FACTOR;

    for (Particle& particle : mParticles) {
        particle.mPosition = {(float)LINES, initCol};
        particle.mVelocity = {initVelocity, 0};
    }
}

void Firework::update(uint32_t deltaTimeMs) {
    mLife -= deltaTimeMs;
    for (Particle& particle : mParticles) {
        particle.mPosition[Particle::AXIS_ROW] +=
          particle.mVelocity[Particle::AXIS_ROW] * deltaTimeMs;
        particle.mPosition[Particle::AXIS_COL] +=
          particle.mVelocity[Particle::AXIS_COL] * deltaTimeMs;
    }
    if (lifeInPercentage() < M_EXPLODE_T && mIsExploded == false) {
        mIsExploded = true;
        for (Particle& particle : mParticles) {
            particle.mCenter[Particle::AXIS_ROW] =
              particle.mPosition[Particle::AXIS_ROW];
            particle.mCenter[Particle::AXIS_COL] =
              particle.mPosition[Particle::AXIS_COL];

            auto currentVel = particle.mVelocity[Particle::AXIS_ROW];
            particle.mVelocity[Particle::AXIS_COL] =
              randMToN(-randVel(), randVel());
            particle.mVelocity[Particle::AXIS_ROW] =
              randMToN(-randVel(), randVel());
        }
    }
}

void Firework::draw() {
    attron(COLOR_PAIR(mColor)); // turn on color scheme

    if (lifeInPercentage() > 0.55 && lifeInPercentage() < 0.75) {
        attron(A_BOLD); // display bright characters right after explosion
    } else if (lifeInPercentage() < 0.2) {
        attron(A_DIM); // display dim characters right before dying
    }

    for (Particle& particle : mParticles) {
        mvaddch(particle.mPosition[Particle::AXIS_ROW],
                particle.mPosition[Particle::AXIS_COL],
                'o');
    }

    // turn off color scheme
    attroff(A_BOLD);
    attroff(A_DIM);
    attroff(COLOR_PAIR(mColor));
}

float Firework::lifeInPercentage() const { return (float)mLife / M_MAX_LIFE; }
