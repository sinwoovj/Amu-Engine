#pragma once

#include <vector>
#include <opengl.h>

class Grid
{
    GLuint gridVAO, gridVBO;
    std::vector<float> vertices;
public:
    Grid() : gridVAO(0), gridVBO(0), vertices({}) {};
    Grid(float gridSize_, float gridSpacing_) : gridVAO(0), gridVBO(0), vertices({}) {
        SetupGrid(gridSize_, gridSpacing_);
    };
    void SetupGrid(float gridSize, float gridSpacing);

    std::vector<float> GenerateGridVertices(float gridSize, float gridSpacing);

    void RenderGrid();
};