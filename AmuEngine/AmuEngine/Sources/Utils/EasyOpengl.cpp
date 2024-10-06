#include "EasyOpengl.h"

void Mtx33Trans(glm::mat3* TransMtx, float x, float y)
{
	// ���� �̵� ��� ����
	glm::mat3 translationMatrix = glm::mat3(1.0f);  // ���� ��ķ� �ʱ�ȭ
	translationMatrix[2][0] = x;  // x�� �̵�
	translationMatrix[2][1] = y;  // y�� �̵�

	// ���� �̵� ����� ����
	*TransMtx = translationMatrix * (*TransMtx);
};
void Mtx33Rot(glm::mat3* RotMtx, float angle)
{
	// ������ ���� ������ ��ȯ (glm�� rotate�� ������ ���)
	float radians = glm::radians(angle);

	// ȸ�� ��� ����
	glm::mat3 rotationMatrix = glm::mat3(1.0f);
	rotationMatrix[0][0] = cos(radians);
	rotationMatrix[0][1] = -sin(radians);
	rotationMatrix[1][0] = sin(radians);
	rotationMatrix[1][1] = cos(radians);

	// ȸ�� ����� ����
	*RotMtx = rotationMatrix * (*RotMtx);
};

void Mtx33Scale(glm::mat3* scaleMtx, float x, float y)
{
	// �����ϸ� ���� (x�� 2��, y�� 0.5��)
	glm::mat3 scaleMatrix = glm::mat3(1.0f);
	scaleMatrix[0][0] = x;  // x�� ������
	scaleMatrix[1][1] = y;  // y�� ������

	// ������ ����� �� ��Ŀ� ���ϱ�
	*scaleMtx = (*scaleMtx) * scaleMatrix;
};

void Mtx33Concat(glm::mat3* mat1, glm::mat3* mat2, glm::mat3* mat3)
{
	// mat1�� mat2�� ����� ���ؼ� mat3�� ����
	*mat3 = (*mat1) * (*mat2);
};