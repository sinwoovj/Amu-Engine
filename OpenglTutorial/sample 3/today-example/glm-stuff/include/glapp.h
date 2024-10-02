/* !
@file    	glapp.h
@author  	pghali@digipen.edu
@coauthor	parminder.singh@digipen.edu
@date    	31/03/2024

This file contains the declaration of namespace GLApp that encapsulates the
functionality required to implement an OpenGL application including 
compiling, linking, and validating shader programs
setting up geometry and index buffers, 
configuring VAO to present the buffered geometry and index data to
vertex shaders,
configuring textures (in later labs),
configuring cameras (in later labs), 
and transformations (in later labs).
*//*__________________________________________________________________________*/

/*                                                                      guard
----------------------------------------------------------------------------- */
#ifndef GLAPP_H
#define GLAPP_H
#include <glhelper.h>
#include <glslshader.h>

/*                                                                   includes
----------------------------------------------------------------------------- */

struct GLApp {
  static void init();
  static void update();
  static void draw();
  static void cleanup();

  // encapsulates state required to render a geometrical model
  struct GLModel {
      GLenum     primitive_type; // which OpenGL primitive to be rendered?
      GLSLShader shdr_pgm;       // which shader program?
      GLuint     vaoid;          // handle to VAO
      GLuint     vbo_hdl;        // handle to VBO
      GLuint     idx_elem_cnt;   // how many elements of primitive_type
      // are to be rendered?
      
      glm::mat4 transform_matrix;

      // member functions defined in glapp.cpp
      void setup_vao();
      void setup_shdrpgm();
      void draw();
  };

  // Matrices
  static void matrix_intro();
  static void matrix_initialization();
  static void print_matrix(const glm::mat4& matrix);

  // Transformation
  static glm::mat4x4 scale();
  static glm::mat4x4 translate();
  static glm::mat4x4 rotate();
  static glm::mat4x4 ortho();

  // data member to represent geometric model to be rendered
  // C++ requires this object to have a definition in glapp.cpp!!!
  static GLModel mdl;
};

#endif /* GLAPP_H */
