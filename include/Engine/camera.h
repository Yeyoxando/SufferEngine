/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-10-2019
* Camera Header
*/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector3.h"
#include "vector2.h"
#include "matrix4.h"
#include "quaternion.h"
#include <referenced.h>
#include <ref_ptr.h>

namespace Suffer {

    class Camera : public virtual Referenced {
      friend class InputManager;
      friend class Scene;

    public:
        Camera();
        Camera(const Camera& copy);
        Camera& operator=(const Camera& cam);

        /**
         * @brief: setups the projection matrix of the camera.
         * @param: fov: field of view: is the extent of the observable 
         *              world that is seen at any given moment
         * @param: aspect: screen ratio (width / height)
         * @param: znear: minimum distance at which an object is displayed
         * @param: zfar:  maximum distance at which an object is displayed.
         */
        void SetupPerspective(float fov, float aspect, float znear, float zfar);
        void SetupPerspective(float left, float right, float bottom, float top, float near, float far);

        void SetPosition(const mathmorra::Vector3 position);
        void SetPosition(const float position[3]);

        /**
         * @brief: setups the direction vector of the camera.
         */
        void SetViewDirection(const mathmorra::Vector3 view_direction);
        void SetViewDirection(const float view_direction[3]);

        void SetFOV(const float new_fov);

        /**
         * @brief: setups the projection matrix of the camera.
         */
        void SetProjectionMatrix(mathmorra::Matrix4 projection_matrix);
        void SetProjectionMatrix(const float m[16]);

        /**
         * @brief: setups the view matrix of the camera.
         */
        void SetViewMatrix(mathmorra::Matrix4 view_matrix);
        void SetViewMatrix(const float m[16]);

        const float* Target();
        const float* Position() const;
        const float* Up() const;

        const float Fov() const;

        /**
         * @return: returns the projection matrix of the camera.
         */
        mathmorra::Matrix4 ProjectionMatrix();

        /**
         * @return: returns the view matrix of the camera.
         */
        mathmorra::Matrix4 ViewMatrix();

        /**
         * @brief: begins an FPS movement of the camera
         * @param: camera: the camera that will moves
         */
        void CameraMovement(ref_ptr<Camera> camera);

        /*
         * @brief: sensitivity with which the 
                   camera eye moves with the mouse
         * @param: new_sensibility: the new value.
         */
        void SetSensibility(float new_sensitivity_);

        void SetSpeed(float new_speed);

        void SetTarget(mathmorra::Vector3 new_target);

        bool FPS();
        bool Moving();

        float Sensitivity();


        float yaw_;
        float pitch_;
        mathmorra::Vector2 last_cursor_position_;

    protected:
        virtual ~Camera();


    private:
        void Update();

        mathmorra::Vector3 camera_position_;

        mathmorra::Vector3 camera_up_;
        mathmorra::Vector3 camera_back_;
        mathmorra::Vector3 camera_right_;
        mathmorra::Vector3 camera_target_;

        mathmorra::Matrix4 view_matrix_;
        mathmorra::Matrix4 projection_matrix_;
        mathmorra::Matrix4 look_at_matrix_;

        float field_of_view_; // FOV

        // Movement attributes
        float speed_;
        float sensitivity_;
        bool  fps_movement_;


    };

}

#endif // __CAMERA_H__