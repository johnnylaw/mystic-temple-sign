#include "RollingRainbow.h"

RollingRainbow::RollingRainbow(
  CartesianStrip* strips,
  int numStrips,
  int hueSpread,
  int velocity
): _strips(strips), _numStrips(numStrips), _hueSpread(hueSpread), _velocity(velocity) {};

void RollingRainbow::next() {
  CartesianStrip strip;
  int bulbPosition;

  for (int stripInd = 0; stripInd < _numStrips; stripInd++) {
    strip = _strips[stripInd];
    for (int bulbInd = 0; bulbInd < strip.numPositions; bulbInd++) {
      bulbPosition = strip.positions[bulbInd];
      strip.buffer[bulbInd] = getHue(_baseHue + (bulbPosition - _baseHue) * _hueSpread);
    }
  }

  _baseHue -= _velocity;
}