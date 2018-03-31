#include <cstdio>
#include "state_manager.hpp"

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
    StateManager<unsigned int, StateVariableLabel,
        unsigned long, float> state_manager;

    /*
        Add a new state with the given id.
    */
    state_manager.add_state(0u);

    /*
        Add a graph to the given state with given variable label.
    */
    state_manager.add_graph(0u, StateVariableLabel::POSITION_Y);

    /*
        Add some keys to the graph.
    */
    state_manager.add_key(0u, StateVariableLabel::POSITION_Y, 50ul, 100.f);
    state_manager.add_key(0u, StateVariableLabel::POSITION_Y, 100ul, 150.f);

    /*
        Get a value from given graph with given interpolation.
    */
    float value = state_manager.get_value(0u, StateVariableLabel::POSITION_Y,
        GraphInterpolationType::LINEAR, 75ul);

    printf("Value: %.1f\n", value); // Prints Value: 125.0

    return 0;
}
