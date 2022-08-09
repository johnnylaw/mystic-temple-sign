#include "EyeStrip.h"

EyeStrip::EyeStrip(CRGB* buffer, int bufferLength, CRGB primaryColor, HotSpot* hotSpots):
  _buffer(buffer), 
  _bufferLength(bufferLength), 
  _primaryColor(primaryColor), 
  _hotSpots(hotSpots) {};

