#pragma once

#include <vector>
#include <opengl.h>

class Grid
{
    GLuint gridVAO, gridVBO;
public:
    std::vector<float> vertices;
    Grid() : gridVAO(0), gridVBO(0), vertices({}) {};
    Grid(int gridWidth_, int gridHeight_, int gridSpacing_) : gridVAO(0), gridVBO(0), vertices({}) {
        SetupGrid(gridWidth_, gridHeight_, gridSpacing_);
    };
    void SetupGrid(int gridWidth, int gridHeight, int gridSpacing);

    std::vector<float> GenerateGridVertices(int gridWidth, int gridHeight, int gridSpacing);

    void RenderGrid();
};