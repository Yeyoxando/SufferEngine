/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-27-2019
* SystemLight Source
*/

#include "system_light.h"
#include "component_light.h"
#include "component_transform.h"
#include "common_definitions.h"
#include "suffermanager.h"
#include "draw_depth.h"
#include "draw_point_depth.h"
#include "shadow_map.h"
#include "shadow_cubemap.h"
#include "interface.h"
#include "scene.h"
#include "display_list.h"
#include "imgui.h"
#include "matrix4.h"
#include "math_utils.h"

struct ExampleAppLog {
    void    AddLog(const char* fmt, ...) IM_FMTARGS(2);
};

// --------------------------------------------------- //

Suffer::SystemLight::SystemLight(){

}

// --------------------------------------------------- //

Suffer::SystemLight::~SystemLight(){

}

// --------------------------------------------------- //

void Suffer::SystemLight::Execute(GameObject* go) {

     // LIGHTS STUFF
    {
        assert(go != nullptr && "ERROR: NULL GameObject!");
        if (go == nullptr) abort();

        if (!go->HasComponent(Suffer::Component::kComponentKind_Light)) return;
        if (!go->HasComponent(Suffer::Component::kComponentKind_Transform)) {
            Interface::log.AddLog("\n[" _warning_ "] The GameObject with the Light component also needs the Transform component too to be processed.");
            printf("WARNING: The GameObject with the Light component also needs the Transform component too to be processed.\n");
            return;
        }

        Component* transform = go->GetComponent(Suffer::Component::kComponentKind_Transform);
        Transform* transform_component = static_cast<Transform*>(transform);
        if (transform_component == nullptr) return;

        Component* light = go->GetComponent(Suffer::Component::kComponentKind_Light);
        LightComponent* light_component = static_cast<LightComponent*>(light);
        if (light_component == nullptr) return;

        if (!light_component->initialized_) {
            printf("CRITICAL ERROR: The LIGHT has not been initialized.");
            abort();
        }

        //light_component->SetDirection(transform_component->Forward());
        light_component->SetPosition(transform_component->GetGlobalPosition());


    // SHADOWS STUFF
        LightManager::LightKind shadowmap_kind = (LightManager::LightKind)light_component->reference_->GetLightKind();

        switch (shadowmap_kind){
        case Suffer::LightManager::LightKind::kLightKind_Invalid:
            break;
        case Suffer::LightManager::LightKind::kLightKind_Directional: {

            mathmorra::Matrix4 view_matrix_ = mathmorra::Matrix4::LookAt(light_component->Position(),
                mathmorra::Vector3(0.0f, 0.0f, 0.0f),
                mathmorra::Vector3(0.0f, 1.0f, 0.0f));

            mathmorra::Matrix4 projection_matrix_ = projection_matrix_.OrthoMatrix(-40.0f, 40.0f, 0.01f, 60.0f).Transpose();

            light_component->reference_->view_projection_mat_ = view_matrix_ * projection_matrix_;

            Scene* scene = suffer.GetCurrentScene();
            u32 current_gameobjects = scene->current_gameobjects_.size();

            DisplayList light_dl;

            ref_ptr<ShadowMap> shadow_cmd;
            shadow_cmd.alloc();
            shadow_cmd->SetData(light_component);

            light_dl.AddCommand(shadow_cmd.get());

            // Create a depth render command for each object in the scene
            GameObject* aux_gameobject;
            for (u32 i = 0; i < current_gameobjects; ++i) {

                ref_ptr<DrawDepth> depth_cmd;
                depth_cmd.alloc();
                aux_gameobject = scene->current_gameobjects_[i].get();
                depth_cmd->SetData(aux_gameobject);

                auto component = aux_gameobject->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
                Suffer::Transform* transform_component = static_cast<Suffer::Transform*>(component);
                if (transform_component == nullptr) return;
                depth_cmd->SetMatrix(transform_component->GetModelMatrix(),
                    view_matrix_, projection_matrix_);

                light_dl.AddCommand(depth_cmd.get());

            }

            suffer.render_manager_.AddToRenderQueue(std::move(light_dl), nullptr);
            break;
        }
        case Suffer::LightManager::LightKind::kLightKind_Point: {

            float far_plane = 25.0f;

            auto point_light = static_cast<Suffer::LightManager::PointLight*>(light_component->reference_);
            if (point_light == nullptr) {
                printf("ERROR: NULL Light.\n");
                break;
            }

            // Matrices stuff
            mathmorra::Matrix4 projection_matrix = projection_matrix.PerspectiveMatrix(ThiefUtils::Math::Radians(90.0f), (float)suffer.GetWindowSize().x_ / (float)suffer.GetWindowSize().y_, 1.0f, far_plane);
            mathmorra::Vector3 light_position = point_light->Position();

            point_light->view_matrices_[0] = mathmorra::Matrix4::LookAt(light_position, light_position + mathmorra::Vector3( 1.0f,  0.0f,  0.0f), mathmorra::Vector3(0.0f, -1.0f,  0.0f));
            point_light->view_matrices_[1] = mathmorra::Matrix4::LookAt(light_position, light_position + mathmorra::Vector3(-1.0f,  0.0f,  0.0f), mathmorra::Vector3(0.0f, -1.0f,  0.0f));
            point_light->view_matrices_[2] = mathmorra::Matrix4::LookAt(light_position, light_position + mathmorra::Vector3( 0.0f,  1.0f,  0.0f), mathmorra::Vector3(0.0f,  0.0f,  1.0f));
            point_light->view_matrices_[3] = mathmorra::Matrix4::LookAt(light_position, light_position + mathmorra::Vector3( 0.0f, -1.0f,  0.0f), mathmorra::Vector3(0.0f,  0.0f, -1.0f));
            point_light->view_matrices_[4] = mathmorra::Matrix4::LookAt(light_position, light_position + mathmorra::Vector3( 0.0f,  0.0f,  1.0f), mathmorra::Vector3(0.0f, -1.0f,  0.0f));
            point_light->view_matrices_[5] = mathmorra::Matrix4::LookAt(light_position, light_position + mathmorra::Vector3( 0.0f,  0.0f, -1.0f), mathmorra::Vector3(0.0f, -1.0f,  0.0f));

            point_light->view_matrices_[0] = projection_matrix * point_light->view_matrices_[0];
            point_light->view_matrices_[1] = projection_matrix * point_light->view_matrices_[1];
            point_light->view_matrices_[2] = projection_matrix * point_light->view_matrices_[2];
            point_light->view_matrices_[3] = projection_matrix * point_light->view_matrices_[3];
            point_light->view_matrices_[4] = projection_matrix * point_light->view_matrices_[4];
            point_light->view_matrices_[5] = projection_matrix * point_light->view_matrices_[5];


            Scene* scene = suffer.GetCurrentScene();
            u32 current_gameobjects = scene->current_gameobjects_.size();

            DisplayList light_dl;

            ref_ptr<ShadowCubemap> shadow_cubemap_cmd;
            shadow_cubemap_cmd.alloc();
            shadow_cubemap_cmd->SetData(light_component);

            light_dl.AddCommand(shadow_cubemap_cmd.get());

            // Create a point depth render command for each object in the scene
            GameObject* aux_gameobject;
            for (u32 i = 0; i < current_gameobjects; ++i) {

                ref_ptr<DrawPointDepth> point_depth_cmd;
                point_depth_cmd.alloc();
                aux_gameobject = scene->current_gameobjects_[i].get();
                point_depth_cmd->SetData(aux_gameobject, light_position, far_plane);

                auto component = aux_gameobject->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
                Suffer::Transform* transform_component = static_cast<Suffer::Transform*>(component);
                if (transform_component == nullptr) return;
                point_depth_cmd->SetMatrices(transform_component->GetModelMatrix(), point_light->view_matrices_);

                light_dl.AddCommand(point_depth_cmd.get());

            }

            suffer.render_manager_.AddToRenderQueue(std::move(light_dl), nullptr);


            break;
        }
        default:
            break;
        }
      
      

    }
}

// --------------------------------------------------- //