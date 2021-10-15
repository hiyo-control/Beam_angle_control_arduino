#ifndef RotaryEncoder_h
#define RotaryEncoder_h
#include "Arduino.h"

class RotaryEncoder
{
public:
    RotaryEncoder(int pin1, int pin2, void(*fptr)());
    long  getValue();
    float getAngle();
    void  tick(void);
private:
    int    _pin1, _pin2, value;
    int8_t Signal_prev;
    long   count;
};

#endif
