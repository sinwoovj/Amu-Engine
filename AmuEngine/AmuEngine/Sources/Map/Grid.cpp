#include "Grid.h"

std::vector<float> Grid::GenerateGridVertices(int gridWidth, int gridHeight, int gridSpacing) {
    std::vector<float> vertices;

    // 세로 선 (y축 기준)
    for (float x = -1; x <= 1; x += (float)gridSpacing / gridWidth) {
        vertices.push_back(x);
        vertices.push_back(-1);
        vertices.push_back(0.0f); // z축 (2D 그리드의 경우 z는 0)

        vertices.push_back(x);
        vertices.push_back(1);
        vertices.push_back(0.0f);
    }

    // 가로 선 (x축 기준)
    for (float y = -1; y <= 1; y += (float)gridSpacing / gridHeight) {
        vertices.push_back(-1);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        vertices.push_back(1);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    return vertices;
}

void Grid::SetupGrid(int gridWidth, int gridHeight, int gridSpacing) { // 셰이더 프로그램 안에 넣어야 함.
    vertices = GenerateGridVertices(gridWidth, gridHeight, gridSpacing);

    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);

    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);  // Unbind VAO
}

void Grid::RenderGrid() { // 셰이더 프로그램 안에 넣어야 함.
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, vertices.size() / 3);  // 각 선은 두 개의 정점으로 구성됨
    glBindVertexArray(0);
}