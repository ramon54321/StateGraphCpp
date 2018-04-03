#include "event_manager.hpp"

namespace game_logic
{
    void EventManager::attach(IEvents* observer, Events events)
    {
        for (int shift = 0; shift < 32; shift++)
        {
            unsigned int flag = 1 << shift;
            if ((events & flag) == flag)
                observers[flag].insert(observer);
        }
    }

    void EventManager::fire_tick()
    {
        for (IEvents* observer : observers[Events::TICK])
            observer->tick();
    }
}