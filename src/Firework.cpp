#include "Firework.h"
#include <math.h>

void Firework::init() {
    mColor = rand() % 8;
    mIsExploded = false;
    mLife = randMToN(0.95, 1.0) * M_MAX_LIFE;

    constexpr float SCALE_DOWN_FACTOR = 1e-4;
    float initCol = (float)(rand() % COLS);
    float initVelocity = ((float)(rand() % 4) + 2 + randZeroToOne()) *
                         ((float)-LINES) * (float)SCALE_DOWN_FACTOR;

    for (Particle& particle : mParticles) {
        particle.init();
        particle.setPosition((float)LINES, initCol);
        particle.setVelocity(initVelocity, 0);
    }
}

void Firework::update(int deltaTimeMs) {
    mLife -= deltaTimeMs;
    for (Particle& particle : mParticles) {
        particle.updatePosition(deltaTimeMs);
    }
    if (lifeInPercentage() < M_EXPLODE_T && !mIsExploded) {
        mIsExploded = true;
        explode();
    }
    if (mIsExploded) {
        simulateFadeOut();
    }
}

void Firework::explode() {
    for (Particle& particle : mParticles) {
        particle.setCenterToCurrentPosition();
        if ((mColor == 3 || mColor == 7) && rand() % 5 != 0) {
            // If the color is Magenta or Red, set it to heart shape
            // with a 4/5 probability
            setHeartShapeVelocity(particle);
        } else {
            setCircleShapeVelocity(particle);
        }
    }
}

void Firework::simulateFadeOut() {
    for (Particle& particle : mParticles) {
        if ((lifeInPercentage() < randMToN(0, M_EXPLODE_T) && rand() % 10 == 0) ||
            particle.distance() > pow(randMToN((float)18, 22), 2)) {
        // if (lifeInPercentage() > randMToN(M_EXPLODE_T, 1)) {
            particle.fadeOut();
        }
    }
}

void Firework::draw() {
    attron(COLOR_PAIR(mColor)); // turn on color scheme

    if (lifeInPercentage() > M_HIGHLIGHT_T &&
        lifeInPercentage() < M_EXPLODE_T) {
        attron(A_BOLD); // display bright characters right after explosion
    } else if (lifeInPercentage() < M_DIM_T) {
        attron(A_DIM); // display dim characters right before dying
    }

    for (Particle& particle : mParticles) {
        float rowPosition = NAN;
        float colPosition = NAN;
        std::tie<float, float>(rowPosition, colPosition) =
          particle.getPosition();
        if (!particle.hasFadeOut()) {
            mvaddch(rowPosition, colPosition, 'o');
        }
    }

    // turn off color scheme
    attroff(A_BOLD);
    attroff(A_DIM);
    attroff(COLOR_PAIR(mColor));
}

float Firework::lifeInPercentage() const { return (float)mLife / M_MAX_LIFE; }

float Firework::randZeroToOne() { return ((float)rand() / (float)RAND_MAX); }
float Firework::randMToN(float M, float N) {
    return (N - M) * randZeroToOne() + M;
}
float Firework::randVel() {
    // Generate the velocity in a reasonable range
    constexpr float SCALE_DOWN_FACTOR = 3e-5;
    float result = ((float)(rand() % 4) + 0.5 + 2 * randZeroToOne()) *
                   ((float)-LINES) * (float)SCALE_DOWN_FACTOR;
    return result;
}
std::pair<float, float> Firework::heartEquation(float angle) {
    float row = 6.5 * cos(angle) - 2.5 * cos(2 * angle) - cos(3 * angle) -
                0.5 * cos(4 * angle);
    float col = 16 * pow(sin(angle), 3);
    row *= 0.7;
    return std::make_pair(row, col);
}
void Firework::setHeartShapeVelocity(Particle& particle) {
    float velRowBase = NAN;
    float velColBase = NAN;
    static float scaler = 0.15 * randVel();
    std::tie(velRowBase, velColBase) =
      Firework::heartEquation(randMToN(0, 2 * M_PI));
    particle.setVelocity(velRowBase * scaler, velColBase * scaler);
}
void Firework::setCircleShapeVelocity(Particle& particle) {
    float angle = randMToN(0, 2 * M_PI);
    float velRowBase = 0.3 * sin(angle); // compensate the row-col size diff
    float velColBase = cos(angle);
    float scaler = 2.2 * randVel();
    particle.setVelocity(velRowBase * scaler, velColBase * scaler);
}
