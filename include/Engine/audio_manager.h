/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-10-2019
* AudioManager Header
*/

#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include <display_list.h>
#include <mutex>
#include <audio.h>
#include <vector>
#include "audio_commands.h"

namespace Suffer {

    class AudioManager {
      friend class SufferManager;
      friend class Audio3D;
      friend class Camera;
      friend class Interface;

public:

    /**
        * @brief: moves the DL calculated by the logic to the audio DL
        * @param: the DL calculated by the logic
        */
    void AddToAudioQueue(DisplayList&& audio_dl_by_logic_);

    /**
        * @brief: executes the audio DisplayList
        */
    void DoAudio();

    Mutex crossfade_mutex_;

private:
    void StartUp();  // a.k.a Init()
    void ShutDown(); // a.k.a End()

    AudioManager();
    ~AudioManager();

    u32 max_audio_sources_;
    u32 audio_sources_;
    Mutex dl_mutex_;
    DisplayList audio_dl_;
    std::vector<ref_ptr<Audio3D>> audio_container_;

};


}

#endif //AUDIO_MANAGER_H