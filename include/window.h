// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef WINDOW_H
#define WINDOW_H

namespace Suffer {
  /**
    * @brief:
    */
	class Window {
    friend class SufferManager;
	private:
		Window();
		~Window();

    /**
    * @brief:
    * @param:
    * @param:
    */
		bool init(int width, int height);
		
    /**
    * @brief:
    */
    bool processEvents();
		
    /**
    * @brief:
    */
    void swapBuffers();
		
    /**
    * @brief:
    */
    void finish();

	};
};

#endif // WINDOW_H
