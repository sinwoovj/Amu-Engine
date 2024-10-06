#include "EasyOpengl.h"

void Mtx33Trans(glm::mat3* TransMtx, float x, float y)
{
	// 평행 이동 행렬 생성
	glm::mat3 translationMatrix = glm::mat3(1.0f);  // 단위 행렬로 초기화
	translationMatrix[2][0] = x;  // x축 이동
	translationMatrix[2][1] = y;  // y축 이동

	// 평행 이동 행렬을 적용
	*TransMtx = translationMatrix * (*TransMtx);
};
void Mtx33Rot(glm::mat3* RotMtx, float angle)
{
	// 각도를 라디안 단위로 변환 (glm의 rotate는 라디안을 사용)
	float radians = glm::radians(angle);

	// 회전 행렬 생성
	glm::mat3 rotationMatrix = glm::mat3(1.0f);
	rotationMatrix[0][0] = cos(radians);
	rotationMatrix[0][1] = -sin(radians);
	rotationMatrix[1][0] = sin(radians);
	rotationMatrix[1][1] = cos(radians);

	// 회전 행렬을 적용
	*RotMtx = rotationMatrix * (*RotMtx);
};

void Mtx33Scale(glm::mat3* scaleMtx, float x, float y)
{
	// 스케일링 적용 (x축 2배, y축 0.5배)
	glm::mat3 scaleMatrix = glm::mat3(1.0f);
	scaleMatrix[0][0] = x;  // x축 스케일
	scaleMatrix[1][1] = y;  // y축 스케일

	// 스케일 행렬을 모델 행렬에 곱하기
	*scaleMtx = (*scaleMtx) * scaleMatrix;
};

void Mtx33Concat(glm::mat3* mat1, glm::mat3* mat2, glm::mat3* mat3)
{
	// mat1과 mat2의 행렬을 곱해서 mat3에 저장
	*mat3 = (*mat1) * (*mat2);
};