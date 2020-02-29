/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-27-2019
* SystemLight Source
*/

#include "system_light.h"
#include "component_light.h"
#include "component_transform.h"
#include "interface.h"
#include "imgui.h"

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

    }

    // SHADOWS STUFF
}

// --------------------------------------------------- //