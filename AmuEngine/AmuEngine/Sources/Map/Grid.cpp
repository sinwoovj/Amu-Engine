#include "Grid.h"

std::vector<float> Grid::GenerateGridVertices(float gridSize, float gridSpacing) {
    std::vector<float> vertices;

    // ���� �� (y�� ����)
    for (float x = -gridSize; x <= gridSize; x += gridSpacing) {
        vertices.push_back(x);
        vertices.push_back(-gridSize);
        vertices.push_back(0.0f); // z�� (2D �׸����� ��� z�� 0)

        vertices.push_back(x);
        vertices.push_back(gridSize);
        vertices.push_back(0.0f);
    }

    // ���� �� (x�� ����)
    for (float y = -gridSize; y <= gridSize; y += gridSpacing) {
        vertices.push_back(-gridSize);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        vertices.push_back(gridSize);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    return vertices;
}

void Grid::SetupGrid(float gridSize, float gridSpacing) { // ���̴� ���α׷� �ȿ� �־�� ��.
    vertices = GenerateGridVertices(gridSize, gridSpacing);

    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);

    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);  // Unbind VAO
}

void Grid::RenderGrid() { // ���̴� ���α׷� �ȿ� �־�� ��.
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, vertices.size() / 3);  // �� ���� �� ���� �������� ������
    glBindVertexArray(0);
}