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

namespace Suffer {

    class AudioManager {
        friend class SufferManager;
        friend class Audio3D;

    public:
        void AddToAudioQueue(DisplayList&& audio_dl_by_logic_);
        void DoAudio();

    private:
        void StartUp();
        void ShutDown();

        AudioManager();
        ~AudioManager();

        u32 max_audio_sources_;
        u32 audio_sources_;
        Mutex dl_mutex_;
        DisplayList audio_dl_;
        std::vector<ref_ptr<Audio3D>> audio_container_;
        
    };


}

#endif //__AUDIO_MANAGER_H__