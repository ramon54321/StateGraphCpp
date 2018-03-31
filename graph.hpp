#pragma once
#include <map>

namespace state_management
{
    /*
        Enum containing options for interpolation when retrieving value
        from graph.
    */
    enum GraphInterpolationType
    {
        STEP,
        LINEAR
    };

    template <typename TimeType, typename ValueType>
    class Graph
    {
    private:
        std::map<TimeType, ValueType> values;

    public:
        /*
        Constructor checks constraints for graph key and value.
        */
        Graph()
        {
            static_assert(std::is_integral<TimeType>::value 
                    || std::is_floating_point<TimeType>::value
                    , "Key needs to be an integral or float.");
            static_assert(std::is_integral<ValueType>::value 
                    || std::is_floating_point<ValueType>::value
                    , "Value needs to be an integral or float.");
        }

        /*
        Adds value at time t.
        */
        void add_key(TimeType t, ValueType v)
        {
            values[t] = v;
        }

        /*
        Removes key at time t.
        */
        void remove_key(TimeType t)
        {
            values.erase(t);
        }

        /*
        Removes all keys in range (Inclusive).
        */
        void remove_range(TimeType from_t, TimeType to_t)
        {
            auto searchStart = values.lower_bound(from_t);
            auto searchEnd = values.lower_bound(to_t);

            // -- If no keyframes
            if (searchStart == values.end())
                return;

            // -- For each keyframe between iterators
            while (true)
            {
                // -- Get key of iterator
                ValueType keyframeTime = searchStart->first;

                /*
                    If iterator points to value over t -> return
                    This can happen if both lower and upper is under
                    closest key
                */
                if (keyframeTime > to_t)
                    return;

                // -- Remove key
                this->remove_key(keyframeTime);
                
                // -- Break from loop once last key is reached
                if (searchStart == searchEnd)
                    return;

                // -- Advance iterator twice to compensate for removed key
                ++searchStart;
                ++searchStart;
            }
        }

        /*
            Get value from graph given t, using the given interpolation option.
        */
        ValueType get_value(GraphInterpolationType graphInterpolationType,
            TimeType t) const
        {
            // -- Iterator pointing to closest >= t
            auto search = values.lower_bound(t);

            // -- If exact key -> Return it
            if (search->first == t)
                return search->second;

            // -- If first keyframe -> Return it
            if (search == values.begin())
                return search->second;
                
            // -- If last keyframe -> Return previous
            if (search == values.end())
                return (--search)->second;

            // -- Interpolation options
            switch (graphInterpolationType)
            {
                // -- Step -> Return closest key to left of t
                case GraphInterpolationType::STEP:
                    --search;
                    return search->second;
                /*
                    Linear interpolation -> Return linearly interpolated value
                    for t
                */
                case GraphInterpolationType::LINEAR:
                    TimeType x1 = search->first;
                    ValueType y1 = search->second;
                    --search;
                    TimeType x0 = search->first;
                    ValueType y0 = search->second;

                    return y0 + (t - x0)*((y1 - y0) / (ValueType)(x1 - x0));
            }
        }
    };
}
