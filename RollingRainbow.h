#include "HueWheel.h"
#include <FastLED.h>
#include "CartesianStrip.h"

#ifndef ROLLING_RAINBOW
#define ROLLING_RAINBOW

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