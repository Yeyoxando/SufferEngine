/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 12-05-2019
* SystemAudio Header
*/

#ifndef __SYSTEM_AUDIO_H__
#define __SYSTEM_AUDIO_H__

#include "system.h"
#include "game_object.h"

// --------------------------------------------------- //

namespace Suffer {

  class SystemAudio : public System {

    friend class SufferManager;
    friend class Scene;

  public:
    SystemAudio();

  protected:
    virtual void Execute(GameObject* go) override;

  private:
    ~SystemAudio();

  };

}

// --------------------------------------------------- //

#endif // __SYSTEM_AUDIO_H__