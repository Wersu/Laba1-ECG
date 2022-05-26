#include "camera.h"
#include <GL/freeglut.h>

const static float StepScale = 0.1f;

Camera::Camera()
{
    m_pos    = vec3(0.0f, 0.0f, 0.0f);
    m_target = vec3(0.0f, 0.0f, 1.0f);
    m_up     = vec3(0.0f, 1.0f, 0.0f);
}


Camera::Camera(const vec3& Pos, const vec3& Target, const vec3& Up)
{
    m_pos    = Pos;
    m_target = Target;
    normalize(m_target);
    m_up     = Up;
    normalize(m_up);
}


bool Camera::OnKeyboard(int Key)
{
    bool Ret = false;

    switch (Key) {

    case GLUT_KEY_UP:
    {
        m_pos += (m_target * StepScale);
        Ret = true;
    }
    break;

    case GLUT_KEY_DOWN:
    {
        m_pos -= (m_target * StepScale);
        Ret = true;
    }
    break;

    case GLUT_KEY_LEFT:
    {
        vec3 Left = cross(m_target, m_up);
        normalize(Left);
        Left *= StepScale;
        m_pos += Left;
        Ret = true;
    }
    break;

    case GLUT_KEY_RIGHT:
    {
        vec3 Right = cross(m_up, m_target);
        normalize(Right);
        Right *= StepScale;
        m_pos += Right;
        Ret = true;
    }
    break;
    }

    return Ret;
}

