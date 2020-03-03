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
#include "shadow_map.h"
#include "interface.h"
#include "scene.h"
#include "display_list.h"
#include "imgui.h"
#include "matrix4.h"

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

        Component* light = go->GetComponent(Suffer::Component::kComponentKind_Light);
        LightComponent* light_component = static_cast<LightComponent*>(light);

        if (!light_component->initialized_) {
            printf("CRITICAL ERROR: The LIGHT has not been initialized.");
            abort();
        }

        light_component->SetDirection(transform_component->Forward());
        light_component->SetPosition(transform_component->GetPosition());


    // SHADOWS STUFF
      
      // Calculate light view and projection matrix (Directional only for the moment)
      mathmorra::Matrix4 view_matrix_ = mathmorra::Matrix4::LookAt(light_component->Position(),
        mathmorra::Vector3(0.0f, 0.0f, 0.0f),
        mathmorra::Vector3(0.0f, 1.0f, 0.0f));

      light_component->reference_->view_mat_ = view_matrix_;
      
      mathmorra::Matrix4 projection_matrix_ = projection_matrix_.OrthoMatrix(-20.0f, 20.0f, 1.0f, 20.0f).Transpose();

      light_component->reference_->projection_mat_ = projection_matrix_;

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
        Suffer::Transform* transform_component = reinterpret_cast<Suffer::Transform*>(component);
        depth_cmd->SetMatrix(transform_component->GetModelMatrix(),
          view_matrix_, projection_matrix_);

        light_dl.AddCommand(depth_cmd.get());

      }

      suffer.render_manager_.AddToRenderQueue(std::move(light_dl), nullptr);

    }
}

// --------------------------------------------------- //