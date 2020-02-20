// Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__

#include <display_list.h>
#include "resource_manager.h"
#include <mutex>
#include <list>

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Manages all render commands using a DisplayList calculated in the logic thread.
   */
	class RenderManager {
		friend class SufferManager;
    friend class Interface;

	public:
    /**
     * @brief: Add a DisplayList to the render queue.
     * @param: Display list parameter created in logic thread.
     *         Use std::move to pass parameter without creating a copy.
     * @param: framebuffer to use for drawing
     */
		void AddToRenderQueue(DisplayList&& logic_dl, ResourceManager::FrameBuffer* framebuffer);

    /**
     * @brief: Extracts first DisplayList of the List of DLs and executes all 
     *         render commands of it.
     */
		void DoRender();
	
	private:
    void StartUp(); // a.k.a Init()
    void ShutDown(); // a.k.a End()

		RenderManager();
		~RenderManager();

		// This will be drawn
		DisplayList render_dl_;
		std::list<DisplayList> list_of_dl_;
		Mutex dl_mutex_;
    u32 dls_to_draw_;

    s32 current_drawn_texture_id_;

    struct RenderData;
    RenderData* data_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif //__RENDER_MANAGER_H__