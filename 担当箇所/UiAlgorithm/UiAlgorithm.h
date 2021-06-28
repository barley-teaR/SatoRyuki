#pragma once
#include "../../../ESGLib.h"

//一の位の数値を返す
static int OnesPlace(int value)
{
	return (value % 1000) % 100 % 10;
}
//十の位の数値を返す
static int TensPlace(int value)
{
	return (value % 1000) % 100 / 10;
}
//百の位の数値を返す
static int HundredPlace(int value)
{
	return (value % 1000) / 100;
}
//千の位の数値を返す
static int ThousandPlace(int value)
{
	return value / 1000;
}

//どの位の数値を取るか配列で返す
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