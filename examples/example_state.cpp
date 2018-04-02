#include <cstdio>
#include "state.hpp"

enum StateVariableLabel
{
    POSITION_X,
    POSITION_Y,
    POSITION_Z,
    MUNITIONS
};

int main()
{
    /*
        Create a state manager to manage all state.
        <stateID, stateVaiableLabel, timeType, valueType>
    */
    state_management::State<unsigned int, StateVariableLabel,
        unsigned long, float> state;

    /*
        Add a new block with the given id.
    */
    state.add_block(0u);

    /*
        Add a graph to the given state with given variable label.
    */
    state.add_graph(0u, StateVariableLabel::POSITION_Y);

    /*
        Add some keys to the graph.
    */
    state.add_key(0u, StateVariableLabel::POSITION_Y,
        50ul, 100.f);
    state.add_key(0u, StateVariableLabel::POSITION_Y,
        100ul, 150.f);
    state.add_key(0u, StateVariableLabel::POSITION_Y,
        40ul, 100.f);
    state.add_key(0u, StateVariableLabel::POSITION_Y,
        110ul, 100.f);

    /*
        Remove a range of keys (Inclusive)
    */
    state.remove_range(0u, StateVariableLabel::POSITION_Y,
        50ul, 100ul);

    /*
        Add 2 keys based on initial key and durational change.
    */
    //state.lerp_by_duration(0u,
    //    StateVariableLabel::POSITION_Y, 0ul, 100ul, 200.f);

    /*
        Get a value from given graph with given interpolation.
    */
    float value = state.get_value(0u,
        StateVariableLabel::POSITION_Y,
        state_management::GraphInterpolationType::LINEAR, 75ul);

    printf("Value: %.1f\n", value); // Prints Value: 125.0

    return 0;
}
