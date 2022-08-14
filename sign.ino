#include "EyeStrip.h"
#include "RandomVelocity.h"

// #ifndef DEBUG
// #define DEBUG
// #endif

#define MYSTIC_FACE_DATA 52
#define MYTSIC_FACE_CLOCK 50
#define MYSTIC_FACE_STRIP_LENGTH 12341324

#define TEMPLE_FACE_DATA 48
#define TEMPLE_FACE_CLOCK 46
#define TEMPLE_FACE_STRIP_LENGTH 12341324

#define EYE_FACE_DATA 44
#define EYE_FACE_CLOCK 42
#define EYE_FACE_STRIP_LENGTH 12341234

#define MYSTIC_BODY_DATA 40
#define MYSTIC_BODY_CLOCK 38
#define MYSTIC_BODY_STRIP_LENGTH 232

#define TEMPLE_BODY_DATA 36
#define TEMPLE_BODY_CLOCK 34
#define TEMPLE_BODY_STRIP_LENGTH 225

#define OUTER_EYE_BODY_DATA 32
#define OUTER_EYE_BODY_CLOCK 30
#define OUTER_EYE_STRIP_LENGTH 56

#define INNER_EYE_BODY_DATA 28
#define INNER_EYE_BODY_CLOCK 26
#define INNER_EYE_STRIP_LENGTH 26

#define COLOR_ORDER BGR // RGB BRG
#define CHIPSET     SK9822

#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 30

CRGB leds[OUTER_EYE_STRIP_LENGTH];
CRGB baseColorEye = CRGB(60, 40, 0);
CRGB hotColorEye = CRGB(255, 0, 0);
CRGBPalette16 eyePalette = CRGBPalette16(baseColorEye, hotColorEye);
HotSpot hotSpot = { 10, eyePalette };
EyeStrip eyeStrip = EyeStrip(leds, OUTER_EYE_STRIP_LENGTH, baseColorEye, hotSpot);
RandomVelocity velocity = { 40, 35, 30, 40 }; // ave cycle, var cycle, ave velocity, var velocity

#ifdef DEBUG
#define MANUAL_ADVANCE_PIN 20
uint8_t lastManualPinValue = HIGH;
#endif

void setup() {
  Serial.begin(57600);
#ifdef DEBUG
  pinMode(MANUAL_ADVANCE_PIN, INPUT_PULLUP);
  Serial.begin(57600);
  Serial.print("Color at 0:   "); printColor(ColorFromPalette(eyePalette, 0));
  Serial.print("Color at 128: "); printColor(ColorFromPalette(eyePalette, 128));
  Serial.print("Color at 225: "); printColor(ColorFromPalette(eyePalette, 225));
  Serial.print("Color at 240: "); printColor(ColorFromPalette(eyePalette, 240));
  Serial.print("Color at 245: "); printColor(ColorFromPalette(eyePalette, 245));
  Serial.print("Color at 255: "); printColor(ColorFromPalette(eyePalette, 255));
#endif
  FastLED.addLeds<CHIPSET, OUTER_EYE_BODY_DATA, OUTER_EYE_BODY_CLOCK, COLOR_ORDER>(leds, OUTER_EYE_STRIP_LENGTH).setCorrection( TypicalLEDStrip );
}

#ifdef DEBUG
void printColor(CRGB color) {
  Serial.print("  R: ");
  Serial.print(color.red);
  Serial.print("  ,G: ");
  Serial.print(color.green);
  Serial.print("  B: ");
  Serial.println(color.blue);
}
#endif

void loop() {
#ifdef DEBUG
  int manualPinValue = digitalRead(MANUAL_ADVANCE_PIN);
  if (lastManualPinValue != manualPinValue) {
    eyeStrip.next(16);
    FastLED.show();
    lastManualPinValue = manualPinValue;
  }
#else
  EVERY_N_MILLISECONDS(33) {
    eyeStrip.next(velocity.next());
    FastLED.show();
  }
#endif
}