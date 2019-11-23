// Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__

#include <display_list.h>
#include <mutex>
#include <list>

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief:
   */
	class RenderManager {
		friend class SufferManager;

	public:
    /**
     * @brief:
     * @param:
     */
		void AddToRenderQueue(DisplayList&& logic_dl);
    /**
     * @brief:
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
  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif //__RENDER_MANAGER_H__