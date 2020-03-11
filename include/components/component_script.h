/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-12-2019
* ComponentScript Header
*/

#ifndef __COMPONENT_SCRIPT_H__
#define __COMPONENT_SCRIPT_H__

#include "component.h"
#include "game_object.h"

namespace Suffer {

  class ScriptComponent : public Component {
    friend class SystemScript;
    friend class Interface;

  public:
    ScriptComponent();

    void AttachScript(char* script_path);
    void Reload(char* new_path);

  protected:
    ~ScriptComponent();

  private:
    ScriptComponent(const ScriptComponent&) = delete;

    void Update();
    void Start();

    struct ScriptData;
    ScriptData* data_;

    // TODO: test
    bool initialized_;
    bool script_attached_;
    GameObject* reference_;

  };

}

#endif //  __COMPONENT_SCRIPT_H__