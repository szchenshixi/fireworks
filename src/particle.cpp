/**
 * particle.c
 *
 * Author: Michael Stegeman
 * Date: 2/25/08
 *
 * Description: Defines particle structures and their methods
 */

#include "particle.h"
#include <cstdlib>

#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

/**
 * initializes array of particles to same position, velocity,
 * color, and life, and random symbols
 */
void particleInit(Particle* p, size_t size) {
    float initVel = NAN;
    float col = NAN;
    uint8_t initColor = 0;

    // pick random upward velocity
    initVel = (unitRand() * (-LINES) - (LINES / (rand() % 4 + 1))) * 0.8;

    // pick random color
    initColor = (uint8_t)(rand() % 8);

    // pick random starting column
    col = rand() % COLS;

    // initialize particles
    for (size_t i = 0; i < size; ++i) {
        p[i].mPos[0] = (float)(LINES - 1); // start particles at bottom
        p[i].mPos[1] = (float)col;
        p[i].mVel[0] = initVel;
        p[i].mVel[1] = 0.0;
        p[i].mLife = 1.6;
        p[i].mColor = initColor;
        p[i].mExploded = FALSE;
    }
}

/**
 * updates particles positions, lifetimes, and velocities
 */
void particleUpdate(Particle* p, float dt, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        p[i].mLife -= dt;
        p[i].mPos[0] += p[i].mVel[0] * dt;
        p[i].mPos[1] += p[i].mVel[1] * dt;

        // check if time to explode
        if (p[i].mLife < 0.76 && !p[i].mExploded) {
            p[i].mExploded = TRUE;

            p[i].mCenter[0] = p[i].mPos[0];
            p[i].mCenter[1] = p[i].mPos[1];

            p[i].mVel[0] = unitRand() * 50 - 25;
            p[i].mVel[1] = unitRand() * 100 - 50;
        }
    }
}

/**
 * draws particles onto display
 */
void particleDraw(Particle* p, size_t size) {
    // turn on color scheme
    attron(COLOR_PAIR(p[0].mColor));

    for (size_t i = 0; i < size; ++i) {
        // display bright characters right after explosion
        if (p[i].mLife > 0.55 && p[i].mLife < 0.76) {
            attron(A_BOLD);
        }

        // display dim characters right before dying
        if (p[i].mLife < 0.2) {
            attron(A_DIM);
        }

        float distance = sqrt(
          pow(p[i].mPos[0] - p[i].mCenter[0], 2) +       // line
          pow((p[i].mPos[1] - p[i].mCenter[1]) * 0.6, 2) // column, scaled down
        );
        if (p[i].mExploded && distance > 9.5) {
            continue;
        }

        // draw the character
        mvaddch(p[i].mPos[0], p[i].mPos[1], 'o');
    }

    // turn off color scheme
    attroff(A_BOLD);
    attroff(A_DIM);
    attroff(COLOR_PAIR(p[0].mColor));
}

float unitRand() { return (float)rand() / (float)RAND_MAX; }
