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
#ifdef DEBUG_RAND_VELOC
  Serial.print("currentCycle: "); Serial.println(_currentCycle);
  _velocity.print();
  Serial.println("");
#endif
  if (++_currentCycle >= _velocity.lifetime) {
    mintNew();
    reset();
  }
  return _velocity.value;
}

void RandomVelocity::mintNew() {
  int velocity = max(random16(0, 2 * _varMag) - _varMag + _aveMag, 1);
  int lifetime = max(random16(0, 2 * _varCycles) - _varCycles + _aveCycles, 5);
  int rand = random8(2);
  int sign = rand * 2 - 1;
#ifdef DEBUG_RAND_VELOC
  Serial.print("rand: "); Serial.println(rand);
  Serial.println("");
#endif
  _velocity = { .value = velocity * sign, .lifetime = lifetime };
}

void RandomVelocity::reset() {
  _currentCycle = 0;
}