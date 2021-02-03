#pragma once

#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include "Settings.h"
#include "IndexEdge2D.h"
#include "Timer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;

namespace cmst
{
    class Graph2D
    {
    public:

        /// Constructor which does everything.
        ///
        /// - Compute Delaunay graph
        /// - Reconstruct the graph
        Graph2D(std::vector<Point2D>& points);

        /// The Kruskal algorithm for finding the minimal spanning tree.
        ///
        /// Use the CGAL computed Delaunay Diagram.
        /// \return The length of the MST.
        double Kruskal();

        /// The naive Kruskal algorithm.
        ///
        /// Construct all the edges in the graph, then run Kruskal.
        /// \return The length of the MST.
        double naiveKruskal();

        /// Use GLUT to draw the points in the graph.
        void drawPoint();

        /// Use GLUT to draw the Delaunay Diagram of the graph.
        void drawDelaunay();

        // void drawVoronoi();

        /// Use GLUT to draw the MST computed by Kruskal().
        void drawMST();

        /// Use GLUT to draw the ST computed by naiveKruskal().
        void drawST();

        /// Print the graph information to file.
        bool print(std::string file = "graph.txt");

        /// Change the displaying spanning tree
        ///
        /// To-do: calculate the top k spanning trees
        void changeSTDisplay(int direc)
        {
            if (m_ST.size() == 0) return;
            else if (m_displaySTNum == -1)
            {
                m_displaySTNum = 0;
                return;
            }
            if (direc < 0 && m_displaySTNum > 0)
                m_displaySTNum--;
            else if (direc > 0 && m_displaySTNum < m_ST.size()-1)
                m_displaySTNum++;
        }

        /// Print the information of the current spanning tree displayed
        void printSTInfo()
        {
            if (m_displaySTNum != -1)
            {
                std::cout << "\nCurrent MST(naive) displaying: " << m_displaySTNum << " th" << std::endl;
                std::cout << "== Number of edges: " << m_ST[m_displaySTNum].m_edges.size() << std::endl;
                std::cout << "== Length: " << m_ST[m_displaySTNum].m_length << std::endl;
                // std::cout << "== Delaunay Triangulation Compute Time: " << m_curGraph->delaunayTime()/1000.0 << std::endl;
                // std::cout << "== Graph construct time: " << m_curGraph->graphConstructTime()/1000.0 << std::endl;
                std::cout << "== MST Compute Time: " << m_ST[m_displaySTNum].m_stTime/1000.0 << std::endl;
                if (std::abs(m_ST[m_displaySTNum].m_length - m_mstLength) < EPS_MIN)
                    std::cout << "Correct MST!" << std::endl;
                else
                    std::cout << "Failed!" << std::endl;
            }
        }

        /// Return the length of the MST
        /// \return Length of MST
        double mstLength()
        {
            if (!m_mstDone)
                Kruskal();
            return m_mstLength;
        }

        /// Return the time used for computing Delaunay diagram
        int delaunayTime() const { return m_delaunayTime; }

        /// Return the time used for computing MST,
        /// using Kruskal's algorithm
        int mstTime()
        {
            if (!m_mstDone)
                Kruskal();
            return m_mstTime;
        }

        /// Return the time used for reconstructing the graph.
        ///
        /// When using CGAL library, the internal data structure is different from the one used in this program.
        /// So you need some conversion.
        int graphConstructTime() const { return m_graphConstructTime; }

        /// Return the number of points in this graph.
        int pointNum() const { return m_points.size(); }

        /// Return the number of edges in the Delaunay diagram.
        int edgeNum() const { return m_delaunayEdge.size(); }

        /// Return if the MST has been validated
        bool validateDone() const { return m_validateDone; }


    protected:

        /// Father array for Union-find Sets structure
        std::vector<int> father;

        /// Find the father of x in the Union-find Sets structure
        int findFather(int x);

        /// Initializes the father array for Union-find Sets structure
        void initFather();

        std::vector<Point2D> m_points; ///< Points in the graph.
        std::vector<IndexEdge2D> m_delaunayEdge; ///< Delaunay edges of the graph.

        std::vector<IndexEdge2D> m_MSTEdge; ///< MST edges of the graph.

        std::vector<IndexEdge2D> m_edges; ///< All possible edges in the graph.
        // std::vector<CGAL::Object> m_voronoiEdge; ///
        std::vector<std::vector<int>> m_graph; ///< Adjacency list of the Delaunay diagram of the graph.
        Delaunay m_delaunay; ///< CGAL data structure for storing and computing a Delaunay diagram.

        /// Store a spanning tree of the graph.
        struct ST
        {
            std::vector<IndexEdge2D> m_edges; ///< Edges of the spanning tree.
            int m_stTime; ///< Time used to compute the spanning tree.
            double m_length; ///< Length of the spanning tree.

            /// Constructor
            ST(std::vector<IndexEdge2D> edges = std::vector<IndexEdge2D>(), int stTime = 0, double length = 0.0) :
                m_edges(edges), m_stTime(stTime), m_length(length) {}
        };
        std::vector<ST> m_ST; ///< Spanning trees of the graph.

    private:

        bool m_mstDone; ///< If Kruskal() has been called.
        bool m_validateDone; ///< If naiveKruskal() has been called.

        double m_mstLength; ///< Length of the MST.

        int m_delaunayTime; ///< Time used for computing the Delaunay diagram.
        int m_mstTime; ///< Time used for computing the MST.
        int m_graphConstructTime; ///< Time used for reconstructing the graph.
        // int m_kMSTTime;

        int m_displaySTNum; /// The number of the ST that is being displayed.
    };
}
