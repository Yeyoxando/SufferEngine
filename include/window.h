#ifndef WINDOW_H
#define WINDOW_H

namespace Suffer {
	class Window {
	public:
		Window();
		~Window();
		bool init(int width, int height);
		bool processEvents();
		void swapBuffers();
		void finish();
	private:

	};
};

#endif // WINDOW_H
