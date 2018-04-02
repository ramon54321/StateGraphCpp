#include <cstdio>
#include "state_management/state.hpp"

enum StateVariableLabel
{
    POSITION_X,
    POSITION_Y,
    POSITION_Z,
    MUNITIONS
};

int main()
{
    
    state_management::State<unsigned int, StateVariableLabel,
        unsigned long, float> state;

    


    //printf("Value: %.1f\n", value);

    return 0;
}
