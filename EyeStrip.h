#include <FastLED.h>

typedef struct HotSpot {
  int width;
  CRGBPalette16 palette;
} HotSpot;

class EyeStrip {
  public:
    EyeStrip(
      CRGB* buffer, 
      int bufferLength, 
      CRGB primaryColor, 
      HotSpot hotSpot
    );
  
  private:
    CRGB* _buffer;
    int _bufferLength;
    CRGB _primaryColor;
    HotSpot _hotSpot;
    int _position = 0;
    int _numPositions;

  public:
    void next(int velocity); // velocity in bulbs per frame * 256

  private:
    void writeBase();
    void writeHotSpot();
};
