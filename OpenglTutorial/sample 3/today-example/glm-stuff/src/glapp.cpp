/*!
@file       glapp.cpp
@author  	pghali@digipen.edu
@co-author	parminder.singh@digipen.edu
@date    	31/03/2024

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <glapp.h>
#include <sstream>
#include <iomanip>
#include <glm/glm.hpp>
#include <array>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

/*                                                   objects with file scope
----------------------------------------------------------------------------- */
GLApp::GLModel GLApp::mdl;
const std::string my_tutorial_1_vs = {
  #include "my-tutorial-1.vert"
};

const std::string my_tutorial_1_fs = {
  #include "my-tutorial-1.frag"
};

void GLApp::init() {
    // Part 1: clear colorbuffer with RGBA value in glClearColor ...
    glClearColor(0.5f, 0.5f, 0.f, 1.f);

    // Part 2: use entire window as viewport ...
    glViewport(0, 0, GLHelper::width, GLHelper::height);

    // Part 3: initialize VAO and create shader program
    mdl.setup_vao();
    mdl.setup_shdrpgm();

#if 0
    matrix_intro(); // 1
    matrix_initialization(); // 2
#endif
}

void GLApp::draw() {
  // clear back buffer as before
  glClear(GL_COLOR_BUFFER_BIT);

  // now, render rectangular model from NDC coordinates to viewport
  mdl.draw();
}

void GLApp::cleanup() {
  // empty for now
}

