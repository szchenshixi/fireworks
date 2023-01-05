/**
 * particle.h
 *
 * Author: Michael Stegeman
 * Date: 2/25/08
 *
 * Description: Forward declaration of particle structure
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct Particle {
    float mPos[2];
    float mCenter[2];
    float mVel[2];
    float mLife;
    uint8_t mColor;
    bool mExploded;
};

void particleInit(Particle* p, size_t size);

void particleUpdate(Particle* p, float dt, size_t size);

void particleDraw(Particle* p, size_t size);

float unitRand();
