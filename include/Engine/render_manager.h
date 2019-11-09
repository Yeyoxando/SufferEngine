// Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__

#include <display_list.h>
#include <mutex>
#include <list>

namespace Suffer {

	class RenderManager {
		friend class SufferManager;


	public:
		void AddToRenderQueue(DisplayList&& logic_dl);
		void DoRender();
	
	private:
		void StartUp();
		void ShutDown();

		RenderManager();
		~RenderManager();

		// This will be drawn
		DisplayList render_dl_;
		std::list<DisplayList> list_of_dl_;
		Mutex dl_mutex_;
	};


}

#endif //__RENDER_MANAGER_H__