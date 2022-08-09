#include "EyeStrip.h"

EyeStrip::EyeStrip(CRGB* buffer, int bufferLength, CRGB primaryColor, HotSpot hotSpot):
  _buffer(buffer), 
  _bufferLength(bufferLength), 
  _primaryColor(primaryColor), 
  _hotSpot(hotSpot) {
    _numPositions = _bufferLength * 256;
  };

void EyeStrip::next(int velocity) {
  writeBase();
  writeHotSpot();
  _position = (_position + velocity + _numPositions) % _numPositions;
}

void EyeStrip::writeBase() {
  for (int i = 0; i < _bufferLength; i++) {
    _buffer[i] = _primaryColor;
  }
}

void EyeStrip::writeHotSpot() {
  int firstBulb = _position / 256 + 1;
  int bulb;
  int dissipationDistance = _hotSpot.width * 256 / 2;
  int hotPoint = _position + dissipationDistance;

  for (int i = firstBulb; i < firstBulb + _hotSpot.width; i++) {
    int distance = min(abs(i * 256 - hotPoint) * 2 / _hotSpot.width, 255);
    bulb = i % _bufferLength;
    _buffer[i] = ColorFromPalette(_hotSpot.palette, 255 - distance);
  }
}