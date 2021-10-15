#include "Arduino.h"
#include "RotaryEncoder.h"

const int8_t Table[] = {0,-1,1,0, 1,0,0,-1, -1,0,0,1, 0,1,-1,0};

RotaryEncoder::RotaryEncoder(int pin1, int pin2, void (*fptr)())
{
  _pin1 = pin1;
  _pin2 = pin2;
  pinMode(_pin1, INPUT);
  pinMode(_pin2, INPUT);
  attachInterrupt(digitalPinToInterrupt(_pin1), fptr ,CHANGE);
  attachInterrupt(digitalPinToInterrupt(_pin2), fptr ,CHANGE);

  Signal_prev = 3;
  count       = 0;

}

float RotaryEncoder::getAngle(){
    return (float)count * (2*PI/2400);
}

void RotaryEncoder::tick(void)
{
  int    sig1   = digitalRead(_pin1);
  int    sig2   = digitalRead(_pin2);
  int8_t Signal = sig1 | (sig2<<1);

  if(Signal_prev != Signal)
  {
    value = Signal | (Signal_prev<<2);
    count += Table[ value ];
    
    Signal_prev = Signal;
  }
  else
  {
  }
}
