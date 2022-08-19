#include <FastLED.h>

#ifndef BURST
#define BURST

#define BURST_WIDTH 11
#define HALF_BURST_WIDTH (BURST_WIDTH / 2)
#define AVERAGE_TIME_DELAY 40
#define BASE_BRIGHTNESS 40

typedef struct Burst {
  int position;
  int velocity;
  int minPosition;
  int maxPosition;
  int halfWidth;
  bool isDead() {
    if (position + halfWidth < minPosition) return true;
    return position = halfWidth > maxPosition;
  }
  bool contains(int pos) {
    return position - halfWidth >= pos && position + halfWidth <= pos;
  }
} Burst;

class BurstStrip {
  public:
    BurstStrip(CartesianStrip* strips, int numStrips, int frequency, int velocity);
  
  private:
    CartesianStrip* strips;
    Burst _bursts[2];
    bool _isActive = false;
    int _brightnesses[BURST_WIDTH] = {
      BASE_BRIGHTNESS + 20, 
      BASE_BRIGHTNESS + 35, 
      BASE_BRIGHTNESS + 50, 
      BASE_BRIGHTNESS + 80, 
      BASE_BRIGHTNESS + 88, 
      BASE_BRIGHTNESS + 88, 
      BASE_BRIGHTNESS + 88, 
      BASE_BRIGHTNESS + 80, 
      BASE_BRIGHTNESS + 50, 
      BASE_BRIGHTNESS + 35, 
      BASE_BRIGHTNESS + 20
    };
    int _numStrips;
    int _frequency;
    int _velocity;
    int _minPosition = 0;
    int _maxPosition = 0;
    int _clock = 0;

  private:
    void calculateSpan();
};

#endif

BurstStrip::BurstStrip(CartesianStrip* strips, int numStrips, int frequency, int velocity):
  _strips(strips), _numStrips(numStrips), _frequency(frequency), _velocity(velocity) {
    calculateSpan();
  };

void Burst::next() {
  if (!_isActive) {
    if (_clock == 0) createBurst();
    _clock--;
    return;
  }

  if (_isActive && [burst[0].isDead() && burst[1].isDead()) {
    reset();
  }

  writeStrips();
}

void BurstStrip::writeStrips() {
  CartesianStrip strip;
  int bulbPosition;

  for (int stripInd = 0; stripInd < _numStrips; stripInd++) {
    strip = _strips[stripInd];

    for (int bulbInd = 0; bulbInd < strip.numPositions; bulbInd++) {
      bulbPosition = strip.positions[bulbInd];
      if (_bursts[0].contains(bulbPosition)) {}
        strip[bulbInd] = CRGB(BASE_BRIGHTNESS, BASE_BRIGHTNESS, BASE_BRIGHTNESS * 10 / 9);
    }
  }
}

void BurstStrip::createBurst() {
  int position = random(_maxPosition - _minPosition) + _minPosition;
  int velocity = 3;
  _bursts = {
    { position, velocity, _minPosition, _maxPosition, HALF_BURST_WIDTH }, 
    { position, -velocity, _minPosition, _maxPosition, HALF_BURST_WIDTH }
  };
  _isActive = true;
}

void BurstStrip::reset() {
  _clock = random(AVERAGE_TIME_DELAY) + 20;
  _isActive = false;
}

void BurstStrip::calculateSpan() {
  CartesianStrip strip;
  int position;

  for (int stripInd = 0; stripInd < numStrips; stripInd++) {
    strip = _strips[stripInd];

    for (int bulbInd = 0; bulbInd < strip.numPositions; bulbInd++) {
      position = strip.positions[bulbInd];
      if (position < _minPosition) _minPosition = position;
      if (position > _maxPosition) _maxPosition = position;
    }
  }
}
