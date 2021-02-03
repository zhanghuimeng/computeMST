#include <cstring>
#include <fstream>

#include <GL/glut.h>

#include "Window.h"
#include "TestcaseGenerator.h"

cmst::Window* cmst::Window::m_instance = NULL;

void cmst::Window::draw()
{
    /*
    if (m_showVoronoi)
        m_curGraph->drawVoronoi();
    */
    if (m_showDelaunay)
        m_curGraph->drawDelaunay();

    if (m_showMST)
        m_curGraph->drawMST();

    if (m_showST)
        m_curGraph->drawST();

    if (m_showPoint)
        m_curGraph->drawPoint();
}

void cmst::Window::resetCurGraph(std::vector<Point2D>& points)
{
    if (m_curGraph != NULL)
    {
        if (!m_test.m_displayTest)
            delete m_curGraph;
        else
        {
            m_test.m_testGraphs.clear();
            m_test.m_displayTest = false;
        }
    }
    m_curGraph = NULL;
    m_curGraph = new Graph2D(points);
}

void cmst::Window::resetCurGraph()
{
    std::vector<cmst::Point2D> points(cmst::TestcaseGenerator());
    resetCurGraph(points);
}

void cmst::Window::resetCurGraph(int n)
{
    std::vector<cmst::Point2D> points(cmst::TestcaseGenerator(n, n));
    resetCurGraph(points);
}

void cmst::Window::resetCurGraph(int low, int hi)
{
    std::vector<cmst::Point2D> points(cmst::TestcaseGenerator(low, hi));
    resetCurGraph(points);
}

bool cmst::Window::load()
{
    std::string file;
    std::cin >> file;
    std::ifstream in(file.c_str());
    if (!in.is_open())
        return false;
    std::vector<cmst::Point2D> points;
    double x, y;
    while (in >> x >> y)
    {
        if (x < 0 || x > MAX_X) continue;
        if (y < 0 || y > MAX_Y) continue;
        points.push_back(cmst::Point2D(x, y));
    }

    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    if (points.size() > 10000)
    {
        std::cout << "Too many points, cannot compute" << std::endl;
        return false;
    }

    resetCurGraph(points);
    in.close();
    return true;
}

void cmst::Window::printCurInfo()
{
    std::cout << "\nCurrent tree displaying: " << std::endl;
    std::cout << "== Number of points: " << m_curGraph->pointNum() << std::endl;
    std::cout << "== Number of edges in the Delaunay Diagram: " << m_curGraph->edgeNum() << std::endl;
    std::cout << "== Length: " << m_curGraph->mstLength() << std::endl;
    std::cout << "== Delaunay Triangulation Compute Time: " << m_curGraph->delaunayTime()/1000.0 << std::endl;
    std::cout << "== Graph construct time: " << m_curGraph->graphConstructTime()/1000.0 << std::endl;
    std::cout << "== MST Compute Time: " << m_curGraph->mstTime()/1000.0 << std::endl;
}

void cmst::Window::printTestInfo()
{
    if (m_test.m_displayTest)
    {
        std::cout << "\nCurrent test displaying: " << std::endl;
        std::cout << "== Number of tests: " << m_test.m_testGraphs.size() << std::endl;
        std::cout << "== Delaunay Diagram compute time: " << std::endl;
        std::cout << m_test.m_delaunayTimeStat.print() << std::endl;
        std::cout << "== MST compute time: " << std::endl;
        std::cout << m_test.m_mstTimeStat.print() << std::endl;
    }
}

void cmst::Window::generateTest(int n)
{
    if (!m_test.m_displayTest)
    {
        m_test.m_displayTest = true;
        delete m_curGraph;
        m_curGraph = NULL;
    }
    else
    {
        m_curGraph = NULL;
        m_test.m_testGraphs.clear();
    }

    n = std::max(n, 1);
    m_test.m_displayTestNum = 0;
    std::vector<cmst::Point2D> points;
    for (int i = 0; i < n; i++)
    {
        points = cmst::TestcaseGenerator(10000, 10000);
        m_test.m_testGraphs.push_back(cmst::Graph2D(points));

        m_test.m_delaunayTimeStat.record(m_test.m_testGraphs[i].delaunayTime()/1000.0);
        m_test.m_graphConstructTimeStat.record(m_test.m_testGraphs[i].graphConstructTime()/1000.0);
        m_test.m_mstTimeStat.record(m_test.m_testGraphs[i].mstTime()/1000.0);
    }
    m_curGraph = &m_test.m_testGraphs[0];
}
