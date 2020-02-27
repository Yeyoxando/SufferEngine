/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-27-2019
* SystemLight Header
*/

#ifndef __LIGHT_SYSTEM_H__
#define __LIGHT_SYSTEM_H__

#include "system.h"

namespace Suffer {

    class SystemLight : public System {

    public:
        SystemLight();

    protected:
        virtual void Execute(GameObject* go) override;

    private:
        ~SystemLight();
    };

}

#endif // __LIGHT_SYSTEM_H__
