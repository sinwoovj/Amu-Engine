#include "Grid.h"

std::vector<float> Grid::GenerateGridVertices(int gridWidth, int gridHeight, int gridSpacing) {
    std::vector<float> vertices;

    // ���� �� (y�� ����)
    for (float x = -1; x <= 1; x += (float)gridSpacing / gridWidth) {
        vertices.push_back(x);
        vertices.push_back(-1);
        vertices.push_back(0.0f); // z�� (2D �׸����� ��� z�� 0)

        vertices.push_back(x);
        vertices.push_back(1);
        vertices.push_back(0.0f);
    }

    // ���� �� (x�� ����)
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

void Grid::SetupGrid(int gridWidth, int gridHeight, int gridSpacing) { // ���̴� ���α׷� �ȿ� �־�� ��.
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

void Grid::RenderGrid() { // ���̴� ���α׷� �ȿ� �־�� ��.
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, vertices.size() / 3);  // �� ���� �� ���� �������� ������
    glBindVertexArray(0);
}