#include "HueWheel.h"
#include <FastLED.h>

#ifndef ROLLING_RAINBOW
#define ROLLING_RAINBOW

typedef struct CartesianStrip {
  int positions[];
  int numPositions;
  CRGB buffer[];
} CartesianStrip;

class RollingRainbow {
  public: 
    RollingRainbow(CartesianStrip* strips, int numStrips, int hueSpread, int velocity);
  
  private:
    CartesianStrip* _strips;
    int _numStrips;
    int _hueSpread;
    int _velocity;
    int _baseHue;

  public:
    void next();
};

#endif