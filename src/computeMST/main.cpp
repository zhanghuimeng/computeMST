#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <iomanip>

#include "Graph2D.h"
#include "TestcaseGenerator.h"
#include "Settings.h"
#include "Window.h"

#ifdef FREEGLUT
#include <GL/glut.h>
#include "GlutFunctions.h"
// #include <windows.h>
#endif // FREEGLUT

std::stringstream debugout;

void Initialize()
{

}

void CleanUp()
{
    #ifdef DEBUG
    // Write to log
    std::ofstream logout("log.txt");
    logout << debugout.str();
    logout.close();
    #endif // DEBUG

}

int main(int argc, char** argv)
{
    Initialize();
    std::cout << std::fixed << std::setprecision(4);

    cmst::Window::instance()->resetCurGraph(0);

    #ifdef FREEGLUT

    glutInit( &argc, argv );
    glutInitDisplayMode ( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowSize ( 800, 600 );
    glutInitWindowPosition ( 0, 0 );
    glutCreateWindow ( "Compute MST" );

    createGLUTMenus();
    initRendering();

    glutDisplayFunc(display);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);   // 这个必须有
    glutMainLoop();

    #endif // FREEGLUT

    CleanUp();

	return 0;
}
