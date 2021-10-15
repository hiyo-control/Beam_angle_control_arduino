#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

#define pose_time 1 // 1[ms]

#define Forward   2 // 10
#define Backward  1 // 01
#define Stop      0 // 00 (BREAK)

class MotorControl
{
    public:
    MotorControl(int pin1, int pin2, int pin_pwm);
    void control(int16_t input_command);
    
    private:
    int motor_direct      = Stop;
    int motor_direct_prev = Stop;
    int _pin1, _pin2, _pin_pwm;
    float Vref_command = 0;
};

#endif
