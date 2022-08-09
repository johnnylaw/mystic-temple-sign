#include <FastLED.h>

typedef struct HotSpot {
  int width;
  CRGB color;
} HotSpot;

class EyeStrip {
  public:
    EyeStrip(
      CRGB* buffer, 
      int bufferLength, 
      CRGB primaryColor, 
      HotSpot* hotSpots
    );
  
  private:
    CRGB* _buffer;
    int _bufferLength;
    CRGB _primaryColor;
    HotSpot* _hotSpots;
};