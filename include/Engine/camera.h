
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm.hpp>
#include <referenced.h>

namespace Suffer {

    class Camera : public virtual Referenced{
    public:
        Camera();

        void SetupPerspective(float fovy, float aspect, float znear, float zfar);

        void SetPosition(const glm::vec3 position);
        void SetPosition(const float position[3]);

        void SetViewDirection(const glm::vec3 view_direction);
        void SetViewDirection(const float view_direction[3]);

        void SetViewTarget(const glm::vec3 target);
        void SetViewTarget(const float target[3]);

        const float* Position() const;
        const float* Target() const;
        const float* Up() const;

    protected:
        virtual ~Camera();
    private:
        glm::vec3 position_;
        glm::vec3 camera_target_;
        glm::vec3 camera_direction_;
        
        glm::vec3 camera_right_;
        glm::vec3 camera_up_;


    };

}

#endif // __CAMERA_H__