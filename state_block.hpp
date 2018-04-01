#pragma once
#include <unordered_map>
#include "state_graph.hpp"

namespace state_management
{
    template <typename GraphIDType, typename GraphKeyType,
        typename GraphValueType>
    class StateBlock
    {
    private:
        std::unordered_map<GraphIDType, StateGraph<GraphKeyType,
            GraphValueType>> state_graphs;

    public:
        /*
        Adds or replaces a state_graph to the state with the given id.
        */
        void add_graph(GraphIDType graph_id)
        {
            state_graphs[graph_id] = StateGraph<GraphKeyType, GraphValueType>();
        }

        /*
        Adds value at time t to given state_graph.
        */
        void add_key(GraphIDType graph_id, GraphKeyType t, GraphValueType v)
        {
            state_graphs[graph_id].add_key(t, v);
        }

        /*
        Removes a key at time t on the given state_graph.
        */
        void remove_key(GraphIDType graph_id, GraphKeyType t)
        {
            state_graphs[graph_id].remove_key();
        }

        /*
        Removes all keys in range (Inclusive).
        */
        void remove_range(GraphIDType graph_id, GraphKeyType from_t,
            GraphKeyType to_t)
        {
            state_graphs[graph_id].remove_range(from_t, to_t);
        }

        /*
            Gets value at time t from given state_graph with given
            interpolation.
        */
        GraphValueType get_value(GraphIDType graph_id,
            GraphInterpolationType graphInterpolationType, GraphKeyType t)
        {
            return state_graphs[graph_id].get_value(graphInterpolationType, t);
        }
    };
}

