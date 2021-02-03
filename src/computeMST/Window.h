#pragma once

#include "Graph2D.h"
#include "Stat.h"

namespace cmst
{
    /// Return values for GLUT menus
    enum Menu
    {
        LOAD,
        NEW,
        NEW_4_10,
        NEW_11_100,
        NEW_101_1000,
        NEW_1001_5000,
        NEW_5001_10000,
        SHOW,
        SHOW_VORONOI,
        SHOW_DELAUNAY,
        SHOW_POINT,
        SHOW_MST,
        SHOW_ST,
        TEST,
        TEST_5,
        TEST_20,
        VALIDATOR,
        PRINT,
        QUIT,
    };

    /// Manipulates the window.
    ///
    /// Uses Singleton pattern.
    class Window
    {
        public:

            /// Return the pointer to the instance of cmst::Window class.
            ///
            /// \return the pointer to the instance
            static Window* instance()
            {
                if (m_instance == NULL)
                    m_instance = new Window();
                return m_instance;
            }

            /// Returns a pointer to the graph in display currently.
            Graph2D* curGraph() { return m_curGraph; }

            /// Reset the current graph with a vector of points.
            /// \param points A vector of points.
            void resetCurGraph(std::vector<Point2D>& points);

            /// Reset the current graph with cmst::TestcaseGenerator
            ///
            /// The size of the graph is defaulted.
            void resetCurGraph();

            /// Reset the current graph with n random generated points.
            ///
            /// \param n The size of the graph to be generated.
            void resetCurGraph(int n);

            /// Reset the current graph with random generated points.
            ///
            /// The size of the graph to be generated is randomly selected
            /// between low and hi.
            /// \param low The least number of points to be generated.
            /// \param hi The most number of points to be generated.
            void resetCurGraph(int low, int hi);

            bool load();

            // void resetShowVoronoi() { m_showVoronoi = !m_showVoronoi; }

            /// Change whether the Delaunay diagram is to be drawn to the GLUT window.
            void resetShowDelaunay() { m_showDelaunay = !m_showDelaunay; }

            /// Change whether the points are to be drawn to the GLUT window.
            void resetShowPoint() { m_showPoint = !m_showPoint; }

            /// Change whether the MST is to be drawn to the GLUT window.
            void resetShowMST() { m_showMST = !m_showMST; }

            /// Change whether the STs are to be drawn to the GLUT window.
            void resetShowST() { m_showST = !m_showST; }

            /// Record the width of current GLUT window.
            void resetWidth(int width) { m_width = width; }

            /// Record the height of current GLUT window.
            void resetHeight(int height) { m_height = height; }

            /// Return the width of current GLUT window.
            ///
            /// \return The width of current GLUT window
            int width() const { return m_width; }

            /// Return the height of current GLUT window.
            ///
            /// \return The height of current GLUT window
            int height() const { return m_height; }

            /// Draws the current graph
            ///
            /// - Points: definitely
            /// - Delaunay Diagram: change whether to draw it by Window::resetShowDelaunay()
            /// - MST: definitely
            /// - Other spanning trees: draws one of them
            void draw();

            /// Prints information about the current displayed graph to console
            ///
            /// Information including numbers and computational time
            void printCurInfo();

            /// Returns if a test has been generated
            ///
            /// \return If a test has been generated
            bool displayTest() const { return m_test.m_displayTest; }

            /// Generates a test of n graphs and display the first one.
            ///
            /// \param n The number of graphs in the test to be generated
            void generateTest(int n);

            /// Prints information about the test that has been generated to console.
            ///
            /// If no test has been generated, then nothing is printed.
            void printTestInfo();

            /// Returns the number of graphs in the test that has been generated.
            /// \return the number of graphs in the test that has been generated.
            /// \retval 0 If no test has been generated.
            int testDisplayNum() const { return m_test.m_displayTestNum; }

            /// If a test is being displayed, then changes the graph
            /// in the test that is being displayed.
            ///
            /// If no test has been generated, does nothing.
            /// \param direc If negative, display the last graph (if there is one);
            /// if positive, display the next graph (if there is one).
            void changeTestDisplay(int direc)
            {
                if (m_test.m_displayTest)
                {
                    if (direc < 0 && m_test.m_displayTestNum > 0)
                    {
                        m_test.m_displayTestNum--;
                        m_curGraph = &m_test.m_testGraphs[m_test.m_displayTestNum];
                    }
                    else if (direc > 0 && m_test.m_displayTestNum < m_test.m_testGraphs.size()-1)
                    {
                        m_test.m_displayTestNum++;
                        m_curGraph = &m_test.m_testGraphs[m_test.m_displayTestNum];
                    }
                }
            }

            /// Print the information of the current graph to file graph.txt.
            bool printToFile()
            {
                return m_curGraph->print();
            }

            /// Change the MST that is being displayed.
            void changeMSTDisplay(int direc)
            {
                m_curGraph->changeSTDisplay(direc);
            }

            /// Print information of the current ST to console.
            void printSTInfo()
            {
                m_curGraph->printSTInfo();
            }

            /// Run the validator for small graphs.
            void runValidate()
            {
                if (m_curGraph->pointNum() > 5000)
                {
                    std::cout << "\nGraph too big, cannot run validate" << std::endl;
                    return;
                }
                if (!m_curGraph->validateDone())
                {
                    std::cout << "Running..." << std::endl;
                    m_curGraph->naiveKruskal();
                }
            }

        protected:

            /// Stores information of a test.
            ///
            /// Including the generated graphs and statistics of times.
            struct Test
            {
                bool m_displayTest; ///< Whether a test has been generated and displayed.

                int m_displayTestNum; ///< The number of graphs in the test.

                std::vector<Graph2D> m_testGraphs; ///< The graphs generated in the test.

                Stat m_delaunayTimeStat; ///< Statistics of Delaunay Diagram computational time.

                Stat m_graphConstructTimeStat; ///< Statistics of graph re-construction time.

                Stat m_mstTimeStat; ///< Statistics of MST computational time.

                /// Constructor
                ///
                /// No test is generated in initialization.
                Test() : m_displayTest(false), m_displayTestNum(0) {}
            } m_test; ///< The test.

        private:

            /// Constructor
            Window() : m_curGraph(NULL), m_showPoint(true), m_showDelaunay(true), m_showMST(true),
                m_showST(true), m_width(0), m_height(0) {}

            static Window* m_instance; ///< The pointer to an instance of cmst::Window.

            Window(const Window&); ///< Private copy-constructor.

            Graph2D* m_curGraph; ///< The pointer to the graph that is being displayed.

            // bool m_showVoronoi;

            bool m_showDelaunay; ///< Whether the Delaunay iagram is to be drawn.
            bool m_showMST; ///< Whether the MST is to be drawn.
            bool m_showST; ///< Whether the MST is to be drawn.
            bool m_showPoint; ///< Whether the points are to be drawn.

            int m_width; ///< The width of current GLUT window.
            int m_height; ///< The height of current GLUT window.
    };

}
