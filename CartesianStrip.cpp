#include "CartesianStrip.h"

CartesianStrip::CartesianStrip(): length(0) {};

CartesianStrip::CartesianStrip(int* positions, int stripLength, CRGB* buffer):
  _positions(positions), length(stripLength), _buffer(buffer) {};

int CartesianStrip::positionAtIndex(int index) {
  return _positions[index];
}

void CartesianStrip::writeBuffer(int index, CRGB color) {
  _buffer[index] = color;
}
