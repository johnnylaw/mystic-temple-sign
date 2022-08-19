#include "EyeStrip.h"
#include "RandomVelocity.h"

// #ifndef DEBUG
// #define DEBUG
// #endif

#define MYSTIC_FACE_DATA 52
#define MYSTIC_FACE_CLOCK 50
#define MYSTIC_FACE_LENGTH 159
#define MYSTIC_FACE_START 0

#define TEMPLE_FACE_DATA 48
#define TEMPLE_FACE_CLOCK 46
#define TEMPLE_FACE_LENGTH 160
#define TEMPLE_FACE_START MYSTIC_FACE_START + MYSTIC_FACE_LENGTH

#define EYE_FACE_DATA 44
#define EYE_FACE_CLOCK 42
#define EYE_FACE_LENGTH 115
#define EYE_FACE_START TEMPLE_FACE_START + TEMPLE_FACE_LENGTH

#define MYSTIC_BODY_DATA 40
#define MYSTIC_BODY_CLOCK 38
#define MYSTIC_BODY_LENGTH 232
#define MYSTIC_BODY_START EYE_FACE_START + EYE_FACE_LENGTH

#define TEMPLE_BODY_DATA 36
#define TEMPLE_BODY_CLOCK 34
#define TEMPLE_BODY_LENGTH 225
#define TEMPLE_BODY_START MYSTIC_BODY_START + MYSTIC_BODY_LENGTH

#define OUTER_EYE_BODY_DATA 32
#define OUTER_EYE_BODY_CLOCK 30
#define OUTER_EYE_BODY_LENGTH 56
#define OUTER_EYE_BODY_START TEMPLE_BODY_START + TEMPLE_BODY_LENGTH

#define INNER_EYE_BODY_DATA 28
#define INNER_EYE_BODY_CLOCK 26
#define INNER_EYE_BODY_LENGTH 26
#define INNER_EYE_BODY_START OUTER_EYE_BODY_START + OUTER_EYE_BODY_LENGTH

#define COLOR_ORDER BGR // RGB BRG
#define CHIPSET     SK9822

#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 30

CRGB leds[INNER_EYE_BODY_START + INNER_EYE_BODY_LENGTH];
CRGB baseColorEye = CRGB(60, 40, 0);
CRGB hotColorEye = CRGB(255, 0, 0);
CRGBPalette16 eyePalette = CRGBPalette16(baseColorEye, hotColorEye);
HotSpot hotSpotOuter = { 10, eyePalette };
HotSpot hotSpotInner = { 5, eyePalette };
EyeStrip eyeStripOuter = EyeStrip(leds + OUTER_EYE_BODY_START, OUTER_EYE_BODY_LENGTH, baseColorEye, hotSpotOuter);
EyeStrip eyeStripInner = EyeStrip(leds + INNER_EYE_BODY_START, INNER_EYE_BODY_LENGTH, baseColorEye, hotSpotInner);
RandomVelocity velocityOuterEye = { 40, 35, 30, 40 }; // ave cycle, var cycle, ave velocity, var velocity
RandomVelocity velocityInnerEye = { 40, 35, 15, 20 }; // ave cycle, var cycle, ave velocity, var velocity

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
  FastLED.addLeds<CHIPSET, MYSTIC_FACE_DATA, MYSTIC_FACE_CLOCK, COLOR_ORDER>(leds + MYSTIC_FACE_START, MYSTIC_FACE_LENGTH).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, TEMPLE_FACE_DATA, TEMPLE_FACE_CLOCK, COLOR_ORDER>(leds + TEMPLE_FACE_START, TEMPLE_FACE_LENGTH).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, EYE_FACE_DATA, EYE_FACE_CLOCK, COLOR_ORDER>(leds + EYE_FACE_START, EYE_FACE_LENGTH).setCorrection( TypicalLEDStrip );

  FastLED.addLeds<CHIPSET, MYSTIC_BODY_DATA, MYSTIC_BODY_CLOCK, COLOR_ORDER>(leds + MYSTIC_BODY_START, MYSTIC_BODY_LENGTH).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, TEMPLE_BODY_DATA, TEMPLE_BODY_CLOCK, COLOR_ORDER>(leds + TEMPLE_BODY_START, TEMPLE_BODY_LENGTH).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, INNER_EYE_BODY_DATA, INNER_EYE_BODY_CLOCK, COLOR_ORDER>(leds + INNER_EYE_BODY_START, INNER_EYE_BODY_LENGTH).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, OUTER_EYE_BODY_DATA, OUTER_EYE_BODY_CLOCK, COLOR_ORDER>(leds + OUTER_EYE_BODY_START, OUTER_EYE_BODY_LENGTH).setCorrection( TypicalLEDStrip );
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
    eyeStripOuter.next(16);
    FastLED.show();
    lastManualPinValue = manualPinValue;
  }
#else
  EVERY_N_MILLISECONDS(33) {
    for (int i = 0; i < EYE_FACE_START + EYE_FACE_LENGTH; i++) {
      leds[i] = CRGB(10, 10, 20);
    }
    for (int i = MYSTIC_BODY_START; i < MYSTIC_BODY_START + MYSTIC_BODY_LENGTH; i++) {
      leds[i] = CRGB(20, 0, 0);
    }
    for (int i = TEMPLE_BODY_START; i < TEMPLE_BODY_START + TEMPLE_BODY_LENGTH; i++) {
      leds[i] = CRGB(0, 0, 20);
    }
    eyeStripOuter.next(velocityOuterEye.next());
    eyeStripInner.next(velocityInnerEye.next());
    FastLED.show();
  }
#endif
}