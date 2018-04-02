#pragma once
#include "state_management/state.hpp"

namespace game_logic
{
    enum StateVariableLabel
    {
        POSITION_X,
        POSITION_Y,
        ROTATION
    };

    class LogicCore
    {
    private:
        state_management::State<unsigned int, StateVariableLabel,
            unsigned long, float>& state;
    
    public:
        LogicCore(state_management::State<unsigned int, StateVariableLabel,
            unsigned long, float>& state)
        {
            this->state = state;
        }


    };
}