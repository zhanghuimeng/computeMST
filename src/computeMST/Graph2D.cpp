#include "Graph2D.h"
#include <GL/glut.h>
#include <queue>
#include <fstream>
#include <algorithm>
#include <cstring>

cmst::Graph2D::Graph2D(std::vector<cmst::Point2D>& points) : m_points(points),
    m_mstDone(false), m_validateDone(false), m_displaySTNum(-1)
{
    int n = m_points.size();
    m_graph.assign(n, std::vector<int>());
    m_ST.push_back(ST());

    cmst::Timer timer;

    #ifdef DEBUG
    debugout << "Constructing a graph of size " << n << std::endl;
    #endif // DEBUG

    // Construct the Delaunay data structure
    std::vector<K::Point_2> vertices;
    for (int i = 0; i < n; i++)
        vertices.push_back( K::Point_2(points[i].x(), points[i].y()) );
    m_delaunay.insert(vertices.begin(), vertices.end());

    m_delaunayTime = timer.time();
    timer.reset();

    // Store the Voronoi graph
    // This consumes too much time, so is abandoned.
    /*
    Delaunay::Edge_iterator eit;
    for (eit = m_delaunay.edges_begin(); eit != m_delaunay.edges_end(); eit++)
    {
        CGAL::Object o = m_delaunay.dual(eit);//边eit在其对偶图中所对应的边
        m_voronoiEdge.push_back(o);
    }

    std::cout << timer.time() << std::endl;
    */

    // Reconstruct my graph
    std::sort(m_points.begin(), m_points.end());
    Delaunay::Finite_faces_iterator fit;
    for (fit = m_delaunay.finite_faces_begin(); fit != m_delaunay.finite_faces_end(); fit++)
    {
        for (int i = 0; i <= 2; i++)
        {
            cmst::Point2D start( fit->vertex(i)->point().hx(), fit->vertex(i)->point().hy() );
            cmst::Point2D end( fit->vertex((i+1)%3)->point().hx(), fit->vertex((i+1)%3)->point().hy() );

            int index1 = std::lower_bound(m_points.begin(), m_points.end(), start) - m_points.begin();
            int index2 = std::lower_bound(m_points.begin(), m_points.end(), end) - m_points.begin();
            m_delaunayEdge.push_back( cmst::IndexEdge2D(start, end, index1, index2) );
        }
    }

    m_graphConstructTime = timer.time();
    timer.reset();

    int m = m_delaunayEdge.size();
    std::sort(m_delaunayEdge.begin(), m_delaunayEdge.end());
    m_delaunayEdge.erase( std::unique(m_delaunayEdge.begin(), m_delaunayEdge.end()), m_delaunayEdge.end() );
    Kruskal();
    m_mstTime = timer.time();

    for (int i = 0; i < m; i++)
    {
        m_graph[m_delaunayEdge[i].startIndex()].push_back( m_delaunayEdge[i].endIndex() );
        m_graph[m_delaunayEdge[i].endIndex()].push_back( m_delaunayEdge[i].startIndex() );
    }
}

double cmst::Graph2D::Kruskal()
{
    m_MSTEdge.clear();
    std::sort(m_delaunayEdge.begin(), m_delaunayEdge.end());
    cmst::Graph2D::initFather();

    double mstLength = 0.0f;


    int m = m_delaunayEdge.size();
    for (int i = 0; i < m; i++)
    {
        int fa1 = cmst::Graph2D::findFather(m_delaunayEdge[i].startIndex());
        int fa2 = cmst::Graph2D::findFather(m_delaunayEdge[i].endIndex());
        if (fa1 != fa2)
        {
            father[fa1] = fa2;
            m_MSTEdge.push_back(m_delaunayEdge[i]);
            mstLength += m_delaunayEdge[i].length();
        }
    }


    m_mstLength = mstLength;
    m_mstDone = true;

    return mstLength;
}

double cmst::Graph2D::naiveKruskal()
{
    int n = m_points.size();
    std::vector<cmst::IndexEdge2D> edges;
    double mstLength = 0.0;
    Timer timer;

    // Construct all edges
    if (m_edges.empty())
    {
        m_edges.reserve(n * (n-1) / 2);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                m_edges.push_back( IndexEdge2D(m_points[i], m_points[j], i, j) );
        std::sort(m_edges.begin(), m_edges.end());
    }

    cmst::Graph2D::initFather();

    int m = m_edges.size();
    for (int i = 0; i < m; i++)
    {
        int fa1 = cmst::Graph2D::findFather(m_edges[i].startIndex());
        int fa2 = cmst::Graph2D::findFather(m_edges[i].endIndex());
        if (fa1 != fa2)
        {
            father[fa1] = fa2;
            edges.push_back(m_edges[i]);
            mstLength += m_edges[i].length();
        }
    }

    m_ST.push_back(ST(edges, timer.time(), mstLength));
    m_validateDone = true;
    if (m_displaySTNum == -1)
        m_displaySTNum = m_ST.size() - 1;

    return mstLength;
}

int cmst::Graph2D::findFather(int x)
{
    if (father[x] == x) return x;
    return father[x] = findFather(father[x]);
}

