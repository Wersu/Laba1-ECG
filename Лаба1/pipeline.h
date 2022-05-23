#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
using namespace glm;

class Pipeline
{
public:
	Pipeline()
	{
        mScale = vec3(1.0f, 1.0f, 1.0f);
        mWorldPos = vec3(0.0f, 0.0f, 0.0f);
        mRotateInfo = vec3(0.0f, 0.0f, 0.0f);
	}

	void Scale(float ScaleX, float ScaleY, float ScaleZ)
	{
		mScale.x = ScaleX;
		mScale.y = ScaleY;
		mScale.z = ScaleZ;
	}

	void WorldPos(float x, float y, float z)
	{
		mWorldPos.x = x;
		mWorldPos.y = y;
		mWorldPos.z = z;
	}

	void Rotate(float RotateX, float RotateY, float RotateZ)
	{
		mRotateInfo.x = RotateX;
		mRotateInfo.y = RotateY;
		mRotateInfo.z = RotateZ;
	}

	void PerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
	{
		mPersProj.FOV = FOV;
		mPersProj.width = Width;
		mPersProj.height = Height;
		mPersProj.zNear = zNear;
		mPersProj.zFar = zFar;
	}

	void SetCamera(const vec3& pos, const vec3& target, const vec3& up) 
    {
        mCamera.Pos = pos;
        mCamera.Target = target;
        mCamera.Up = up;

	}

	void InitCameraTrans(mat4& m, const vec3& Target, const vec3& Up)//генерирует преобразования камеры, которые позднее будут использованы конвейером
	{
		vec3 N = Target;
		normalize(N);//сделать вектора единичной длины
		vec3 U = Up;
		normalize(U);
		U = cross(U, Target);//cross - возвращает вектор, перпендикулярный плоскости, определяемой исходными векторами
		vec3 V = cross(N, U);

		m[0][0] = U.x; m[0][1] = U.y; m[0][2] = U.z; m[0][3] = 0.0f;
		m[1][0] = V.x; m[1][1] = V.y; m[1][2] = V.z; m[1][3] = 0.0f;
		m[2][0] = N.x; m[2][1] = N.y; m[2][2] = N.z; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	const mat4* getTransformation();

private:
	void InitScaleTrans(mat4& m) const;
	void InitRotateTrans(mat4& m) const;
	void InitTranslationTrans(float x, float y, float z, mat4& m) const;
	void InitPerspectiveProj(mat4& m) const;

    vec3 mScale;
    vec3 mWorldPos;
    vec3 mRotateInfo;

    struct {
        float FOV;
        float width;
        float height;
        float zNear;
        float zFar;
    } mPersProj;

    struct {
        vec3 Pos;
        vec3 Target;
        vec3 Up;
    } mCamera;

	mat4 m_transformation;
};