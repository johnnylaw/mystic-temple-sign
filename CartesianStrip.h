#include <FastLED.h>

#ifndef CARTESIAN_STRIP
#define CARTESIAN_STRIP

class CartesianStrip {
  public:
    CartesianStrip();
    CartesianStrip(int* positions, int stripLength, CRGB* buffer);

  private:
    int* _positions;
    CRGB* _buffer;

  public:
    int length;
    int positionAtIndex(int index);
    void writeBuffer(int index, CRGB color);
};

#endif