void GLApp::update() {
  // Task: Printing to Window's Title Bar
  std::stringstream sstr;
  sstr << std::fixed << std::setprecision(2) << GLHelper::title << " | " << "Prasanna Ghali" << " | " << GLHelper::fps;
  // write window title with current fps ...
  glfwSetWindowTitle(GLHelper::ptr_window, sstr.str().c_str());

  mdl.transform_matrix = glm::mat4x4(1.0f);
  glm::mat4 scl_mtx = glm::mat4x4(1.f), rot_mtx = glm::mat4x4(1.f), tra_mtx = glm::mat4x4(1.f);
  GLboolean scale{ GL_FALSE }, rotate{ GL_TRUE }, translate{ GL_FALSE };

  if (scale) {
    bool use_glm = false;

    static float sx = 0.5f;
    static float sy = 0.25f;
    if (use_glm) {
      scl_mtx = glm::scale(scl_mtx, glm::vec3(sx, sy, 1.0f));
    }
    else {
      scl_mtx = glm::mat4(
        sx, 0.0, 0.0f, 0.0f,
        0.0, sy, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }
  }

  if (rotate) {
    bool use_glm = false;
    static float ang_disp_deg{};
        
    float angle = glm::radians(ang_disp_deg);
    float c = std::cos(angle);
    float s = std::sin(angle);
        
    if (use_glm) {
      rot_mtx = glm::rotate(rot_mtx, angle, glm::vec3(0.0f, 0.0f, 1.0f));    // rotation along Z axis's
    } else {
      rot_mtx = glm::mat4(
          c, s, 0.0f, 0.0f,
          -s, c, 0.0f, 0.0f,
          0.0f, 0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 1.0f
      );
    }
    ang_disp_deg += 1.f;
  }

  if (translate) {
    bool use_glm = false;
    static float tx = 0.0f;
    static float ty = 0.0f;

    if (use_glm) {
      tra_mtx = glm::translate(tra_mtx, glm::vec3(tx, ty, 0.f));
    }
    else {
      tra_mtx = glm::mat4(
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        tx, ty, 0.f, 1.f
      );
    }
  }

  //projection_mat = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  //glm::mat4 proj_mtx = glm::orthoLH_ZO(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
  //projection_mat = glm::ortho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
  //projection_mat = glm::ortho(0.0f, 10.0f, 10.0f, 0.0f); // shift origin to top-left
  //projection_mat = glm::ortho(0.0f, static_cast<float>(GLHelper::height), static_cast<float>(GLHelper::height), 0.0f); // shift origin to top-left

  //mdl.transform_matrix = proj_mtx * tra_mtx * rot_mtx * scl_mtx;
  mdl.transform_matrix = tra_mtx * rot_mtx * scl_mtx;
}

glm::mat4x4 GLApp::scale() {
    float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;

    bool useGLMScale = true;
    glm::mat4 scalingMatrix = glm::mat4(1.0f);
    if (useGLMScale) {
        // Apply scaling
        scalingMatrix = glm::scale(scalingMatrix, glm::vec3(scaleX, scaleY, scaleZ));
    }
    else {

    }

    return scalingMatrix;
}

glm::mat4x4 GLApp::translate() {
    // ortho(T left, T right, T bottom, T top)
    //glm::mat4x4 projection = glm::ortho(-1.0, 1.0, -1.0, 1.0);
    glm::mat4x4 projection = glm::ortho(-50.0, 50.0, -50.0, 50.0);

    return projection;
}

glm::mat4x4 GLApp::rotate() {
    // ortho(T left, T right, T bottom, T top)
    glm::mat4x4 projection = glm::ortho(-1.0, 1.0, -1.0, 1.0);

    return projection;
}

glm::mat4x4 GLApp::ortho() {
    // ortho(T left, T right, T bottom, T top)
    //glm::mat4x4 projection = glm::ortho(-1.0, 1.0, -1.0, 1.0);
    glm::mat4x4 projection = glm::ortho(-50.0, 50.0, -50.0, 50.0);

    return projection;
}

void GLApp::matrix_intro() {
  // Define the 16 elements of the matrix
  float elements[16] = {
      1.0f,  2.0f,  3.0f,  4.0f,   // Column 1
      5.0f,  6.0f,  7.0f,  8.0f,   // Column 2
      9.0f, 10.0f, 11.0f, 12.0f,   // Column 3
      13.0f, 14.0f, 15.0f, 16.0f   // Column 4
  };

  // Initialize the matrix with the specified elements
  glm::mat4 matrix = glm::make_mat4(elements);

  print_matrix(matrix);
}

void GLApp::matrix_initialization()
{
  // Define the 16 elements of the matrix in column-major order
  float e00 = 1.0f, e01 = 2.0f, e02 = 3.0f, e03 = 4.0f;
  float e10 = 5.0f, e11 = 6.0f, e12 = 7.0f, e13 = 8.0f;
  float e20 = 9.0f, e21 = 10.0f, e22 = 11.0f, e23 = 12.0f;
  float e30 = 13.0f, e31 = 14.0f, e32 = 15.0f, e33 = 16.0f;

  // Initialize the matrix with the specified elements
  glm::mat4 matrix(
    e00, e01, e02, e03,
    e10, e11, e12, e13,
    e20, e21, e22, e23,
    e30, e31, e32, e33);

  print_matrix(matrix);
}

void GLApp::print_matrix(const glm::mat4& matrix) {
  // Print the matrix to verify
  std::cout << "MATRIX OUTPUT BY USING SUBSCRIPT OPERATOR" << '\n';
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << std::setw(10) << std::fixed << std::setprecision(4) << matrix[i][j] << " ";
    }
    std::cout << '\n';
  }
  std::cout << "\n";
  std::cout << "PRINT MATRIX BY EXTRACTING COLUMS\n";
  for (int i = 0; i < 4; ++i) {
    glm::vec4 r = glm::column(matrix, i);
    for (int j = 0; j < 4; ++j)
      std::cout << std::setw(10) << std::fixed << std::setprecision(4) << r[j] << ' ';
    std::cout << "\n";
  }

  std::cout << "PRINT MATRIX BY EXTRACTING ROWS\n";
  for (int i = 0; i < 4; ++i) {
    glm::vec4 r = glm::row(matrix, i);
    for (int j = 0; j < 4; ++j)
      std::cout << std::setw(10) << std::fixed << std::setprecision(4) << r[j] << ' ';
    std::cout << "\n";
  }
  std::cout << "\n\n\n";
}

