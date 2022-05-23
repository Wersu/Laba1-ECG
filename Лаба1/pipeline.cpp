#define M_PI 3.14159F
#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)
#include "pipeline.h"
using namespace glm;


void Pipeline::InitScaleTrans(mat4& m) const
{
	m[0][0] = mScale.x;  m[0][1] = 0.0f;      m[0][2] = 0.0f;      m[0][3] = 0.0f;
	m[1][0] = 0.0f;      m[1][1] = mScale.y;  m[1][2] = 0.0f;      m[1][3] = 0.0f;
	m[2][0] = 0.0f;      m[2][1] = 0.0f;      m[2][2] = mScale.z;  m[2][3] = 0.0f;
	m[3][0] = 0.0f;      m[3][1] = 0.0f;      m[3][2] = 0.0f;      m[3][3] = 1.0f;
}

void Pipeline::InitRotateTrans(mat4& m) const
{
	mat4 rx, ry, rz;

	const float x = ToRadian(mRotateInfo.x);
	const float y = ToRadian(mRotateInfo.y);
	const float z = ToRadian(mRotateInfo.z);

	rx[0][0] = 1.0f; rx[0][1] = 0.0f;    rx[0][2] = 0.0f;     rx[0][3] = 0.0f;
	rx[1][0] = 0.0f; rx[1][1] = cosf(x); rx[1][2] = -sinf(x); rx[1][3] = 0.0f;
	rx[2][0] = 0.0f; rx[2][1] = sinf(x); rx[2][2] = cosf(x);  rx[2][3] = 0.0f;
	rx[3][0] = 0.0f; rx[3][1] = 0.0f;    rx[3][2] = 0.0f;     rx[3][3] = 1.0f;

	ry[0][0] = cosf(y); ry[0][1] = 0.0f; ry[0][2] = -sinf(y); ry[0][3] = 0.0f;
	ry[1][0] = 0.0f;    ry[1][1] = 1.0f; ry[1][2] = 0.0f;     ry[1][3] = 0.0f;
	ry[2][0] = sinf(y); ry[2][1] = 0.0f; ry[2][2] = cosf(y);  ry[2][3] = 0.0f;
	ry[3][0] = 0.0f;    ry[3][1] = 0.0f; ry[3][2] = 0.0f;     ry[3][3] = 1.0f;

	rz[0][0] = cosf(z); rz[0][1] = -sinf(z); rz[0][2] = 0.0f; rz[0][3] = 0.0f;
	rz[1][0] = sinf(z); rz[1][1] = cosf(z);  rz[1][2] = 0.0f; rz[1][3] = 0.0f;
	rz[2][0] = 0.0f;    rz[2][1] = 0.0f;     rz[2][2] = 1.0f; rz[2][3] = 0.0f;
	rz[3][0] = 0.0f;    rz[3][1] = 0.0f;     rz[3][2] = 0.0f; rz[3][3] = 1.0f;

	m = rz * ry * rx;
}

void Pipeline::InitTranslationTrans(float x, float y, float z, mat4& m) const
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Pipeline::InitPerspectiveProj(mat4& m) const
{
	const float ar = mPersProj.width / mPersProj.height;
	const float zNear = mPersProj.zNear;
	const float zFar = mPersProj.zFar;
	const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(ToRadian(mPersProj.FOV / 2.0f));

	m[0][0] = 1.0f / (tanHalfFOV * ar); m[0][1] = 0.0f;              m[0][2] = 0.0f;                     m[0][3] = 0.0;
	m[1][0] = 0.0f;                     m[1][1] = 1.0f / tanHalfFOV; m[1][2] = 0.0f;                     m[1][3] = 0.0;
	m[2][0] = 0.0f;                     m[2][1] = 0.0f;              m[2][2] = (-zNear - zFar) / zRange; m[2][3] = 2.0f * zFar * zNear / zRange;
	m[3][0] = 0.0f;                     m[3][1] = 0.0f;              m[3][2] = 1.0f;                     m[3][3] = 0.0;
}

const mat4* Pipeline::getTransformation()
{
	mat4 scaleTrans, rotateTrans, translationTrans, persProjTrans, cameraTranslationTrans, cameraRotateTrans;

	InitScaleTrans(scaleTrans);
	InitRotateTrans(rotateTrans);
	InitTranslationTrans(mWorldPos.x, mWorldPos.y, mWorldPos.z, translationTrans);
	InitTranslationTrans(-mCamera.Pos.x, -mCamera.Pos.y, -mCamera.Pos.z, cameraTranslationTrans);
	InitCameraTrans(cameraRotateTrans, mCamera.Target, mCamera.Up);
	InitPerspectiveProj(persProjTrans);

	m_transformation = cameraRotateTrans * cameraTranslationTrans * translationTrans * rotateTrans * scaleTrans * persProjTrans;
	return &m_transformation;

}