#include "RandomVelocity.h"

RandomVelocity::RandomVelocity(
  int averageCyclesBeforeChange, 
  int varianceCyclesBeforeChange,
  int averageMagnitude,
  int varianceMagnitude
):
  _aveCycles(averageCyclesBeforeChange),
  _varCycles(varianceCyclesBeforeChange),
  _aveMag(averageMagnitude),
  _varMag(varianceMagnitude) {};


int RandomVelocity::next() {
  if (++_currentCycle >= _velocity.lifetime) {
    mintNew();
    reset();
  }
  return _velocity.value;
}

void RandomVelocity::mintNew() {
  int velocity = random16(0, 2 * _varMag) - _varMag + _aveMag;
  int lifetime = random16(0, 2 * _varCycles) - _varCycles + _aveCycles;
  int sign = random8(0, 1) * 2 - 1;
  _velocity = { .value = velocity * sign, .lifetime = lifetime };
}

void RandomVelocity::reset() {
  _currentCycle = 0;
}