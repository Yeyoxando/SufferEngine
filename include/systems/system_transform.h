/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-28-2019
* SystemTransform Header
*/

#ifndef __SYSTEM_TRANSFORM_H__
#define __SYSTEM_TRANSFORM_H__

#include "system.h"
#include "game_object.h"

// --------------------------------------------------- //

namespace Suffer {

    class SystemTransform : public System {

        friend class SufferManager;
        friend class Scene;

        private:
            SystemTransform();
            ~SystemTransform();

            void Execute(GameObject* go);
    };

}

// --------------------------------------------------- //

#endif // __SYSTEM_TRANSFORM_H__