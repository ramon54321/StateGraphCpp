#pragma once
#include <iostream>

namespace game_logic
{
    class IEvents
    {
    public:
        virtual void tick()
        {
            std::cout << "Tick..." << std::endl;
        }
    };
}