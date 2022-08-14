#include <FastLED.h>

#ifndef DEBUG_RAND_VELOC
#define DEBUG_RAND_VELOC
#endif

typedef struct Velocity {
  int value;
  int lifetime;
#ifdef DEBUG_RAND_VELOC
  void print() {
    Serial.print("value: "); Serial.print(value); Serial.print(", lifetime: "); Serial.println(lifetime);
  };
#endif
} Velocity;

class RandomVelocity {
  public:
    RandomVelocity(
      int averageCyclesBeforeChange,
      int varianceCyclesBeforeChange,
      int averageMagnitude,
      int varianceMagnitude
    );

  private:
    int _currentCycle = 0;
    int _aveCycles;
    int _varCycles;
    int _aveMag;
    int _varMag;
    Velocity _velocity = { 0, 0 };

  public:
    int next();

  private:
    void mintNew();
    void reset();
};
