#include <ctime>

namespace cmst
{
    /// A class for timing.
    ///
    /// Uses simple clock() function.
    class Timer
    {
    public:
        /// Constructor. Begin the timer.
        Timer() { m_begin = std::clock(); }

        /// Return the time since construction or reset.
        ///
        /// The time unit is ms.
        int time() { return std::clock() - m_begin; }

        /// Reset the timer.
        void reset() { m_begin = std::clock(); }

    private:
        int m_begin; ///< The time at construction or reset.
    };
}
