#pragma once
#include "../../../ESGLib.h"

//��̈ʂ̐��l��Ԃ�
static int OnesPlace(int value)
{
	return (value % 1000) % 100 % 10;
}
//�\�̈ʂ̐��l��Ԃ�
static int TensPlace(int value)
{
	return (value % 1000) % 100 / 10;
}
//�S�̈ʂ̐��l��Ԃ�
static int HundredPlace(int value)
{
	return (value % 1000) / 100;
}
//��̈ʂ̐��l��Ԃ�
static int ThousandPlace(int value)
{
	return value / 1000;
}

//�ǂ̈ʂ̐��l����邩�z��ŕԂ�
static std::vector<int> CalculationOfPlace(int value)
{
	std::vector<int> num;
	num.push_back(ThousandPlace(value));
	num.push_back(HundredPlace(value));
	num.push_back(TensPlace(value));
	num.push_back(OnesPlace(value));
	return num;
}

static Vector3 VectorMatrixMultiplication(Vector3& vector, Matrix& matrix)
{
	Vector3 transform;
	const float w = 1.0f / (vector.x * matrix._14 + vector.y * matrix._24 + vector.z * matrix._34 + matrix._44);
	transform.x = (vector.x * matrix._11 + vector.y * matrix._21 + vector.z * matrix._31 + matrix._41) * w;
	transform.y = (vector.x * matrix._12 + vector.y * matrix._22 + vector.z * matrix._32 + matrix._42) * w;
	transform.z = (vector.x * matrix._13 + vector.y * matrix._23 + vector.z * matrix._33 + matrix._43) * w;

	return transform;
}

static Vector3 WorldToScreen(Vector3& pos, Camera& camera)
{
	Matrix view = camera.GetViewMatrix();
	Matrix projection = camera.GetProjectionMatrix();
	Matrix view_port = GraphicsDevice.GetViewportMatrix();

	Vector3 screen_pos = pos;
	screen_pos = VectorMatrixMultiplication(screen_pos, view);
	screen_pos = VectorMatrixMultiplication(screen_pos, projection);
	screen_pos = VectorMatrixMultiplication(screen_pos, view_port);

	return screen_pos;
}