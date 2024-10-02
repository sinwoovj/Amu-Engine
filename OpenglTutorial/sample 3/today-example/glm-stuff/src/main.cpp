/*!
@file    	main.cpp
@author  	pghali@digipen.edu
@co-author	parminder.singh@digipen.edu
@date    	31/03/2024

This file uses functionality defined in types GLHelper and GLApp to initialize
an OpenGL context and implement a game loop.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!
#include <glhelper.h>
#include <glapp.h>
#include <iostream>
#include <hook_csd2101.h>

/*                                                   type declarations
----------------------------------------------------------------------------- */

/*                                                      function declarations
----------------------------------------------------------------------------- */
static void draw();
static void update();
static void init(GLint width, GLint height, std::string title);
static void cleanup();

/*                                                      function definitions
----------------------------------------------------------------------------- */
/*  _________________________________________________________________________ */
/*! main

@param none

@return int

Indicates how the program existed. Normal exit is signaled by a return value of
0. Abnormal termination is signaled by a non-zero return value.
Note that the C++ compiler will insert a return 0 statement if one is missing.
*/
int main(int argc, char* argv[]) {
  // Part 1
  ParseArguments& args = ParseArguments::getInstance();
  if (!args.parseArguments(argc, argv)) return 0;

  // Part 2
  init(args.window_width, args.window_height, "Matrices in GLSL and GLM");

  AUTOMATION_HOOK_RENDER(args); // Automation hook. [!WARNING!] Do not alter/remove this!

  // Part 3
  while (!glfwWindowShouldClose(GLHelper::ptr_window)) {
    // Part 3a
    update();
    // Part 3b
    draw();
  }

  // Part 4
  cleanup();
}

/*  _________________________________________________________________________ */
/*! update
@param none
@return none

Uses GLHelper::GLFWWindow* to get handle to OpenGL context.
For now, there are no objects to animate nor keyboard, mouse button click,
mouse movement, and mouse scroller events to be processed.
*/
static void update() {
  // Part 1
  glfwPollEvents();

  // Part 2
  GLHelper::update_time(1.0);

  // Part 3
  GLApp::update();
}

/*  _________________________________________________________________________ */
/*! draw
@param none
@return none

Call application to draw and then swap front and back frame buffers ...
Uses GLHelper::GLFWWindow* to get handle to OpenGL context.
*/
static void draw() {
  // Part 1
  GLApp::draw();

  // Part 2: swap buffers: front <-> back
  glfwSwapBuffers(GLHelper::ptr_window);
}

/*  _________________________________________________________________________ */
/*! init
@param none
@return none

The OpenGL context initialization stuff is abstracted away in GLHelper::init.
The specific initialization of OpenGL state and geometry data is
abstracted away in GLApp::init
*/
static void init(GLint width, GLint height, std::string title) {
  // Part 1
  if (!GLHelper::init(width, height, title)) {
    std::cout << "Unable to create OpenGL context" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // Part 2
  GLHelper::print_specs();

  // Part 3
  GLApp::init();
}

/*  _________________________________________________________________________ */
/*! cleanup
@param none
@return none

Return allocated resources for window and OpenGL context thro GLFW back
to system.
Return graphics memory claimed through
*/
void cleanup() {
  // Part 1
  GLApp::cleanup();

  // Part 2
  GLHelper::cleanup();
}