void GLApp::GLModel::setup_vao()
{
    // We'll define a rectangle in normalized device coordinates (NDC)
    // coordinates that has one-fourth the area of the window.
    // The NDC coordinates for a window range from [-1, 1] along both
    // both the X- and Y-axes. Therefore, the rectangle's (x, y) position
    // coordinates are in range [-0.5, 0.5]
    // We're using NDC coordinates, because we don't want to specify
    // a "model-to-world-to-view-to-clip" transform to the vertex shader.
    // Define vertex position and color attributes
    std::array<glm::vec2, 4> pos_vtx {
      glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.5f),
      glm::vec2(-0.5f, 0.5f), glm::vec2(-0.5f, -0.5f)
    };

    std::array<glm::vec3, 4> clr_vtx {
      glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f),
      glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f)
    };

    // transfer vertex position and color attributes to VBO
    glCreateBuffers(1, &vbo_hdl);
    glNamedBufferStorage(vbo_hdl,
        sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec3) * clr_vtx.size(),
        nullptr, GL_DYNAMIC_STORAGE_BIT);

    GLsizei position_data_offset    = 0;
    GLsizei position_attribute_size = sizeof(glm::vec2);
    GLsizei position_data_size      = position_attribute_size * static_cast<GLsizei>(pos_vtx.size());
    GLsizei color_data_offset       = position_data_size;
    GLsizei color_attribute_size    = sizeof(glm::vec3);
    GLsizei color_data_size         = color_attribute_size * static_cast<GLsizei>(clr_vtx.size());

    /*
        + Position offset                  + Color offset
        |                                  |
        v                                  v
        +-----------------------------------------------------------------------+
        |    Position Data                 |                Color Data          |
        +----------------------------------+------------------------------------+
              Position Data Size                      Color Data Size
        <---------------------------------> <------------------------------------>
    */
    glNamedBufferSubData(vbo_hdl, position_data_offset, position_data_size, pos_vtx.data());
    glNamedBufferSubData(vbo_hdl, color_data_offset, color_data_size, clr_vtx.data());

    // encapsulate information about contents of VBO and VBO handle
    // to another object called VAO
    glCreateVertexArrays(1, &vaoid);

    // for vertex position array, we use vertex attribute index 8
    // and vertex buffer binding point 3
    glEnableVertexArrayAttrib(vaoid, 8);
    glVertexArrayVertexBuffer(vaoid, 3, vbo_hdl, position_data_offset, position_attribute_size);

    glVertexArrayAttribFormat(vaoid, 8, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vaoid, 8, 3);
    // for vertex color array, we use vertex attribute index 9
    // and vertex buffer binding point 4
    glEnableVertexArrayAttrib(vaoid, 9);
    glVertexArrayVertexBuffer(vaoid, 4, vbo_hdl, color_data_offset, color_attribute_size);
    glVertexArrayAttribFormat(vaoid, 9, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vaoid, 9, 4);

    primitive_type = GL_TRIANGLES;

    std::array<GLushort, 6> idx_vtx{
        0, 1, 2, // 1st triangle with counterclockwise winding is specified by
                 // vertices in VBOs with indices 0, 1, 2
        2, 3, 0  // 2nd triangle with counterclockwise winding
    };
    idx_elem_cnt = static_cast<GLuint>(idx_vtx.size());

    GLuint ebo_hdl;
    glCreateBuffers(1, &ebo_hdl);
    glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_elem_cnt,
        reinterpret_cast<GLvoid*>(idx_vtx.data()),
        GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(vaoid, ebo_hdl);
    glBindVertexArray(0);
}

void GLApp::GLModel::setup_shdrpgm() {
    if (!shdr_pgm.CompileShaderFromString(GL_VERTEX_SHADER,
        my_tutorial_1_vs)) {
        std::cout << "Vertex shader failed to compile: ";
        std::cout << shdr_pgm.GetLog() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if (!shdr_pgm.CompileShaderFromString(GL_FRAGMENT_SHADER,
        my_tutorial_1_fs)) {
        std::cout << "Fragment shader failed to compile: ";
        std::cout << shdr_pgm.GetLog() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (!shdr_pgm.Link()) {
        std::cout << "Shader program failed to link!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (!shdr_pgm.Validate()) {
        std::cout << "Shader program failed to validate!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void GLApp::GLModel::draw()
{
    // there are many shader programs initialized - here we're saying
    // which specific shader program should be used to render geometry
    shdr_pgm.Use();

    glUniformMatrix4fv(shdr_pgm.GetUniformLocation("transform_mat"), 1, GL_FALSE, glm::value_ptr(transform_matrix));
    // there are many models, each with their own initialized VAO object
    // here, we're saying which VAO's state should be used to set up pipe
    glBindVertexArray(vaoid);

    // here, we're saying what primitive is to be rendered and how many
    // such primitives exist.
    // the graphics driver knows where to get the indices because the VAO
    // containing this state information has been made current ...
    glDrawElements(primitive_type, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);

    // after completing the rendering, we tell the driver that VAO
    // vaoid and current shader program are no longer current
    glBindVertexArray(0);
    shdr_pgm.UnUse();
}
