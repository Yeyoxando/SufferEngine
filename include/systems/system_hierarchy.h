/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 03-11-2020
* HierarchySystem Header
*/

#ifndef __SYSTEM_HIERARCHY_H__
#define __SYSTEM_HIERARCHY_H__

#include "system.h"

namespace Suffer {

    class SystemHierarchy : public System {
        friend class SufferManager;
    public:
        SystemHierarchy();
    protected:
        virtual void Execute(GameObject* go) override;
    private:
        ~SystemHierarchy();

    };

} // End of Suffer namespace

#endif // __SYSTEM_HIERARCHY_H__
