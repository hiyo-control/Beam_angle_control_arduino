#include <MsTimer2.h>
#include "RotaryEncoder.h"
#include "MotorControl.h"
#include "State_FB.h"

void tickPath();
RotaryEncoder encoder = RotaryEncoder(3, 2, &tickPath);
MotorControl  motor   = MotorControl(12, 13, 6);
State_FB      FB      = State_FB();

void tickPath()
{
  encoder.tick();
}

float T_control  = 10;     // 制御周期[msec]
float T_sampling = 1/1000; // 測定周期[msec]

float angle_now  = 0 ;
float angle_prev = 0 ;

float input_command = 0;
float input_Vref    = 0 ;

float f[2]     = {3.0908, 0.2074}; // 線形状態FBゲイン
float state[2] = {0     , 0     }; // 状態変数：[角変位　角速度]

void setup()
{
  pinMode(8,OUTPUT);
  Serial.begin(115200);

  MsTimer2::set(T_sampling, sensor_get);
  MsTimer2::start();
}

void loop()
{
  digitalWrite(8,HIGH);
  MsTimer2::stop();

  state[0] =  angle_now;
  state[1] = (angle_now - angle_prev)/(T_control/1000);
  
  input_command = FB.control_input(f, state);
  motor.control( input_command );

  angle_prev = angle_now;
  Serial.println(angle_now * 180/PI);
  
  MsTimer2::start();
  delay(T_control);
}

void sensor_get()
{
  angle_now = encoder.getAngle();
}
