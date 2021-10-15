#include "State_FB.h"
#include "Arduino.h"

State_FB::State_FB()
{
}

float State_FB::control_input(float gain[], float state[])
{
    input = 0; // inputの初期化

    // 制御入力算出
    for (int i=0; i<2; i++)
    {
        input = -gain[i] * state[i] + input;
    }

    // 飽和処理
    if(input > 5)
    {
      input = 5;
    }
    if(input < -5)
    {
      input = -5;
    }

    return input;
}
