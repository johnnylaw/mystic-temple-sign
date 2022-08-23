#include <FastLED.h>
#include "CartesianStrip.h"

#ifndef BURST
#define BURST

#define BURST_WIDTH 11
#define HALF_BURST_WIDTH (BURST_WIDTH / 2)
#define AVERAGE_TIME_DELAY 40
#define HALF_WIDTH ((BURST_WIDTH + 1) / 2)
int burstBrightnesses[HALF_WIDTH] = { 200, 150, 120, 100, 90, 70 };

typedef struct Burst {
  int position;
  int velocity;
  int minPosition;
  int maxPosition;
  bool isDead() {
    return position - HALF_WIDTH >= maxPosition || position + HALF_WIDTH <= minPosition;
  };
  int multiplierAtPosition(int pos) {
    int diff = abs(pos - position);
    if (diff >= HALF_WIDTH) return 100;
    return burstBrightnesses[diff];
  };
} Burst;

class BurstStrip {
  public:
    BurstStrip(CartesianStrip* strips, int numStrips, int frequency, int velocity, CRGB base);
  
  private:
    CartesianStrip* _strips;
    Burst _bursts[2];
    bool _isActive = false;
    int _numStrips;
    int _frequency;
    int _velocity;
    CRGB _base;
    int _minPosition = 0;
    int _maxPosition = 0;
    int _clock = 0;

  public:
    void next();

  private:
    void calculateSpan();
    void createBurst();
    void reset();
    void writeStrips();
};

#endif
