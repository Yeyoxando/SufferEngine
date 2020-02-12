/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-12-2019
* SystemScript Header
*/

#ifndef __SYSTEM_SCRIPT_H__
#define __SYSTEM_SCRIPT_H__

#include "system.h"
#include "game_object.h"

// --------------------------------------------------- //

namespace Suffer {

  class SystemScript : public System {

    friend class SufferManager;
    friend class Scene;

  public:
    SystemScript();

  protected:
    virtual void Execute(GameObject* go) override;

  private:
    ~SystemScript();

  };

}

// --------------------------------------------------- //

#endif // __SYSTEM_SCRIPT_H__