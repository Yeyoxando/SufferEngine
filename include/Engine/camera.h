/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-10-2019
* Camera Header
*/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm.hpp>
#include <referenced.h>
#include <ref_ptr.h>

namespace Suffer {

    class Camera : public virtual Referenced {
    public:
        Camera();
        Camera(const Camera& copy);
        Camera& operator=(const Camera& cam);

        void SetupPerspective(float fovy, float aspect, float znear, float zfar);

        void SetupFrustum(float left, float right,
                          float bottom, float top,
                          float znear, float zfar);

        void SetPosition(const glm::vec3 position);
        void SetPosition(const float position[3]);

        void SetViewDirection(const glm::vec3 view_direction);
        void SetViewDirection(const float view_direction[3]);

        void SetViewTarget(const glm::vec3 target);
        void SetViewTarget(const float target[3]);

        void SetFOV(const float new_fov);

        void SetForward(const float forward[3]);
        void SetForward(const glm::vec3 forward);

        void SetProjectionMatrix(glm::mat4 projection_matrix);
        void SetProjectionMatrix(const float m[16]);

        void SetViewMatrix(glm::mat4 view_matrix);
        void SetViewMatrix(const float m[16]);

        const float* Position() const;
        const float* Target() const;
        const float* Up() const;

        const float Fov() const;

        // FPS Movement
        void CameraMovement(ref_ptr<Camera> camera);
        void SetSensibility(float new_sensibility);
        void SetSpeed(float new_speed);

    protected:
        virtual ~Camera();

    private:
        glm::vec3 position_;
        glm::vec3 camera_target_;
        glm::vec3 camera_direction_;

        glm::vec3 camera_up_;
        glm::vec3 camera_right_;
        glm::vec3 camera_forward_;

        glm::mat4 view_matrix_;
        glm::mat4 projection_matrix_;

        float field_of_view_; // FOV

        // Movement attributes
        float speed_;
        float sensibility_;


    };

}

#endif // __CAMERA_H__