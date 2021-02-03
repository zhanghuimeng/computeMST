#include <vector>
#include <limits>
#include <string>
#include <sstream>

namespace cmst
{
    /// Simple statistics.
    ///
    /// Including:
    /// - Minimum
    /// - Maximum
    /// - Mean
    /// - Standard Deviation
    class Stat
    {
    public:
        /// Constructor
        ///
        /// Set m_max to DOUBLE_MIN and m_min to DOUBLE_MAX
        Stat() : m_min(std::numeric_limits<double>::max()), m_max(std::numeric_limits<double>::min()) {}

        /// Record a datum and update m_min, m_max
        void record(double data)
        {
            m_data.push_back(data);
            m_min = std::min(m_min, data);
            m_max = std::max(m_max, data);
        }

        /// Return the minimum of recorded data.
        /// \return Minimum of recorded data
        /// \retval 0.0 If no data has been recorded
        double min() const { return m_data.size() > 0 ? m_min : 0.0; }

        /// Return the maximum of recorded data.
        /// \return Maximum of recorded data
        /// \retval 0.0 If no data has been recorded
        double max() const { return m_data.size() > 0 ? m_max : 0.0; }

        /// Return the number of recorded data.
        /// \return The number of recorded data
        /// \retval 0 If no data has been recorded.
        int count() const { return m_data.size(); }

        /// Return the mean of all data.
        /// \return Mean of all data
        /// \retval 0.0 If no data has been recorded.
        double mean()
        {
            int n = m_data.size();
            m_mean = 0.0;
            for (int i = 0; i < n; i++)
                m_mean += m_data[i];
            return m_mean = m_mean / n;
        }

        /// Return the standard deviation of all data.
        /// \return Standard deviation of all data
        /// \retval 0.0 If no data has been recorded.
        double standardDeviation()
        {
            mean();
            m_standardDeviation = 0.0;
            int n = m_data.size();
            for (int i = 0; i < n; i++)
                m_standardDeviation += (m_data[i] - m_mean) * (m_data[i] - m_mean);
            return m_standardDeviation = std::sqrt(m_standardDeviation);
        }

        /// Print the information of the statistic.
        ///
        /// - Average
        /// - Maximum
        /// - Minimum
        /// - Standard deviation
        std::string print()
        {
            std::stringstream str;
            mean();
            standardDeviation();
            str << "*** Average: " << m_min << std::endl;
            str << "*** Maximum: " << m_max << std::endl;
            str << "*** Minimum: " << m_min << std::endl;
            str << "*** Standard Deviation: " << m_standardDeviation;

            return str.str();
        }

    private:

        double m_min; ///< Minimum of the data.
        double m_max; ///< Maximum of the data.
        double m_mean; ///< Average of the data.
        double m_standardDeviation; ///< Standard deviation of the data.
        std::vector<double> m_data; ///< Data.
    };
}
