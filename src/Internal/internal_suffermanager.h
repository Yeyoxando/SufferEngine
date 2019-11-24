// Author: Pablo Banyo Benito <banyobe@esat-alumni.com>

#ifndef __INTERNAL_SUFFERMANAGER_H__
#define __INTERNAL_SUFFERMANAGER_H__

#include "suffermanager.h"
#include "window.h"
#include "interface.h"

// ------------------------------------------------------------------------- //

struct Suffer::SufferManager::Data {

    Suffer::Window wind_;
    double previous_time_;
    double current_time_;
    double delta_time_;
    Interface interface_;
    bool is_interface_active_;

    ref_ptr<Scene> scene_context_;

    // Running
    bool window_should_close_;

};

// ------------------------------------------------------------------------- //

#endif //__INTERNAL_SUFFERMANAGER_H__