#pragma once

#include <vector>
#include <opengl.h>

class Grid
{
    GLuint gridVAO, gridVBO;
public:
    std::vector<float> vertices;
    Grid() : gridVAO(0), gridVBO(0), vertices({}) {};
    Grid(float gridWidth_, float gridHeight_, float gridSpacing_) : gridVAO(0), gridVBO(0), vertices({}) {
        SetupGrid(gridWidth_, gridHeight_, gridSpacing_);
    };
    void SetupGrid(float gridWidth, float gridHeight, float gridSpacing);

    std::vector<float> GenerateGridVertices(float gridWidth, float gridHeight, float gridSpacing);

    void RenderGrid();
};