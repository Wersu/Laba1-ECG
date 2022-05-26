#pragma once
#include <glm/glm.hpp>
#ifndef CAMERA_H
#define	CAMERA_H
#include "pipeline.h"
//#include "Camera.cpp"
using namespace glm;

class Camera
{
public:

    Camera();

    Camera(const vec3& Pos, const vec3& Target, const vec3& Up);

    bool OnKeyboard(int Key);

    const vec3& GetPos() const
    {
        return m_pos;
    }

    const vec3& GetTarget() const
    {
        return m_target;
    }

    const vec3& GetUp() const
    {
        return m_up;
    }

private:

    vec3 m_pos;
    vec3 m_target;
    vec3 m_up;
};
#endif