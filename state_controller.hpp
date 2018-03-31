#pragma once
#include <unordered_map>
#include "state.hpp"

namespace state_management
{
    template <typename StateIDType, typename GraphIDType,
        typename GraphKeyType, typename GraphValueType>
    class StateController
    {
    private:
        std::unordered_map<StateIDType, State<GraphIDType,
            GraphKeyType, GraphValueType>> states;

    public:
        /*
        Adds or replaces a state to the manager with the given state_id.
        */
        void add_state(StateIDType state_id)
        {
            states[state_id] = State<GraphIDType, GraphKeyType,
                GraphValueType>();
        }

        /*
        Removes a state from the manager by state_id.
        */
        void remove_state(StateIDType state_id)
        {
            states.erase(state_id);
        }

        /*
        Adds or replaces a graph to the state with the given state_id.
        */
        void add_graph(StateIDType state_id, GraphIDType graph_id)
        {
            states[state_id].add_graph(graph_id);
        }

        /*
        Adds value at time t to given graph in the given state.
        */
        void add_key(StateIDType state_id, GraphIDType graph_id,
            GraphKeyType t, GraphValueType v)
        {
            states[state_id].add_key(graph_id, t, v);
        }

        /*
        Removes key at time t in the given graph in the given state.
        */
        void remove_key(StateIDType state_id, GraphIDType graph_id,
            GraphKeyType t)
        {
            states[state_id].remove_key(graph_id, t);
        }

        /*
        Removes all keys in range (Inclusive).
        */
        void remove_range(StateIDType state_id, GraphIDType graph_id,
            GraphKeyType from_t, GraphKeyType to_t)
        {
            states[state_id].remove_range(graph_id, from_t, to_t);
        }

        /*
            Gets value at time t from given graph with given interpolation.
        */
        GraphValueType get_value(StateIDType state_id, GraphIDType graph_id,
            GraphInterpolationType graphInterpolationType, GraphKeyType t)
        {
            return states[state_id].get_value(graph_id, graphInterpolationType,
                t);
        }
    };
}