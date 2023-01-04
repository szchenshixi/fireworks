#include "Particle.h"

void Particle::init() {
    mFadeOut = false;
    mPosition = {0, 0};
    mCenter = {0, 0};
    mVelocity = {0, 0};
}

std::pair<float, float> Particle::getPosition() const {
    return std::make_pair(mPosition.at(AXIS_ROW), mPosition.at(AXIS_COL));
}

void Particle::updatePosition(int deltaTimeMs) {
    mPosition.at(AXIS_ROW) += mVelocity[Particle::AXIS_ROW] * deltaTimeMs;
    mPosition.at(AXIS_COL) += mVelocity[Particle::AXIS_COL] * deltaTimeMs;
}

void Particle::setPosition(float row, float column) {
    mPosition.at(AXIS_ROW) = row;
    mPosition.at(AXIS_COL) = column;
}

void Particle::setCenterToCurrentPosition() {
    mCenter.at(AXIS_ROW) = mPosition.at(AXIS_ROW);
    mCenter.at(AXIS_COL) = mPosition.at(AXIS_COL);
}

void Particle::setVelocity(float row, float column) {
    mVelocity.at(AXIS_ROW) = row;
    mVelocity.at(AXIS_COL) = column;
}

float Particle::distance() const {
    // Compensate for the row-col length difference
    return pow(2*(mPosition.at(AXIS_ROW) - mCenter.at(AXIS_ROW)), 2) +
           pow(mPosition.at(AXIS_COL) - mCenter.at(AXIS_COL), 2);
}

void Particle::fadeOut() { mFadeOut = true; }

bool Particle::hasFadeOut() const { return mFadeOut; }
