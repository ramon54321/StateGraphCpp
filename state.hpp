#pragma once
#include <unordered_map>
#include "graph.hpp"

namespace state_management
{
    template <typename IDType, typename GraphKeyType, typename GraphValueType>
    class State
    {
    private:
        std::unordered_map<IDType, Graph<GraphKeyType, GraphValueType>> graphs;

    public:
        /*
        Adds or replaces a graph to the state with the given id.
        */
        void add_graph(IDType graph_id)
        {
            graphs[graph_id] = Graph<GraphKeyType, GraphValueType>();
        }

        /*
        Adds value at time t to given graph.
        */
        void add_key(IDType graph_id, GraphKeyType t, GraphValueType v)
        {
            graphs[graph_id].add_key(t, v);
        }

        /*
        Removes a key at time t on the given graph.
        */
        void remove_key(IDType graph_id, GraphKeyType t)
        {
            graphs[graph_id].remove_key();
        }

        /*
        Removes all keys in range (Inclusive).
        */
        void remove_range(IDType graph_id, GraphKeyType from_t,
            GraphKeyType to_t)
        {
            graphs[graph_id].remove_range(from_t, to_t);
        }

        /*
            Gets value at time t from given graph with given interpolation.
        */
        GraphValueType get_value(IDType graph_id,
            GraphInterpolationType graphInterpolationType, GraphKeyType t)
        {
            return graphs[graph_id].get_value(graphInterpolationType, t);
        }
    };
}

