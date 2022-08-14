#include "EyeStrip.h"
// #ifndef DEBUG
// #define DEBUG
// #endif

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

#ifdef DEBUG
  Serial.print("Position: ");
  Serial.print(_position);
  Serial.print(", First bulb: ");
  Serial.println(firstBulb);
#endif

  for (int i = firstBulb; i < firstBulb + _hotSpot.width; i++) {
    int distanceFromHotSpot = distance(hotPoint, i);
    int fractionalDistance = min(distanceFromHotSpot * 2 / _hotSpot.width, 255);
    bulb = i % _bufferLength;
    _buffer[bulb] = ColorFromPalette(_hotSpot.palette, scale8(255 - fractionalDistance, 240));
#ifdef DEBUG
    Serial.print("  bulb: ");
    Serial.print(bulb);
    Serial.print("  R: ");
    Serial.print(_buffer[bulb].red);
    Serial.print("  ,G: ");
    Serial.print(_buffer[bulb].green);
    Serial.print("  B: ");
    Serial.println(_buffer[bulb].blue);
#endif
  }
}

int EyeStrip::distance(int position, int bulb) {
  return abs(bulb * 256 - position);
}