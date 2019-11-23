// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef WINDOW_H
#define WINDOW_H

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
    * @brief: Manages the Engine Window 
    */
	class Window {
    friend class SufferManager;

	private:
		Window();
		~Window();

    /**
     * @brief: Open and initializes all the necessary dependencies to create a window context
     * @param: width of the window
     * @param: height of the window
     * @return: true if all is initialized successful
     */
		bool Open(int width, int height);
		
    /**
    * @brief: processes all the window events
    */
    void ProcessEvents();
		
    /**
    * @brief: swap the two buffers used to render 
    */
    void SwapBuffers();
		
    /**
    * @brief: closes and destroy the window context
    */
    void Close();


    struct Data;
    Data* data_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // WINDOW_H
