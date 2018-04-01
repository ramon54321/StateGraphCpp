#pragma once
#include <unordered_map>
#include "state_block.hpp"

namespace state_management
{
    template <typename BlockIDType, typename GraphIDType,
        typename GraphKeyType, typename GraphValueType>
    class State
    {
    private:
        std::unordered_map<BlockIDType, StateBlock<GraphIDType,
            GraphKeyType, GraphValueType>> state_blocks;

    public:
        /*
            Adds or replaces a block to the manager with the given state_id.
        */
        void add_block(BlockIDType state_id)
        {
            state_blocks[state_id] = StateBlock<GraphIDType, GraphKeyType,
                GraphValueType>();
        }

        /*
            Removes a block from the manager by state_id.
        */
        void remove_block(BlockIDType state_id)
        {
            state_blocks.erase(state_id);
        }

        /*
            Adds or replaces a graph to the state with the given state_id.
        */
        void add_graph(BlockIDType state_id, GraphIDType graph_id)
        {
            state_blocks[state_id].add_graph(graph_id);
        }

        /*
            Adds value at time t to given graph in the given state.
        */
        void add_key(BlockIDType state_id, GraphIDType graph_id,
            GraphKeyType t, GraphValueType v)
        {
            state_blocks[state_id].add_key(graph_id, t, v);
        }

        /*
            Removes key at time t in the given graph in the given state.
        */
        void remove_key(BlockIDType state_id, GraphIDType graph_id,
            GraphKeyType t)
        {
            state_blocks[state_id].remove_key(graph_id, t);
        }

        /*
            Removes all keys in range (Inclusive).
        */
        void remove_range(BlockIDType state_id, GraphIDType graph_id,
            GraphKeyType from_t, GraphKeyType to_t)
        {
            state_blocks[state_id].remove_range(graph_id, from_t, to_t);
        }

        /*
            Gets value at time t from given graph with given interpolation.
        */
        GraphValueType get_value(BlockIDType state_id, GraphIDType graph_id,
            GraphInterpolationType graphInterpolationType, GraphKeyType t)
        {
            return state_blocks[state_id].get_value(graph_id,
                graphInterpolationType, t);
        }

        /*
            Adds keys with given change and after given duration.
        */
        void lerp_by_duration(BlockIDType state_id, GraphIDType graph_id,
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