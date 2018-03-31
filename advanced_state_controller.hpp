#pragma once
#include "state_controller.hpp"

namespace state_management
{
    template <typename StateIDType, typename GraphIDType,
        typename GraphKeyType, typename GraphValueType>
    class AdvancedStateController : public StateController<StateIDType,
        GraphIDType, GraphKeyType, GraphValueType>
    {

    public:
        /*
        Adds keys with given change and after given duration.
        */
        void lerp_by_duration(StateIDType state_id, GraphIDType graph_id,
            GraphKeyType start_t, GraphKeyType duration_t,
            GraphValueType change_v)
        {
            GraphValueType start_v = this->get_value(state_id, graph_id,
                GraphInterpolationType::LINEAR, start_t);
            this->add_key(state_id, graph_id, start_t, start_v);
            this->add_key(state_id, graph_id, start_t + duration_t,
                start_v + change_v);
        }
    };
}