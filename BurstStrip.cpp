#include "BurstStrip.h"

BurstStrip::BurstStrip(CartesianStrip* strips, int numStrips, int frequency, int velocity, CRGB base):
  _strips(strips), _numStrips(numStrips), _frequency(frequency), _velocity(velocity), _base(base) {
    calculateSpan();
  };

void BurstStrip::next() {
  if (!_isActive) {
    if (_clock == 0) createBurst();
    _clock--;
    return;
  }

  if (_isActive && _bursts[0].isDead() && _bursts[1].isDead()) {
    reset();
  }

  writeStrips();
}

void BurstStrip::writeStrips() {
  CartesianStrip strip;
  int bulbPosition;

  for (int stripInd = 0; stripInd < _numStrips; stripInd++) {
    strip = _strips[stripInd];

    for (int bulbInd = 0; bulbInd < strip.length; bulbInd++) {
      bulbPosition = strip.positionAtIndex(bulbInd);
      int multiplier = _bursts[0].multiplierAtPosition(bulbPosition)
        * _bursts[1].multiplierAtPosition(bulbPosition);

      uint8_t red = min(_base.red * multiplier / 10000, 255);
      uint8_t green = min(_base.green * multiplier / 10000, 255);
      uint8_t blue = min(_base.blue * multiplier / 10000, 255);
      CRGB color = CRGB(red, green, blue);
      
      strip.writeBuffer(bulbInd, color);
    }
  }
}

void BurstStrip::createBurst() {
  int position = random(_maxPosition - _minPosition) + _minPosition;
  int velocity = 3;
  _bursts[0] = { position, velocity, _minPosition, _maxPosition };
  _bursts[1] = { position, -velocity, _minPosition, _maxPosition };
  _isActive = true;
}

void BurstStrip::reset() {
  _clock = random(AVERAGE_TIME_DELAY) + 20;
  _isActive = false;
}

void BurstStrip::calculateSpan() {
  CartesianStrip strip;
  int position;

  for (int stripInd = 0; stripInd < _numStrips; stripInd++) {
    strip = _strips[stripInd];

    for (int bulbInd = 0; bulbInd < strip.length; bulbInd++) {
      position = strip.positionAtIndex(bulbInd);
      if (position < _minPosition) _minPosition = position;
      if (position > _maxPosition) _maxPosition = position;
    }
  }
}
