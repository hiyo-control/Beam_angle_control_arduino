#include "MotorControl.h"
#include "Arduino.h"

MotorControl::MotorControl(int pin1, int pin2, int pin_pwm)
{
  _pin1    = pin1;
  _pin2    = pin2;
  _pin_pwm = pin_pwm;
  
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
}

void MotorControl::control(int16_t input_command)
{
  motor_direct_prev = motor_direct;
  
  if(input_command > 0)
  {
    motor_direct = Forward; // 2 = 10
  }
  else if(input_command < 0)
  {
    motor_direct = Backward; // 1 = 01
  }
  else
  {
    motor_direct = Stop; // 0 = 00
  }

  if(motor_direct != motor_direct_prev)
  {
    digitalWrite(_pin1, 0);
    digitalWrite(_pin2, 0);
    delay(pose_time);
  }

  Vref_command = abs( input_command*255/5 );
  analogWrite(_pin_pwm, Vref_command);

  digitalWrite(_pin1,  motor_direct     &1);
  digitalWrite(_pin2, (motor_direct>>1) &1);
}
