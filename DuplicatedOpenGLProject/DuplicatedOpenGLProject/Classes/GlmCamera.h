#pragma once
#include "GlewfwConfig.h"
#include "GlmConfig.h"

namespace camera_default {
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    namespace movement {
        enum CameraMovement {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };
    }
    // Default camera values
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;

    const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 0.0f);

    const glm::vec3 UP_DIRECTION = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 DOWN_DIRECTION = glm::vec3(0.0f, -1.0f, 0.0f);

    const glm::vec3 FRONT_DIRECTION = glm::vec3(0.0f, 0.0f, -1.0f);
    const glm::vec3 BACK_DIRECTION = glm::vec3(0.0f, 0.0f, 1.0f);

    const glm::vec3 LEFT_DIRECTION = glm::vec3(-1.0f, 0.0f, 0.0f);
    const glm::vec3 RIGHT_DIRECTION = glm::vec3(1.0f, 0.0f, 0.0f);
}


class GlmCamera
{
public:
    // constructor with vectors
    GlmCamera(glm::vec3 a_Position = camera_default::POSITION,
        glm::vec3 a_Up = camera_default::UP_DIRECTION,
        float a_Yaw = camera_default::YAW, float a_Pitch = camera_default::PITCH) :

        m_Position(a_Position), m_WorldUp(a_Up), m_Yaw(a_Yaw), m_Pitch(a_Pitch),

        m_Front(camera_default::FRONT_DIRECTION),
        m_MovementSpeed(camera_default::SPEED),
        m_MouseSensitivity(camera_default::SENSITIVITY), m_Zoom(camera_default::ZOOM)
    {
        UpdateVectors();
    }
    // constructor with scalar values
    GlmCamera(
        float a_PositionX, float a_PositionY, float a_PositionZ,
        float a_UpX, float a_UpY, float a_UpZ,
        float a_Yaw = camera_default::YAW, float a_Pitch = camera_default::PITCH) :

        GlmCamera(
            glm::vec3(a_PositionX, a_PositionY, a_PositionZ),
            glm::vec3(a_UpX, a_UpY, a_UpZ),
            a_Yaw, a_Pitch)
    {}
    float GetZoom() {
        return m_Zoom;
    }
    glm::vec3 GetPosition() {
        return glm::vec3(m_Position);
    }
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        //return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        return glm::lookAt(m_Position - m_Front, m_Position, m_WorldUp);
    }
    glm::mat3 GetMatrix() {
        return glm::mat3(
            m_Right,
            m_WorldUp,
            -m_MovingFront);
    }
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(camera_default::movement::CameraMovement direction, float deltaTime)
    {
        float velocity = m_MovementSpeed * deltaTime;
        if (direction == camera_default::movement::FORWARD)
            m_Position += m_Front * velocity;
        if (direction == camera_default::movement::BACKWARD)
            m_Position -= m_Front * velocity;
        if (direction == camera_default::movement::LEFT)
            m_Position -= m_Right * velocity;
        if (direction == camera_default::movement::RIGHT)
            m_Position += m_Right * velocity;
    }
    void ProcessKeyboard(glm::vec3 direction, float deltaTime)
    {
        float velocity = m_MovementSpeed * deltaTime;
        m_Position += GetMatrix() * glm::normalize(direction) * velocity;
    }
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= m_MouseSensitivity;
        yoffset *= m_MouseSensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        UpdateVectors();
    }
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        m_Zoom -= (float)yoffset;
        if (m_Zoom < 1.0f)
            m_Zoom = 1.0f;
        if (m_Zoom > 45.0f)
            m_Zoom = 45.0f;
    }
private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_MovingFront;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    // euler Angles
    float m_Yaw;
    float m_Pitch;

    // camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;
    
    // calculates the front vector from the Camera's (updated) Euler Angles
    void UpdateVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        glm::vec3 dfront;
        dfront.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        dfront.y = 0.0f;
        dfront.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_MovingFront = glm::normalize(dfront);

        // also re-calculate the Right and Up vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }
};