void cmst::Graph2D::initFather()
{
    father.clear();
    int n = m_points.size();
    for (int i = 0; i < n; i++)
        father.push_back(i);
}

void cmst::Graph2D::drawPoint()
{
    glPointSize( 4.0f );   // 绘制前设置下点的大小和颜色
    glColor3f( 0, 0, 0 );

    glBegin( GL_POINTS );
    //glVertex3f( 56, 87, 0 );
    for (int i = 0; i < m_points.size(); i++)
        glVertex2f(m_points[i].x(), m_points[i].y());
    glEnd();
}

void cmst::Graph2D::drawDelaunay()
{
    glColor3f( 0, 0, 1 );
    // glColor3f( 1, 0, 0 );
    glLineWidth(1);
    glBegin(GL_LINES);
    for (int i = 0; i < m_delaunayEdge.size(); i++)
    {
        glVertex3f(m_delaunayEdge[i].start().x(), m_delaunayEdge[i].start().y(), 0);
        glVertex3f(m_delaunayEdge[i].end().x(), m_delaunayEdge[i].end().y(), 0);
    }
    glEnd();
}

void cmst::Graph2D::drawMST()
{
    // Draw the Delaunay MST
    glColor3f( 245/255.0, 92/255.0, 229/255.0 );
    // glColor3f(1, 1, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    for (int i = 0; i < m_MSTEdge.size(); i++)
    {
        glVertex2f(m_MSTEdge[i].start().x(), m_MSTEdge[i].start().y());
        glVertex2f(m_MSTEdge[i].end().x(), m_MSTEdge[i].end().y());
    }
    glEnd();
}

void cmst::Graph2D::drawST()
{
    // Draw the test MST
    if (m_ST.size() > 0 && m_displaySTNum != -1)
    {
        glEnable( GL_LINE_STIPPLE );
        glLineWidth(1);
        glLineStipple(1, 0x3333);
        glColor3f(52/255.0, 197/255.0, 18/255.0);
        glBegin(GL_LINES);
        for (int i = 0; i < m_ST[m_displaySTNum].m_edges.size(); i++)
        {
            cmst::IndexEdge2D& e = m_ST[m_displaySTNum].m_edges[i];
            glVertex2f(e.start().x(), e.start().y());
            glVertex2f(e.end().x(), e.end().y());
        }
        glEnd();
        glDisable( GL_LINE_STIPPLE );
    }
}

bool cmst::Graph2D::print(std::string file/* = "graph.txt"*/)
{
    std::ofstream out(file.c_str());
    if (!out.is_open())
        return false;
    out << "Graph information: " << std::endl;
    out << "Points: " << std::endl;
    for (int i = 0; i < m_points.size(); i++)
        out << "= " << m_points[i] << std::endl;

    out << "\nDelaunay Edges:" << std::endl;
    for (int i = 0; i < m_delaunayEdge.size(); i++)
        out << "= " << m_delaunayEdge[i] << std::endl;

    if (m_mstDone)
    {
        out << "\nMST calculated: " << std::endl;
        out << "Length: " << m_mstLength << std::endl;
        out << "MST edges: " << std::endl;
        for (int i = 0; i < m_MSTEdge.size(); i++)
            out << "= " << m_MSTEdge[i] << std::endl;
    }
    else
        out << "\nMST not done" << std::endl;

    out.close();
    return true;
}

/*
void cmst::Graph2D::drawVoronoi()
{
    Delaunay::Edge_iterator eit;//遍历Delaunay的所有边，绘制Delaunay图的对偶图，即Voronoi图

    glEnable( GL_LINE_STIPPLE );//使用点画模式，即使用虚线来绘制Voronoi图
    glLineWidth(1);
    glLineStipple(1, 0x3333);
    glColor3f(52/255.0, 197/255.0, 18/255.0);

    for (int i = 0; i < m_voronoiEdge.size(); i++)
    {
        CGAL::Object o = m_voronoiEdge[i];

        if (CGAL::object_cast<K::Segment_2>(&o)) //如果这条边是线段，则绘制线段
        {
            glBegin(GL_LINES);
            glVertex2i( CGAL::object_cast<K::Segment_2>(&o)->source().hx(), CGAL::object_cast<K::Segment_2>(&o)->source().hy() );
            glVertex2i( CGAL::object_cast<K::Segment_2>(&o)->target().hx(), CGAL::object_cast<K::Segment_2>(&o)->target().hy() );
            glEnd();
        }
        else if (CGAL::object_cast<K::Ray_2>(&o))//如果这条边是射线，则绘制射线
        {
            glBegin(GL_LINES);
            glVertex2i( CGAL::object_cast<K::Ray_2>(&o)->source().hx(), CGAL::object_cast<K::Ray_2>(&o)->source().hy() );
            glVertex2i( CGAL::object_cast<K::Ray_2>(&o)->point(1).hx(), CGAL::object_cast<K::Ray_2>(&o)->point(1).hy() );
            glEnd();
        }
    }
    glDisable( GL_LINE_STIPPLE );//关闭点画模式
}
*/
