#pragma once

#include <opengl.h>

void Mtx33Trans(glm::mat3* TransMtx, float x, float y);

void Mtx33Rot(glm::mat3* RotMtx, float angle);

void Mtx33Scale(glm::mat3* scaleMtx, float x, float y);

void Mtx33Concat(glm::mat3* mat1, glm::mat3* mat2, glm::mat3* mat3);