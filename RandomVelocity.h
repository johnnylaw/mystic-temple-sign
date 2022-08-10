#include <FastLED.h>

typedef struct Velocity {
  int value;
  int lifetime;
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