#ifndef STATE_FB_H
#define STATE_FB_H
#include "Arduino.h"

class State_FB
{
    public:
    State_FB();
    float control_input(float gain[], float state[]);

    private:
    float input = 0;
};

#endif
