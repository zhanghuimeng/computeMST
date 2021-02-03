#pragma once

#ifdef FREEGLUT

#include <vector>
#include <GL/glut.h>

#include "Settings.h"
#include "Graph2D.h"
#include "Window.h"

/// The GLUT display function.
///
/// Draws the points, Delaunay edges, MST and so on.
void display();

/// The GLUT reshape function.
///
/// Sets the view port to the whole window and resets modelview matrix,
/// so that the graph is shown in the middle of the window.
void reshape(int width, int height);

/// The GLUT keyboard function.
///
/// - key 'Esc': exit the window
void processNormalKeys(unsigned char key, int x, int y);

/// The GLUT special keyboard function.
///
/// - Left arrow key: switch between test graphs
/// - Right arrow key: switch between test graphs
/// - Up arrow key: switch between spanning trees
/// - Down arrow key: switch between spanning trees
void processSpecialKeys(int key, int x, int y);

/// Initialize GLUT rendering.
///
/// - Smooth rendering for points and edges
/// Background color: light gray (0.9, 0.9, 0.9, 1)
void initRendering();

/// Create pop-up menus for the window
void createGLUTMenus();

/// Sub-menu 'New' process function
///
/// Provides ways of generating new graphs of
/// random numbers of points \n
/// The point numbers have these ranges to select from:
/// - [4, 10]
/// - (10, 100]
/// - (100, 1000]
/// - (1000, 5000]
/// - (5000, 10000]
void processNewMenu(int option);

/// Sub-menu 'Show' process function
///
/// Provides options of whether to display the Delaunay diagram
void processShowMenu(int option);

/// Sub-menu 'Test' process function
///
/// Provides options of running Tests of graphs.\n
/// Information of the test, like time statistics will be printed.\n
/// Graph size: 6000\n
/// Test size:\n
/// - 5
/// - 20
void processTestMenu(int option);

/// Main menu process function
/// Menu entries:
/// - Load: load a graph from file input. For input format, see src/example_input.txt.
/// - Generate: see processNewMenu(int option)
/// - Show: see processShowMenu(int option)
/// - Run Test: see processTestMenu(int option)
/// - Validate: Run a MST validate test. The algorithm is to generate all possible edges in a Eculidean graph, then run Kruskal's MST algorithm.
/// - Print: Print the current graph information to file.
/// - Quit: Quit the program.
void processMainMenu(int option);

#endif // FREEGLUT
