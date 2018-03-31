#pragma once
#include <unordered_map>
#include "graph.hpp"

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
        Gets value at time t from given graph with given interpolation.
    */
    GraphValueType get_value(IDType graph_id,
        GraphInterpolationType graphInterpolationType, GraphKeyType t)
    {
        return graphs[graph_id].get_value(graphInterpolationType, t);
    }
};

