/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-12-2019
* ComponentScript Header
*/

#ifndef __COMPONENT_SCRIPT_H__
#define __COMPONENT_SCRIPT_H__

#include "component.h"

namespace Suffer {

  class ScriptComponent : public Component {
    friend class SystemScript;

  public:
    ScriptComponent();

    void AttachScript(const char* script_path);

  protected:
    virtual ~ScriptComponent();

  private:
    ScriptComponent(const ScriptComponent&) = delete;

    void Update();
    void Start();

    struct ScriptData;
    ScriptData* data_;

    // TODO: test
    bool initialized_;
    bool script_attached_;

  };

}

#endif //  __COMPONENT_SCRIPT_H__