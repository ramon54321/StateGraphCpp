#pragma once
#include "constants.hpp"
#include "i_events.hpp"
#include <unordered_set>
#include <unordered_map>

namespace game_logic
{
    class EventManager
    {
    private:
        std::unordered_map<unsigned int, std::unordered_set<IEvents*>> observers;

    public:
        void attach(IEvents* observer, Events events);

        void fire_tick();
    };
}